# CODEMASTERS GROUP 1 – PANDAS
## Final Project Report

**Project:** C++17 Data-Analysis Library  
**Repository:** `niyomike8-boop/CODEMASTERS-GROUP1-PANDAS`  
**Project group:** CODEMASTERS Group 1  
**Reporting status:** Final project report  
**Prepared :** GROUP LEADER NIYONSABA MICHAEL


---

## 1. Executive Summary

CODEMASTERS Group 1 Pandas is a modular data-analysis library developed in C++17. It is inspired by common tabular-data operations found in tools such as Python Pandas. The project provides reusable components for representing individual data values, organising values into named series and data frames, manipulating tabular records, calculating descriptive statistics, transforming data, and reading and writing CSV and JSON files.

The project was designed to demonstrate the practical application of object-oriented programming, generic programming, standard template library (STL) containers and algorithms, file handling, exception handling, modular design, and software testing.

The repository contains public header files, implementation files, examples, sample datasets, tests, project documentation, and group progress reports. The implementation brings the major modules together in a shared CMake-based C++17 project.

This report describes the project scope, design, implementation, programming concepts, testing resources, documented group responsibilities, limitations, and recommended final verification activities. It distinguishes implemented features from verification steps that still require recorded test evidence.

## 2. Introduction and Background

Data analysis commonly involves storing structured records, selecting relevant fields, filtering rows, sorting information, calculating summary statistics, and exporting results for further use. Libraries such as Pandas provide these operations in Python. This project applies selected similar ideas in C++ to strengthen the group's understanding of data structures, reusable software components, and practical programming.

The resulting library is intended as an educational implementation of selected data-analysis operations. It is not a complete replacement for Python Pandas and does not aim to implement every feature of a production data-analysis framework.

## 3. Project Aim and Objectives

### 3.1 Aim

To design and implement a reusable C++17 library that supports fundamental tabular-data storage, manipulation, transformation, statistical analysis, and CSV/JSON file operations.

### 3.2 Specific Objectives

The project set out to:

1. Create a flexible value representation supporting different data types and missing values.
2. Implement a `Series` class for named, ordered one-dimensional data.
3. Implement a `DataFrame` class for structured tabular data.
4. Provide operations for selecting, slicing, filtering, sorting, reshaping, and deriving columns.
5. Implement descriptive statistical functions and grouped aggregation.
6. Provide data-cleaning and transformation functions.
7. Read and write datasets in CSV and JSON formats.
8. Demonstrate encapsulation, inheritance, polymorphism, templates, and exception handling.
9. Provide sample datasets, practical usage examples, and automated test programs.
10. Organise the code as a modular project that can be built using CMake and a C++17-compatible compiler.

## 4. Project Scope and Main Features

The implemented library provides the following principal capabilities.

| Component | Main capabilities |
|---|---|
| `Value` | Represents missing values, integers, floating-point numbers, Booleans, and strings |
| `Series` | Named ordered values, checked indexing, slicing, mapping, and filtering |
| `DataFrame` | Tabular storage, column access, selection, slicing, filtering, sorting, and derived columns |
| Reshaping | Wide-to-long conversion using `melt()` |
| Statistics | Count, sum, minimum, maximum, mean, median, standard deviation, quantile, percentile, and correlation |
| Grouped analysis | Group count, sum, minimum, and maximum |
| Transformations | Normalization, standardization, numeric conversion, string conversion, uppercase, lowercase, and trimming |
| File input/output | CSV and JSON reading and writing |
| Exporter hierarchy | CSV and JSON exporters using a common base-class interface |
| Generic programming | Numerical mean template supporting arithmetic types |
| Error handling | Standard exceptions for invalid columns, indices, inputs, and unsupported operations |

## 5. System Design and Architecture

The project follows a modular design. Public declarations are located in `include/codemasterspandas/`, while corresponding implementations are located in `src/`.

```text
CODEMASTERS-GROUP1-PANDAS
|
+-- include/codemasterspandas/
|   +-- value.hpp
|   +-- series.hpp
|   +-- dataframe.hpp
|   +-- statistics.hpp
|   +-- transform.hpp
|   +-- io.hpp
|   +-- codemasterspandas.hpp
|
+-- src/
|   +-- value.cpp
|   +-- series.cpp
|   +-- dataframe.cpp
|   +-- statistics.cpp
|   +-- transform.cpp
|   +-- io.cpp
|
+-- examples/
+-- tests/
+-- data/
|   +-- input/
|   +-- output/
|
+-- docs/
+-- reports/
+-- CMakeLists.txt
+-- README.md
```

The umbrella header, `codemasterspandas.hpp`, includes the public module headers so that a user can access the library through one main include.

### 5.1 Value Module

The `Value` type is implemented using `std::variant`. It supports:

