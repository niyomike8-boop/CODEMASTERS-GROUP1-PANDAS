#include "codemasterspandas/series.hpp"
#include <stdexcept>

namespace codemasterspandas {
Series::Series(std::string name, std::vector<Value> values) : name_(std::move(name)), values_(std::move(values)) {
    if (name_.empty()) throw std::invalid_argument("series name cannot be empty");
}
const std::string& Series::name() const noexcept { return name_; }
std::size_t Series::size() const noexcept { return values_.size(); }
bool Series::empty() const noexcept { return values_.empty(); }
const std::vector<Value>& Series::values() const noexcept { return values_; }
const Value& Series::at(std::size_t index) const { return values_.at(index); }
Value& Series::at(std::size_t index) { return values_.at(index); }
Series Series::slice(std::size_t begin, std::size_t end) const {
    if (begin > end || end > size()) throw std::out_of_range("invalid series slice");
    return Series(name_, {values_.begin() + static_cast<std::ptrdiff_t>(begin), values_.begin() + static_cast<std::ptrdiff_t>(end)});
}
Series Series::map(const std::function<Value(const Value&)>& operation) const {
    std::vector<Value> output; output.reserve(size());
    for (const auto& item : values_) output.push_back(operation(item));
    return Series(name_, std::move(output));
}
std::vector<Value> Series::filter(const std::function<bool(const Value&)>& predicate) const {
    std::vector<Value> output; for (const auto& item : values_) if (predicate(item)) output.push_back(item); return output;
}
} // namespace codemasterspandas
