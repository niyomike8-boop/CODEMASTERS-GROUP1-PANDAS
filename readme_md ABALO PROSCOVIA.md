# CodeMastersPandas

A lightweight C++ library inspired by Pandas for managing dynamic, strongly-typed series data using C++17 variant types.

---

## 📌 Overview

**CodeMastersPandas** provides data structure primitives to store, manipulate, and transform heterogeneous data series. It utilizes `std::variant` (`Value`) to dynamically handle basic data types—such as integers, floating-point numbers, booleans, strings, and missing values (`monostate`)—while maintaining memory safety and clean C++ ergonomics.

---

## 🛠 Features

* **Flexible Value Representation (`Value`)**:
  * Supports `std::monostate` (representing null/missing data), `bool`, `std::int64_t`, `double`, and `std::string`.
  * Type-safe extraction, conversion to string, and numeric checks.
  * String parsing engine to automatically deduce data types from text strings.

* **Series Data Structure (`Series`)**:
  * Named collection of `Value` items.
  * Bounds-checked element access and range slicing.
  * Functional operations: higher-order mapping (`map`) and predicate filtering (`filter`).
  * Strict validation (e.g., non-empty series names, safe boundary checks).

---

## 🚀 Getting Started

### Prerequisites

* C++17 compatible compiler (e.g., `GCC 7+`, `Clang 5+`, or `MSVC 2017+`)
* Standard C++ Library (`<variant>`, `<vector>`, `<string>`, `<functional>`, `<algorithm>`)

---

## 💡 Usage Examples

### 1. Working with `Value`

```cpp
#include "codemasterspandas/value.hpp"
#include <iostream>

using namespace codemasterspandas;

int main() {
    // Parsing values from raw text strings
    Value val1 = parse_value("12345");       // Parsed as std::int64_t
    Value val2 = parse_value("3.14159");     // Parsed as double
    Value val3 = parse_value("true");        // Parsed as bool
    Value val4 = parse_value("");            // Parsed as std::monostate (null)

    // Check if numeric and extract double
    if (is_numeric(val1)) {
        double num = as_number(val1);        // Converts int64_t or double to double
        std::cout << "Numeric value: " << num << "\n";
    }

    // String formatting
    std::cout << "String form: " << value_to_string(val2) << "\n";
}
```

### 2. Working with `Series`

```cpp
#include "codemasterspandas/series.hpp"
#include <iostream>

using namespace codemasterspandas;

int main() {
    // Constructing a Series
    std::vector<Value> raw_data = {
        int64_t{10},
        int64_t{20},
        int64_t{30},
        int64_t{40}
    };

    Series series("Metrics", raw_data);

    // Metadata & Access
    std::cout << "Series Name: " << series.name() << "\n";
    std::cout << "Series Size: " << series.size() << "\n";
    std::cout << "First Element: " << value_to_string(series.at(0)) << "\n";

    // Slice a range [1, 3)
    Series sub_series = series.slice(1, 3);

    // Map operation (e.g., doubling numeric values)
    Series doubled = series.map([](const Value& v) -> Value {
        if (is_numeric(v)) {
            return as_number(v) * 2.0;
        }
        return v;
    });

    // Filter operation (e.g., keep elements > 15)
    std::vector<Value> filtered = series.filter([](const Value& v) {
        return is_numeric(v) && as_number(v) > 15.0;
    });
}
```

---

## 🏛 Architecture & API Reference

### `value.hpp` / `value.cpp`

* `using Value = std::variant<std::monostate, std::string, bool, std::int64_t, double>;`
* `std::string value_to_string(const Value& value)`: Converts any variant type into its string representation.
* `bool is_numeric(const Value& value)`: Returns `true` if variant holds `int64_t` or `double`.
* `double as_number(const Value& value)`: Casts numeric variants to `double`; throws `std::invalid_argument` if non-numeric.
* `Value parse_value(const std::string& text)`: Automatically parses string input into the most specific type possible.

### `series.hpp` / `series.cpp`

* `Series(std::string name, std::vector<Value> values)`: Constructs a series. Throws `std::invalid_argument` if `name` is empty.
* `const std::string& name() const noexcept`: Returns series identifier.
* `std::size_t size() const noexcept`: Returns item count.
* `bool empty() const noexcept`: Returns `true` if series contains no elements.
* `const Value& at(std::size_t index) const`: Accesses element with bounds checking.
* `Series slice(std::size_t begin, std::size_t end) const`: Returns a sub-series within range `[begin, end)`. Throws `std::out_of_range` on invalid range.
* `Series map(const std::function<Value(const Value&)>& operation) const`: Applies transformation across all elements.
* `std::vector<Value> filter(const std::function<bool(const Value&)>& predicate) const`: Returns array of items satisfying predicate.

---

## 📝 License

This project is licensed under the MIT License - see the LICENSE file for details.