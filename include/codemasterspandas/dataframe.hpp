#pragma once

#include "codemasterspandas/series.hpp"
#include <cstddef>
#include <functional>
#include <string>
#include <vector>

namespace codemasterspandas {

/// A rectangular table whose columns all have the same number of rows.
class DataFrame {
public:
    DataFrame() = default;
    DataFrame(std::vector<std::string> columns, std::vector<std::vector<Value>> rows);
    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;
    bool empty() const noexcept;
    const std::vector<std::string>& columns() const noexcept;
    bool has_column(const std::string& name) const noexcept;
    const Series& column(const std::string& name) const;
    Series& column(const std::string& name);
    Value at(std::size_t row, const std::string& name) const;
    void set(std::size_t row, const std::string& name, Value value);
    void add_column(const std::string& name, std::vector<Value> values);
    DataFrame select(const std::vector<std::string>& names) const;
    DataFrame slice(std::size_t begin, std::size_t end) const;
    DataFrame filter(const std::string& name,
                     const std::function<bool(const Value&)>& predicate) const;
    DataFrame sort_by(const std::string& name, bool ascending = true) const;
    DataFrame with_column(const std::string& name,
                          const std::function<Value(const std::vector<Value>&)>& operation) const;
    std::string to_string() const;

private:
    std::vector<Series> columns_;
    std::vector<std::string> column_names_;
    std::size_t row_count_ = 0;
    std::size_t column_index(const std::string& name) const;
};

/// Convert selected wide columns into variable/value rows while retaining id columns.
DataFrame melt(const DataFrame& frame, const std::vector<std::string>& id_columns,
               const std::vector<std::string>& value_columns,
               const std::string& variable_name = "variable",
               const std::string& value_name = "value");

} // namespace codemasterspandas
