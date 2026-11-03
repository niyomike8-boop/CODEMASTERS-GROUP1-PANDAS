# CODEMASTERS GROUP 1 – PANDAS
## Overall Group Progress Report — Week 3

**Reporting period:** 19–25 October 2026  
**Project:** C++17 Pandas-Inspired Data Processing Library  
**Repository:** [CODEMASTERS-GROUP1-PANDAS](https://github.com/niyomike8-boop/CODEMASTERS-GROUP1-PANDAS)  
**Prepared for:** Academic project assessment  
**prepared by:** NIYONSABA MICHAEL 

---

## 1. Executive Summary

During Week 3, the group moved from initial project setup towards implementation and integration of the library's main data-processing capabilities. The repository shows work across the typed-value and series abstractions, data-frame operations, CSV/JSON input and output, descriptive statistics, data transformations, examples, sample datasets, and test sources.

The group's work was organised around separate modules so that different contributors could implement related functionality without placing the entire application in one source file. Individual Week 3 records describe work on the supporting `Value` interface, advanced statistical calculations, data-transformation checks, sample datasets, and usage examples.

The report distinguishes between (a) work described in individual weekly reports, (b) files and implementation components visible in the repository, and (c) work that still requires confirmation through test output or Git history. The presence of a source file is not treated by itself as proof that every feature was complete or passed testing.

## 2. Project Objectives

The group continued working towards the following objectives:

1. Build a reusable C++17 library for common tabular-data operations.
2. Represent heterogeneous data values and labelled one-dimensional series.
3. Provide DataFrame construction, selection, filtering, sorting, slicing, and derived-column operations.
4. Implement statistical calculations and grouped aggregation.
5. Support data cleaning and transformation operations.
6. Read and write sample data using CSV and JSON.
7. Demonstrate object-oriented and generic programming concepts.
8. Build examples and test cases that demonstrate and verify the library.
9. Coordinate individual work through Git branches and shared documentation.

## 3. Work Carried Out During the Week

### 3.1 Module development and organisation

The repository was organised into public headers under `include/codemasterspandas/` and implementation files under `src/`. The main modules visible in the project include:

| Module | Main files | Role in the project |
|---|---|---|
| Values | `value.hpp`, `value.cpp` | Represent missing, integer, floating-point, Boolean, and string values. |
| Series | `series.hpp`, `series.cpp` | Store and operate on a named one-dimensional sequence. |
| DataFrame | `dataframe.hpp`, `dataframe.cpp` | Store tabular data and support row/column operations. |
| Statistics | `statistics.hpp`, `statistics.cpp` | Provide descriptive statistics, correlation, and grouped aggregation. |
| Transformations | `transform.hpp`, `transform.cpp` | Convert, normalise, standardise, and modify values. |
| Input/output | `io.hpp`, `io.cpp` | Read and write CSV/JSON data and provide exporter functionality. |

This separation supports modular development, reuse, and easier testing.

### 3.2 Statistics and numerical analysis

Mukose Divine's Week 3 report records implementation of advanced statistical operations, including:

- `quantile()` and `percentile()`;
- `median()` based on quantiles;
- `standard_deviation()` with sample and population options;
- `correlation()` using paired numeric observations;
- exception handling for invalid inputs and insufficient data.

The Week 3 report also identifies grouped aggregation as work still in progress at that stage. The current repository contains the statistics implementation and declarations; the exact historical completion date for every function should be checked against commit history before attributing all current functionality to Week 3.

### 3.3 Value interface and supporting integration

Halima Ganyana's Week 3 individual report describes work on `include/codemasterspandas/value.hpp`, review of the relationship between the value interface and statistics functionality, and careful selection of files for Git staging.

This work is relevant because the `Value` representation is used by the Series and DataFrame modules and therefore affects how numerical, textual, Boolean, and missing data are handled across the library.

### 3.4 Data transformation review

Ninsiima Arthur's individual Week 3 report records review and testing of the following transformation operations:

- `normalize()` and `standardize()`;
- `to_numeric()` and `to_string_series()`;
- `lowercase()` and `uppercase()`;
- `trim_strings()`.

The report states that the functions were checked in relation to the shared `Series`, `Value`, and statistics modules. It also describes integration through the member's branch and a pull request. These statements should be supported at submission by the corresponding commit or pull-request references.

### 3.5 Sample data, tests, and usage examples

Robertbob Murungi's Week 3 report records preparation of an additional employee-performance dataset and development of a practical usage example. The repository contains sample input data in CSV and JSON formats, an employee-performance CSV dataset, example programs, and test source files.

The sample datasets allow the group to demonstrate data loading and operations on structured records. The examples are intended to show how library functions can be used by a consumer rather than only tested in isolation.

## 4. Team Contribution Summary

The table below combines the documented module allocation, individual Week 3 reports, and project records. It is a summary of assigned or reported areas, not a claim that every member completed all allocated work during this single reporting week.

| Member | Allocated area / reported Week 3 activity |
|---|---|
| Abalo Proscovia | `Value` and `Series` abstractions: typed values, indexing, slicing, mapping, and filtering. Confirm Week 3 activity against her individual report and commits. |
| Aguti Jemimah | `DataFrame` operations: tabular storage, selection, filtering, sorting, slicing, and derived columns. Confirm Week 3 activity against her individual report and commits. |
| Halima Ganyana | Supporting value-interface review and file organisation; individual report identifies work on `value.hpp` and preparation of selected files for version control. |
| Mukose Divine | Advanced statistics: quantile, median, percentile, standard deviation, correlation, exception handling; grouping and aggregation identified as ongoing. |
| Ninsiima Arthur | Transformation review/testing for normalisation, standardisation, conversion, and string operations; integration with shared modules reported. |
| Robertbob Murungi | Sample employee-performance dataset and practical usage-example development; further dataset testing and edge-case work identified as ongoing. |
| Mike / group integrator | Shared project coordination, review of module integration, build organisation, documentation, and weekly reporting. Confirm specific Week 3 commits or meeting records before listing individual completed tasks. |

## 5. Repository Evidence and Technical Structure

At the time of inspection, the repository contains the following relevant project areas:

```text
include/codemasterspandas/   Public module headers
src/                         C++ implementation files
tests/                       Main and extended test sources
examples/                    Demonstration programs
data/input/                  CSV and JSON sample datasets
data/output/                 Output location
docs/                        Module guide and branch assignments
reports/                     Individual and group progress reports
CMakeLists.txt                Build configuration
README.md                     Project overview and instructions
```

The structure supports a conventional C++ project layout: public interfaces are separated from implementation, tests are distinct from examples, and data files are kept outside the source modules.

## 6. Testing and Quality Assurance

The repository contains test sources including:

- `tests/test_library.cpp`;
- `tests/test_edge_cases.cpp`;
- `tests/test_transform.cpp`.

The project documentation describes test coverage for DataFrame operations, Series slicing, statistical calculations, transformations, CSV/JSON round trips, exporter behaviour, and exception handling.

**Week 3 verification record:** Individual reports mention testing or validation in specific module areas. However, this report does not claim a complete project-wide test pass for Week 3 because a dated test log or terminal output for the reporting period has not been included as evidence.

| Verification item | Week 3 report status |
|---|---|
| Module source/header organisation | Present in repository; reviewed structurally. |
| Advanced statistics implementation | Reported by statistics contributor; confirm with relevant commit and test output. |
| Transformation review | Reported by transformation contributor; confirm test output. |
| Sample datasets and example work | Reported by testing/examples contributor; files are present in repository. |
| Full project build | Evidence for this specific week should be attached before marking as passed. |
| Full automated test suite | Evidence for this specific week should be attached before marking as passed. |

## 7. Challenges and Responses

The individual Week 3 records identify practical development challenges:

**File selection and staging.** Halima's report describes the need to identify correct paths and avoid including unrelated untracked files. The response was to inspect Git status and stage only intended files.

**Cross-module dependencies.** The transformation module depends on shared `Value` and `Series` interfaces. This made integration checks important and meant that testing could be affected by the state of other modules.

**Statistical edge cases.** The statistics report identifies constant-value data in correlation and mismatched Series lengths as issues requiring careful handling. Exception handling and validation were included in the reported implementation work.

**Using common library interfaces.** The examples contributor needed to understand existing APIs without changing another member's implementation. This reinforced the importance of documenting public interfaces and keeping contributions within assigned areas.

## 8. Work in Progress at the End of Week 3

The following items were identified for continuation:

1. Complete or verify grouped DataFrame aggregation.
2. Continue testing sample datasets and usage examples.
3. Confirm member contributions through commits and pull requests.
4. Strengthen edge-case testing across modules.
5. Check compatibility between headers and source implementations.
6. Compile and test the integrated project using the agreed C++17 build process.
7. Update documentation to reflect the actual available interfaces.

## 9. Plan for Week 4

| Planned activity | Expected output | Evidence to retain |
|---|---|---|
| Complete grouped statistics and aggregation | Group count, sum, minimum, and maximum operations where required | Source changes and focused tests |
| Continue integration of member modules | Consistent interfaces across headers and source files | Pull requests, merge records, and build output |
| Improve sample-data examples | Reproducible end-to-end demonstrations | Example source and execution output |
| Extend edge-case tests | Coverage of invalid, empty, missing, and boundary inputs | Test source and test results |
| Review Git workflow | Changes placed on correct branches and reviewed | Commit history and pull requests |
| Update group documentation | Accurate build, use, and module information | README/docs commits |

## 10. AI Use Declaration

AI tools were reported as used in some individual Week 3 contributions. The individual reports refer to AI assistance for reviewing statistical formulas and edge cases, understanding project structure and Git workflow, and supporting related development tasks.

**Group declaration:** AI assistance was used by contributors in the ways described in their individual reports. AI-generated suggestions were treated as assistance rather than as a substitute for understanding, implementation, testing, or review. Group members remain responsible for the correctness and originality of the submitted code and documentation.

Before submission, the group should confirm the exact tools and uses for each member and ensure that this declaration follows the course's AI-use policy.

## 11. Conclusion

Week 3 focused on extending the library beyond initial setup by progressing the core data abstractions, statistical calculations, transformations, sample data, and practical examples. The modular structure provides a sound basis for parallel development, while the individual reports highlight the need for careful integration and evidence-based testing.

The group's next priority is to complete remaining operations, test the integrated code, maintain reliable branch and pull-request practices, and keep the project documentation aligned with the actual codebase.


