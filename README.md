# CODEMASTERS Group 1 Pandas

A C++17 data-analysis library inspired by common Pandas-style operations. The project provides reusable classes and functions for storing tabular data, selecting and transforming values, calculating statistics, reading and writing CSV/JSON files, and testing the behaviour of the library.

## Project Objectives

The project demonstrates object-oriented programming and generic programming in C++ while solving practical data-analysis tasks. It applies classes, inheritance, polymorphism, function templates, file handling, exceptions, STL containers, lambdas, and modular program design.

## Main Features

- `Value` type for storing integers, floating-point values, Boolean values, strings, and missing values.
- `Series` for one-dimensional labelled data.
- `DataFrame` for rows and columns of data.
- Column selection, row slicing, filtering, sorting, and derived columns.
- Wide-to-long reshaping using `melt()`.
- Statistical functions including count, sum, minimum, maximum, mean, median, standard deviation, percentile, quantile, and correlation.
- Grouped aggregation using group count, sum, minimum, and maximum.
- Data transformations including normalization, standardization, type conversion, trimming, uppercase, and lowercase operations.
- CSV and JSON reading and writing.
- Inheritance and polymorphism through `DataExporter`, `CSVExporter`, and `JSONExporter`.
- A numerical function template that works with `short`, `int`, `float`, and `double`.
- Automated tests for the main library behaviour.

## Project Structure

```text
CODEMASTERS-GROUP1-PANDAS/
├── include/codemasterspandas/   # Public header files
├── src/                         # Library implementations
├── examples/                    # Usage examples
├── tests/                       # Automated and extended tests
├── data/input/                  # Sample CSV and JSON datasets
├── data/output/                 # Generated output files
├── docs/                        # Module and branch documentation
├── reports/                     # Group and individual reports
├── CMakeLists.txt               # Main CMake build file
└── README.md
```

## Requirements

- A C++17-compatible compiler.
- CMake 3.16 or newer for the CMake build.
- GCC 8 or newer is recommended; newer GCC versions are preferred.

The project uses features such as `std::variant`, so very old compilers that do not fully support C++17 will not compile the project.

## Build with CMake

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

To run the registered automated test:

```bash
ctest --test-dir build --output-on-failure
```

## Direct Compilation with g++

The main library test can also be compiled directly:

```bash
g++ -std=c++17 -Iinclude src/value.cpp src/series.cpp src/dataframe.cpp src/statistics.cpp src/transform.cpp src/io.cpp tests/test_library.cpp -o test_library
```

On Windows with MinGW, the executable can then be run with:

```powershell
.\test_library.exe
```

## Basic Usage

```cpp
#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>

using namespace codemasterspandas;

int main()
{
    DataFrame frame(
        {"name", "score"},
        {
            {std::string("Amina"), 88.0},
            {std::string("Brian"), 74.0},
            {std::string("Diana"), 91.0}
        }
    );

    std::cout << frame.to_string();
    std::cout << "Mean score: " << mean(frame.column("score")) << '\n';
}
```

More examples are available in the `examples/` directory.

## Templates

The statistics module contains a function template:

```cpp
template <typename T>
double numeric_mean(const std::vector<T>& data);
```

The template avoids writing separate mean functions for every numerical type. The same implementation can be used with types such as:

```cpp
std::vector<short>
std::vector<int>
std::vector<float>
std::vector<double>
```

The template uses `std::is_arithmetic_v<T>` to restrict it to arithmetic data types.

## Inheritance and Polymorphism

The input/output module demonstrates inheritance and runtime polymorphism:

```text
           DataExporter
                ^
          ______|______
         |             |
   CSVExporter    JSONExporter
```

`DataExporter` defines the common virtual interface `exportData()`. `CSVExporter` and `JSONExporter` override that function to export a `DataFrame` in different file formats. A `DataExporter*` can therefore call either derived implementation through the same interface.

## Testing

The main automated test is `tests/test_library.cpp`. It checks important behaviour across the project, including:

- DataFrame dimensions, filtering, sorting, derived columns, and reshaping.
- Series slicing.
- Statistical calculations and grouped aggregation.
- The numerical template with `short`, `int`, `float`, and `double`.
- Data transformation operations.
- CSV and JSON round-trip operations.
- Inheritance and polymorphism using the exporter classes.
- Exception handling for invalid operations.

Additional test source files in `tests/` can be used for extended testing.

## Sample Data

The `data/input/` directory contains sample CSV and JSON datasets that can be used when demonstrating or testing the library.

## Group Contributions

| Member | Main Contribution |
| --- | --- |
| Abalo Proscovia | `Value` and `Series`: typed values, indexing, slicing, mapping, and filtering |
| Aguti Jemimah | `DataFrame`: storage, selection, filtering, sorting, slicing, and derived columns |
| Halima Ganyana | CSV/JSON I/O, parser handling, inheritance, and polymorphism |
| Mukose Divine | Statistics, correlation, grouped aggregation, and numerical templates |
| Ninsiima Arthur | Type conversion, normalization, standardization, and string transformations |
| Robertbob Murungi | Testing, sample datasets, usage examples, and integration verification |
| Mike | Integration, CMake/build organisation, review, and project documentation |

## OOP Concepts Demonstrated

The project demonstrates:

- Encapsulation through classes such as `Series` and `DataFrame`.
- Inheritance through the exporter class hierarchy.
- Polymorphism through virtual `exportData()` calls.
- Function templates for numerical type independence.
- Exception handling for invalid data operations.
- STL containers, algorithms, and lambda expressions.

## License

See the `LICENSE` file in the repository.