- Missing values represented by `std::monostate`.
- Integer values represented by `std::int64_t`.
- Floating-point values represented by `double`.
- Boolean values.
- String values.

Helper functions provide string conversion, numeric type checking, numeric extraction, and basic parsing.

### 5.2 Series Module

The `Series` class represents a named sequence of values. Its principal operations include:

- Retrieving the series name and size.
- Checking whether the series is empty.
- Accessing values by index using bounds-checked access.
- Extracting a selected range using `slice()`.
- Applying an operation to every value using `map()`.
- Selecting values that satisfy a predicate using `filter()`.

The class encapsulates its name and stored values, exposing operations through its public interface.

### 5.3 DataFrame Module

The `DataFrame` class represents a table consisting of named columns. It maintains a consistent row count across columns and provides:

- Construction from column names and row data.
- Row and column counts.
- Column existence checks and access by name.
- Accessing and updating individual cells.
- Adding columns.
- Selecting specified columns.
- Slicing a range of rows.
- Filtering rows using a predicate.
- Sorting by a selected column.
- Creating or replacing a derived column using `with_column()`.
- Displaying the table in a readable text format.

The `melt()` operation converts selected wide-format columns into variable/value rows while retaining identifier columns.

### 5.4 Statistics Module

The statistics module implements descriptive and relational calculations, including:

- `count()`
- `sum()`
- `minimum()`
- `maximum()`
- `mean()`
- `median()`
- `standard_deviation()`
- `quantile()`
- `percentile()`
- `correlation()`

It also provides grouped operations:

- `group_count()`
- `group_sum()`
- `group_min()`
- `group_max()`

The implementation generally uses integer and floating-point values for numeric calculations. Missing and non-numeric values are excluded from the numeric extraction used by the aggregate functions. The standard-deviation function supports population and sample calculations, with population standard deviation as the default.

### 5.5 Transformation Module

The transformation module supports common data-cleaning and scaling operations:

- `normalize()` rescales numeric values to the range from 0 to 1.
- `standardize()` transforms numeric values using the mean and population standard deviation.
- `to_numeric()` converts parseable values to numeric values and marks unparseable values as missing.
- `to_string_series()` converts non-missing values to strings.
- `lowercase()` converts string values to lowercase.
- `uppercase()` converts string values to uppercase.
- `trim_strings()` removes leading and trailing whitespace from string values.

For constant numeric data, normalization and standardization return zero for numeric entries rather than dividing by zero.

### 5.6 Input and Output Module

The I/O module provides:

- `read_csv()` and `write_csv()` for CSV files.
- `read_json()` and `write_json()` for JSON files.

The CSV implementation handles common quoted fields, commas inside quoted values, and escaped quotation marks. The JSON implementation supports an array of objects containing scalar values.

The module also demonstrates an exporter class hierarchy. `DataExporter` defines a virtual `exportData()` interface, while `CSVExporter` and `JSONExporter` provide format-specific implementations.

## 6. Object-Oriented and Generic Programming Concepts

### 6.1 Encapsulation

Encapsulation is demonstrated by classes such as `Series` and `DataFrame`. Their internal data members are private, while public member functions provide controlled access and modification.

### 6.2 Inheritance

The exporter classes demonstrate inheritance:

```text
             DataExporter
                  |
          +-------+-------+
          |               |
     CSVExporter     JSONExporter
```

`CSVExporter` and `JSONExporter` derive from `DataExporter` and implement its export interface.

### 6.3 Polymorphism

The `exportData()` function is virtual in the base class and overridden in the derived classes. A pointer or reference to `DataExporter` can therefore invoke the appropriate CSV or JSON implementation at runtime.

### 6.4 Templates

The statistics header contains the function template:

```cpp
template <typename T>
double numeric_mean(const std::vector<T>& data);
```

The template supports arithmetic types without requiring a separate implementation for each numeric type. A compile-time `static_assert` using `std::is_arithmetic_v<T>` restricts the accepted type category.

### 6.5 Exception Handling

The library uses standard exceptions to report invalid operations. Examples include invalid column names, out-of-range indices or slices, invalid quantile arguments, incompatible data dimensions, and operations that require numeric values when none are available.

### 6.6 STL and Lambda Expressions

The implementation uses standard library facilities including `std::vector`, `std::variant`, `std::map`, algorithms such as `std::sort` and `std::stable_sort`, and lambda expressions for filtering, mapping, sorting, and transformations.

## 7. Sample Data and Practical Examples

The repository contains sample datasets under `data/input/`, including employee and student-related CSV/JSON data. These datasets are intended for demonstration and testing.

The examples demonstrate how a user can:

1. Include the public library header.
2. Load a dataset from a CSV file.
3. display a DataFrame.
4. Select relevant columns.
5. Filter high-performing records.
6. Sort records by salary or another numeric field.
7. Calculate summary statistics.
8. Group records by department.
9. Export filtered results to CSV and JSON.

