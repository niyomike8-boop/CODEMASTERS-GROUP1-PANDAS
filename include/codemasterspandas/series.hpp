#pragma once

#include "codemasterspandas/value.hpp"
#include <cstddef>
#include <functional>
#include <string>
#include <vector>

namespace codemasterspandas {

/// One named, ordered column of values.
class Series {
public:
    Series(std::string name, std::vector<Value> values = {});
    const std::string& name() const noexcept;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    const std::vector<Value>& values() const noexcept;
    const Value& at(std::size_t index) const;
    Value& at(std::size_t index);
    Series slice(std::size_t begin, std::size_t end) const;
    Series map(const std::function<Value(const Value&)>& operation) const;
    std::vector<Value> filter(const std::function<bool(const Value&)>& predicate) const;

private:
    std::string name_;
    std::vector<Value> values_;
};

} // namespace codemasterspandas
