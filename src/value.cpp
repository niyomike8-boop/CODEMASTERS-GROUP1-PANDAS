#include "codemasterspandas/value.hpp"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace codemasterspandas {
std::string value_to_string(const Value& value) {
    if (std::holds_alternative<std::monostate>(value)) return "";
    if (const auto* text = std::get_if<std::string>(&value)) return *text;
    if (const auto* boolean = std::get_if<bool>(&value)) return *boolean ? "true" : "false";
    if (const auto* integer = std::get_if<std::int64_t>(&value)) return std::to_string(*integer);
    std::ostringstream out; out << std::setprecision(15) << std::get<double>(value); return out.str();
}
bool is_numeric(const Value& value) {
    return std::holds_alternative<std::int64_t>(value) || std::holds_alternative<double>(value);
}
double as_number(const Value& value) {
    if (const auto* integer = std::get_if<std::int64_t>(&value)) return static_cast<double>(*integer);
    if (const auto* number = std::get_if<double>(&value)) return *number;
    throw std::invalid_argument("value is not numeric");
}
Value parse_value(const std::string& text) {
    if (text.empty()) return std::monostate{};
    std::string lower = text;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    if (lower == "true") return true;
    if (lower == "false") return false;
    try { std::size_t used = 0; auto n = std::stoll(text, &used); if (used == text.size()) return static_cast<std::int64_t>(n); } catch (...) {}
    try { std::size_t used = 0; auto n = std::stod(text, &used); if (used == text.size()) return n; } catch (...) {}
    return text;
}
} // namespace codemasterspandas