For example, `examples/employee_analysis.cpp` demonstrates employee-data analysis using the sample employee dataset. The example calculates salary statistics, identifies high performers, counts employees by department, calculates departmental payroll totals, and exports filtered records.

## 8. Testing and Quality Assurance

The repository contains three test source files:

- `tests/test_library.cpp`
- `tests/test_edge_cases.cpp`
- `tests/test_transform.cpp`

The main test program covers functionality across the integrated modules, including DataFrame operations, Series slicing, statistics, grouped aggregation, numerical templates, transformations, CSV/JSON round trips, exporter polymorphism, and exception handling.

The edge-case test program includes checks for situations such as filters with no matching rows, invalid percentile values, constant-value normalization, invalid numeric conversion, missing input files, malformed CSV row widths, quoted commas, and invalid correlation inputs.

The transformation test program provides additional checks for data transformation behaviour.

### 8.1 Build and Test Commands

The project is configured for C++17 and uses CMake. From the repository root, the documented build commands are:

```bash
cmake -S . -B build
cmake --build build
```

The registered CTest suite can be run using:

```bash
ctest --test-dir build --output-on-failure
```

### 8.2 Verification Status and Evidence

The presence of test source files does not, by itself, prove that every test has been compiled and executed. The current `CMakeLists.txt` registers `tests/test_library.cpp` as the CTest test executable. The additional edge-case and transformation test source files are present in the repository but are not currently registered as separate CTest targets in that configuration.


## 9. Group Responsibilities and Contributions

The README documents the following main areas of responsibility:

| Member | Documented contribution area |
|---|---|
| Abalo Proscovia | `Value` and `Series`: typed values, indexing, slicing, mapping, and filtering |
| Aguti Jemimah | `DataFrame`: tabular storage, selection, filtering, sorting, slicing, and derived columns |
| Halima Ganyana | CSV/JSON input/output, parser behaviour, inheritance, and polymorphism |
| Mukose Divine | Statistics, correlation, grouped aggregation, and numerical templates |
| Ninsiima Arthur | Type conversion, normalization, standardization, and string transformations |
| Robertbob Murungi | Testing, sample datasets, usage examples, and integration verification |
| Niyonsaba Michael (Mike) | Integration, build organisation, review, CMake, and project documentation |

This table records the responsibilities and contribution areas documented by the group. Individual contribution claims should be supported during assessment by the corresponding commits, pull requests, source files, reports, and other repository evidence.

## 10. Development Workflow and Repository Organisation

The project is maintained in the shared GitHub repository:

`https://github.com/niyomike8-boop/CODEMASTERS-GROUP1-PANDAS`

The repository separates public headers, source implementations, examples, tests, input datasets, documentation, and reports. This structure helps keep implementation code separate from demonstration material and project records.

The group used Git and GitHub to maintain the shared codebase and integrate changes. Branches and pull requests provide a way to organise individual work and review changes before integration.

During final repository cleanup, generated CMake build files were removed from Git tracking. Such files are produced locally during configuration and compilation and should generally not be committed as part of the source repository. The `.gitignore` file includes build directories and common compiled artefacts.

The final `main` branch should be treated as the group's submission version. Before hand-in, the group should confirm that it contains all required source files, examples, tests, sample data, and final documentation.



## 12. Recommendations and Future Work

Future development could improve the library by:

- Expanding CSV parsing to support multiline quoted fields.
- Extending JSON support to nested arrays and objects.
- Adding more statistical and grouped operations.
- Improving numeric validation and handling of NaN and infinity.
- Defining and testing consistent sorting behaviour for mixed and missing values.
- Adding more comprehensive unit and integration tests.
- Registering every test program with CTest.
- Adding continuous integration to build and test the project automatically when changes are pushed.
- Improving API documentation and providing more usage examples.
- Conducting and recording a clean build and test on a machine outside the development group, if required by the assignment brief.




## 14. Conclusion

CODEMASTERS Group 1 Pandas has produced a modular C++17 data-analysis library that brings together data representation, Series and DataFrame structures, statistical operations, data transformations, CSV/JSON input and output, inheritance, polymorphism, templates, and exception handling.

The project provides practical examples and sample datasets to demonstrate how the library can be used. Its modular structure separates public interfaces from implementation files and provides a foundation for further development.

The work demonstrates the application of core C++ programming concepts to a practical data-processing problem. Final submission readiness should be established by completing the outstanding build, test-registration, and verification activities and retaining evidence of the actual results.

---

**End of Report**

**Repository:** `niyomike8-boop/CODEMASTERS-GROUP1-PANDAS`  
**Project:** CODEMASTERS Group 1 – Pandas
