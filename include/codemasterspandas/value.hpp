#pragma once

#include <cstdint>
#include <string>
#include <variant>

namespace codemasterspandas {

/// A cell value. std::monostate represents a missing value.
using Value = std::variant<std::monostate, std::int64_t, double, bool, std::string>;

/// Convert a value to a display string (missing values become an empty string).
std::string value_to_string(const Value& value);
/// Return true when a value is numeric (integer or floating point).
bool is_numeric(const Value& value);
/// Convert a numeric value to double; throws std::invalid_argument otherwise.
double as_number(const Value& value);
/// Parse a simple scalar string as integer, double, Boolean, or string.
Value parse_value(const std::string& text);

} // namespace codemasterspandas
