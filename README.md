# CODEMASTERS-GROUP1-PANDAS
# Value & Series Operations (`codemasterspandas`)

**Author:** Abalo Proscovia  
**Registration Number:** 25/U/26390/PS  
**Program:** Computer and Communications Engineering  
**Date:** October 2026  

---

## 📌 Executive Summary

This repository contains a modular C++ implementation demonstrating core operations on two fundamental data structures in the custom **`codemasterspandas`** library: `Value` (typed cell containers) and `Series` (1D labeled, homogenous/heterogenous sequences). 

The project highlights data representation, indexing, sub-range slicing, and high-order functional manipulations (mapping and filtering) designed for data engineering applications.

---

## 🛠 Project Structure

The codebase is modularized into five distinct source files based on operational categories:

| File Name | Category | Primary Functionality |
| :--- | :--- | :--- |
| `typed_cells_demo.cpp` | **Typed Cells** | Demonstrates `Value` initialization across scalar primitives (`int`, `double`, `std::string`). |
| `series_creation_indexing.cpp` | **Series Indexing** | Demonstrates creation of `Series` containers and zero-based position indexing (`.at()`). |
| `series_slicing.cpp` | **Slicing Operations** | Isolates sub-ranges from a `Series` using half-open intervals `[start, stop)`. |
| `series_mapping.cpp` | **Functional Mapping** | Applies element-wise transformations across a `Series` using lambda expressions. |
| `series_filtering.cpp` | **Predicate Filtering** | Evaluates elements against a boolean predicate to generate subset collections. |

---

## 🚀 Key Implementations & Concepts

### 1. Typed Cell Containers (`Value`)
The `Value` class acts as a flexible type wrapper capable of holding multiple scalar data types safely within a single abstraction layer.
* **File:** `typed_cells_demo.cpp`
* **Supported Types:** Integers, Floating-point numbers, Standard Strings.

### 2. Series Creation & Explicit Indexing
A `Series` represents a 1D sequence of values. Explicit element lookup is achieved using position-based indexing through `.at(index)`.
* **File:** `series_creation_indexing.cpp`
* **Access Safety:** Bound checking and conversion through conversion functions such as `as_number()`.

### 3. Slicing Operations
The `.slice(start, stop)` operation enables non-destructive Extraction of a sub-range of data.
* **File:** `series_slicing.cpp`
* **Behavior:** Operates with a closed start index and open end index (`[1, 4)` captures indices 1, 2, and 3).

### 4. Mapping Transformations
The `.map()` function allows high-order processing by accepting a callable target (e.g., C++ Lambda) to transform each element individually.
* **File:** `series_mapping.cpp`
* **Example Use Case:** Batch arithmetic transformations (e.g., adding bonus points to student scores).

### 5. Conditional Filtering
The `.filter()` method processes elements through a boolean predicate and retains only the values that satisfy specified threshold constraints.
* **File:** `series_filtering.cpp`
* **Example Use Case:** Extracting passing grades (`score >= 60.0`).

---

## 💻 Compilation & Execution

To compile any individual operational module, ensure you have a C++17 compatible compiler and the `codemasterspandas` library headers linked properly.

```bash
# Example: Compiling the Mapping demonstration module
g++ -std=c++17 series_mapping.cpp -o series_mapping -I/path/to/codemasterspandas

# Execute the compiled binary
./series_mapping
```

---

## 🛡 Exception & Error Handling

All modules wrap operations inside standard standard C++ `try-catch` blocks catching `std::exception`. This guarantees graceful termination and debugging outputs to standard error (`std::cerr`) in case of out-of-bounds indexing or invalid type conversions.
