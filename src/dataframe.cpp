#include "codemasterspandas/dataframe.hpp"
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace codemasterspandas {
DataFrame::DataFrame(std::vector<std::string> names, std::vector<std::vector<Value>> rows) {
    if (names.empty() && !rows.empty()) throw std::invalid_argument("rows require at least one column");
    for (const auto& row : rows) if (row.size() != names.size()) throw std::invalid_argument("row width does not match columns");
    row_count_ = rows.size();
    for (std::size_t c = 0; c < names.size(); ++c) {
        std::vector<Value> values; values.reserve(rows.size());
        for (const auto& row : rows) values.push_back(row[c]);
        add_column(names[c], std::move(values));
    }
}
std::size_t DataFrame::rows() const noexcept { return row_count_; }
std::size_t DataFrame::cols() const noexcept { return columns_.size(); }
bool DataFrame::empty() const noexcept { return row_count_ == 0; }
const std::vector<std::string>& DataFrame::columns() const noexcept {
    return column_names_;
}
bool DataFrame::has_column(const std::string& name) const noexcept { return std::any_of(columns_.begin(), columns_.end(), [&](const Series& s){ return s.name() == name; }); }
std::size_t DataFrame::column_index(const std::string& name) const {
    for (std::size_t i = 0; i < columns_.size(); ++i) if (columns_[i].name() == name) return i;
    throw std::out_of_range("unknown column: " + name);
}
const Series& DataFrame::column(const std::string& name) const { return columns_.at(column_index(name)); }
Series& DataFrame::column(const std::string& name) { return columns_.at(column_index(name)); }
Value DataFrame::at(std::size_t row, const std::string& name) const { return column(name).at(row); }
void DataFrame::set(std::size_t row, const std::string& name, Value value) { column(name).at(row) = std::move(value); }
void DataFrame::add_column(const std::string& name, std::vector<Value> values) {
    if (name.empty()) throw std::invalid_argument("column name cannot be empty");
    if (has_column(name)) throw std::invalid_argument("duplicate column: " + name);
    if (!columns_.empty() && values.size() != row_count_) throw std::invalid_argument("column length does not match rows");
    if (columns_.empty()) row_count_ = values.size();
    columns_.emplace_back(name, std::move(values));
    column_names_.push_back(name);
}
DataFrame DataFrame::select(const std::vector<std::string>& names) const {
    std::vector<std::vector<Value>> rows(row_count_);
    for (const auto& name : names) { const auto& col = column(name); for (std::size_t r = 0; r < row_count_; ++r) rows[r].push_back(col.at(r)); }
    return DataFrame(names, std::move(rows));
}
DataFrame DataFrame::slice(std::size_t begin, std::size_t end) const {
    if (begin > end || end > row_count_) throw std::out_of_range("invalid dataframe slice");
    std::vector<std::vector<Value>> rows; for (std::size_t r = begin; r < end; ++r) { std::vector<Value> row; for (const auto& col : columns_) row.push_back(col.at(r)); rows.push_back(std::move(row)); }
    return DataFrame(columns(), std::move(rows));
}
DataFrame DataFrame::filter(const std::string& name, const std::function<bool(const Value&)>& predicate) const {
    std::vector<std::vector<Value>> rows; const auto& key = column(name);
    for (std::size_t r = 0; r < row_count_; ++r) if (predicate(key.at(r))) { std::vector<Value> row; for (const auto& col : columns_) row.push_back(col.at(r)); rows.push_back(std::move(row)); }
    return DataFrame(columns(), std::move(rows));
}
DataFrame DataFrame::sort_by(const std::string& name, bool ascending) const {
    const auto& key = column(name); std::vector<std::size_t> order(row_count_); for (std::size_t i=0;i<row_count_;++i) order[i]=i;
    std::stable_sort(order.begin(), order.end(), [&](auto a, auto b){ const auto& x=key.at(a); const auto& y=key.at(b); bool less;
        if (is_numeric(x) && is_numeric(y)) less=as_number(x)<as_number(y); else less=value_to_string(x)<value_to_string(y); return ascending ? less : (!less && x!=y); });
    std::vector<std::vector<Value>> rows; for (auto r : order) { std::vector<Value> row; for (const auto& col : columns_) row.push_back(col.at(r)); rows.push_back(std::move(row)); }
    return DataFrame(columns(), std::move(rows));
}
DataFrame DataFrame::with_column(const std::string& name, const std::function<Value(const std::vector<Value>&)>& op) const {
    std::vector<Value> values; values.reserve(row_count_);
    for (std::size_t r=0;r<row_count_;++r) { std::vector<Value> row; for (const auto& col:columns_) row.push_back(col.at(r)); values.push_back(op(row)); }
    std::vector<std::string> names=columns(); std::vector<std::vector<Value>> rows(row_count_);
    for(std::size_t r=0;r<row_count_;++r){for(const auto& col:columns_) rows[r].push_back(col.at(r));}
    if(has_column(name)){auto it=std::find(names.begin(),names.end(),name); auto idx=static_cast<std::size_t>(it-names.begin()); for(std::size_t r=0;r<row_count_;++r) rows[r][idx]=values[r];}
    else {names.push_back(name); for(std::size_t r=0;r<row_count_;++r) rows[r].push_back(values[r]);}
    return DataFrame(std::move(names),std::move(rows));
}
std::string DataFrame::to_string() const {
    std::ostringstream out; for(std::size_t c=0;c<cols();++c){if(c)out<<"\t";out<<columns_[c].name();} out<<"\n";
    for(std::size_t r=0;r<row_count_;++r){for(std::size_t c=0;c<cols();++c){if(c)out<<"\t";out<<value_to_string(columns_[c].at(r));}out<<"\n";} return out.str();
}
DataFrame melt(const DataFrame& frame, const std::vector<std::string>& id_columns,
               const std::vector<std::string>& value_columns,
               const std::string& variable_name, const std::string& value_name) {
    if (variable_name.empty() || value_name.empty() || variable_name == value_name)
        throw std::invalid_argument("melt output column names must be distinct and non-empty");
    if (value_columns.empty()) throw std::invalid_argument("melt requires at least one value column");
    std::vector<std::string> output_names = id_columns;
    if (std::find(output_names.begin(), output_names.end(), variable_name) != output_names.end() ||
        std::find(output_names.begin(), output_names.end(), value_name) != output_names.end())
        throw std::invalid_argument("melt output names conflict with id columns");
    output_names.push_back(variable_name);
    output_names.push_back(value_name);
    std::vector<std::vector<Value>> output_rows;
    for (const auto& name : id_columns) (void)frame.column(name);
    for (const auto& name : value_columns) (void)frame.column(name);
    for (std::size_t row = 0; row < frame.rows(); ++row) {
        for (const auto& value_column : value_columns) {
            std::vector<Value> output;
            for (const auto& id : id_columns) output.push_back(frame.at(row, id));
            output.push_back(value_column);
            output.push_back(frame.at(row, value_column));
            output_rows.push_back(std::move(output));
        }
    }
    return DataFrame(std::move(output_names), std::move(output_rows));
}
} // namespace codemasterspandas
