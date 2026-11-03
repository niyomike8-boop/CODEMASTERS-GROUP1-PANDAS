# CODEMASTERS Group 1 Pandas — Final Group Report

## 1. Project Overview

CODEMASTERS Group 1 Pandas is a C++17 data-analysis library inspired by common operations found in tabular-data tools such as Pandas. The project was developed to demonstrate object-oriented programming, generic programming, file handling, STL use, exception handling, testing, and team-based software development.

The library can represent values and columns, store tabular datasets, filter and sort rows, calculate statistics, transform data, read and write CSV/JSON files, and verify behaviour through automated tests.

## 2. Objectives

The main objectives of the project were to:

1. Design a modular C++ library for basic data analysis.
2. Apply object-oriented programming concepts including encapsulation, inheritance, and polymorphism.
3. Apply function templates to support multiple numerical data types.
4. Support tabular-data operations such as filtering, sorting, slicing, reshaping, and derived columns.
5. Provide statistical and grouped aggregation operations.
6. Support CSV and JSON input/output.
7. Provide data-cleaning and transformation operations.
8. Test the combined library using normal and error cases.
9. Document the project structure, usage, and individual contributions.

## 3. System Design

The project is organised into reusable modules:

```text
Value
  |
  v
Series
  |
  v
DataFrame
  |
  +-----------------------------+
  |              |              |
  v              v              v
Statistics   Transforms      CSV / JSON I/O
  |                             |
  |                     DataExporter
  |                       /        \
  |                CSVExporter  JSONExporter
  +-----------------------------+
                |
                v
          Tests and Examples
```

### 3.1 Value

`Value` represents an individual data cell. It uses `std::variant` to support missing values, integers, floating-point numbers, Boolean values, and strings.

### 3.2 Series

`Series` represents one named column of ordered values. It supports indexing, slicing, mapping, and filtering.

### 3.3 DataFrame

`DataFrame` stores multiple columns with equal row counts. It supports column selection, row slicing, filtering, sorting, derived columns, and wide-to-long reshaping.

### 3.4 Statistics

The statistics module provides count, sum, minimum, maximum, mean, median, standard deviation, quantile, percentile, correlation, and grouped aggregation functions.

### 3.5 Transformations

The transformation module provides normalization, standardization, numeric conversion, string conversion, uppercase/lowercase conversion, and trimming of strings.

### 3.6 Input and Output

The I/O module supports reading and writing CSV and JSON files. It also demonstrates inheritance and polymorphism through the `DataExporter` hierarchy.

## 4. Object-Oriented Programming Concepts

### 4.1 Encapsulation

Classes such as `Series` and `DataFrame` keep their internal data private and expose controlled public operations.

### 4.2 Inheritance

`CSVExporter` and `JSONExporter` inherit from the abstract base class `DataExporter`.

```text
          DataExporter
               ^
          _____|_____
         |           |
   CSVExporter   JSONExporter
```

### 4.3 Polymorphism

`DataExporter` declares a virtual `exportData()` function. A base-class pointer can refer to either exporter and call the appropriate overridden implementation at runtime.

## 5. Templates and Data Types

The statistics module contains a numerical function template:

```cpp
template <typename T>
double numeric_mean(const std::vector<T>& data);
```

The template reduces duplication by allowing one function to work with different numerical types. The main test verifies the template with:

- `short`
- `int`
- `float`
- `double`

The implementation uses `std::is_arithmetic_v<T>` so the function is restricted to arithmetic types.

## 6. Testing

The primary automated test is `tests/test_library.cpp`. It verifies the integration of the main modules and covers:

- DataFrame creation and dimensions.
- Filtering with matches and without matches.
- Descending sorting.
- Derived columns.
- Wide-to-long reshaping.
- Series slicing.
- Mean, median, standard deviation, percentile, correlation, count, sum, minimum, and maximum.
- Group count, group sum, group minimum, and group maximum.
- Numerical template support for `short`, `int`, `float`, and `double`.
- String trimming and uppercase conversion.
- Normalization, standardization, and numeric conversion.
- CSV and JSON round-trip operations.
- Exporter inheritance and polymorphism.
- Invalid-column, invalid-slice, and invalid-quantile exception handling.

The repository also contains additional test source files for extended testing.

## 7. Sample Data and Examples

Sample datasets are stored in `data/input/`. These include CSV and JSON files that can be used to demonstrate reading, transformation, analysis, and output operations.

Usage examples are stored in `examples/` and show how a user can include the library and perform common operations.

## 8. Group Contributions

| Member | Contribution |
| --- | --- |
| Abalo Proscovia | `Value` and `Series`: typed values, indexing, slicing, mapping, and filtering |
| Aguti Jemimah | `DataFrame`: tabular storage, selection, filtering, sorting, slicing, and derived columns |
| Halima Ganyana | CSV/JSON I/O, parser behaviour, inheritance, and polymorphism |
| Mukose Divine | Statistics, correlation, grouped aggregation, and numerical templates |
| Ninsiima Arthur | Type conversion, normalization, standardization, and string transformations |
| Robertbob Murungi | Testing, sample datasets, usage examples, and integration verification |
| Mike | Integration, build organisation, review, CMake, and overall documentation |

## 9. Building and Running

The project requires a C++17-compatible compiler and CMake 3.16 or newer.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The main test can also be compiled directly with a C++17 compiler.

## 10. External-Machine Validation

The project requirement includes testing the project on a machine belonging to a person who is not part of the development group. The external tester should clone or receive a clean copy of the project, build it using the documented instructions, run the main test, and record the outcome below.

| Item | Result |
| --- | --- |
| External tester name | To be recorded after the actual test |
| Machine / operating system | To be recorded after the actual test |
| Compiler used | To be recorded after the actual test |
| Build successful | To be recorded after the actual test |
| Main automated test result | To be recorded after the actual test |
| Problems observed | To be recorded after the actual test |
| Corrective action, if any | To be recorded after the actual test |

This section must be completed using the real external test result before final hand-in. No external result should be invented.

## 11. Conclusion

The project provides a modular C++17 library for basic tabular-data analysis while demonstrating the main programming concepts required by the course. The final code combines data storage, manipulation, statistics, transformation, file input/output, inheritance, polymorphism, templates, exception handling, examples, and automated testing in one integrated project.
