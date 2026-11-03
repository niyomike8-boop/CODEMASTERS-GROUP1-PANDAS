# CODEMASTERS GROUP 1 – PANDAS
## Overall Group Progress Report — Week 4

**Reporting period:** 26 October–1 November 2026  
**Project:** C++17 Pandas-Inspired Data Processing Library  
**Repository:** [CODEMASTERS-GROUP1-PANDAS](https://github.com/niyomike8-boop/CODEMASTERS-GROUP1-PANDAS)  
**Prepared for:** Academic project assessment  
**PREPARED BY THE GROUP LEADER:** NIYONSABA MICHAEL 

---

## 1. Executive Summary

During Week 4, the group concentrated on completing and consolidating the library's main functionality, reviewing individual contributions, improving testing and examples, and preparing the project for final integration and assessment.

The Week 4 individual reports describe progress in grouped statistical aggregation, version-control preparation, sample-data and example review, integration of transformation functions, and preparation of contribution documentation. The repository currently contains the corresponding module files, example programs, sample datasets, multiple test sources, a project README, module documentation, and a final group report.

The repository also includes a CMake build configuration and an existing build directory. The existence of build files and test sources is useful evidence of project setup, but does not on its own prove that a clean build or all tests passed during Week 4. Such claims should be supported by an actual test log or terminal output.

## 2. Project Objectives

The group's continuing objectives were to:

1. Consolidate the C++17 data-processing library into a coherent project.
2. Complete the main Value, Series, DataFrame, statistics, transformation, and I/O functionality.
3. Support CSV and JSON input/output.
4. Demonstrate inheritance, polymorphism, templates, exception handling, and STL use.
5. Improve test coverage for normal and exceptional inputs.
6. Provide examples and sample datasets that demonstrate practical library use.
7. Maintain project documentation and credible contribution records.
8. Prepare the integrated project for clean build, demonstration, and final assessment.

## 3. Main Work Carried Out

### 3.1 Statistics and grouped aggregation

Mukose Divine's Week 4 report records implementation of grouped aggregation operations:

- `group_sum()`;
- `group_min()`;
- `group_max()`;
- `group_count()`.

The report also describes code review, integration testing, exception-handling checks, and preparation for pull-request review. These features complement the descriptive statistics reported in Week 3, including count, sum, minimum, maximum, mean, median, quantile, percentile, standard deviation, and correlation.

The current project documentation describes grouped aggregation as part of the statistics module. The group should retain the relevant code review and test evidence to substantiate the Week 4 verification claims.

### 3.2 CSV/JSON input and output and exporter design

The integrated repository contains `include/codemasterspandas/io.hpp` and `src/io.cpp`, as well as sample CSV/JSON files and I/O examples. The project documentation describes `read_csv`, `write_csv`, `read_json`, and `write_json`.

The I/O design also demonstrates inheritance and runtime polymorphism through a common `DataExporter` interface and CSV/JSON exporter implementations. These are important project outcomes because they allow a DataFrame to be exported through a shared interface.

### 3.3 Transformation module integration

Ninsiima Arthur's Week 4 individual report describes synchronising the personal branch with the latest `main` branch and reviewing the transformation functions in the integrated project. The functions identified include:

- `normalize()`;
- `standardize()`;
- `to_numeric()`;
- `to_string_series()`;
- `lowercase()`;
- `uppercase()`;
- `trim_strings()`.

The report also identifies additional tests needed for non-constant data, mixed types, invalid numeric conversion, blank strings, and conversion behaviour. This is useful evidence of review and test planning; the additional tests should only be described as completed after confirming the corresponding code and results.

### 3.4 Sample data, examples, and edge-case tests

Robertbob Murungi's Week 4 report describes review of the CSV and JSON sample datasets, review of `examples/usage_example.cpp`, review of `tests/test_edge_cases.cpp`, and preparation of `reports/robertbob-contribution.md`.

The report also records troubleshooting around shared header files, C++17/IntelliSense configuration, and selective Git staging. The stated approach was to stage only files belonging to the contributor's assignment rather than unintentionally including unrelated or shared files.

The repository contains sample input data, several example programs, and test sources. These resources support practical demonstration and testing of the library.

### 3.5 Version-control preparation and integration

Halima Ganyana's Week 4 report describes staging intended files, committing changes, and pushing a branch to GitHub. It correctly distinguishes a successful branch push from a completed merge into `main`: the latter still requires a pull request or an authorised integration action.

The group continued to rely on branches and focused commits to separate individual work. Changes should be reviewed before merging so that shared headers, module interfaces, and examples remain compatible.

## 4. Technical Consolidation of the Project

The current repository presents the following integrated structure:

| Project component | Main implementation area | Purpose |
|---|---|---|
| Value | `value.hpp`, `value.cpp` | Represents supported cell types and missing values. |
| Series | `series.hpp`, `series.cpp` | Provides named one-dimensional data and sequence operations. |
| DataFrame | `dataframe.hpp`, `dataframe.cpp` | Provides tabular storage and data manipulation. |
| Statistics | `statistics.hpp`, `statistics.cpp` | Performs descriptive statistics, correlation, and grouped aggregation. |
| Transformations | `transform.hpp`, `transform.cpp` | Performs conversion, normalisation, standardisation, and string operations. |
| I/O | `io.hpp`, `io.cpp` | Supports CSV/JSON reading and writing and exporter classes. |
| Tests | `tests/` | Contains primary and extended test programs. |
| Examples | `examples/` | Demonstrates usage of the library. |
| Data | `data/input/`, `data/output/` | Holds sample input data and an output location. |
| Documentation | `README.md`, `docs/` | Explains objectives, project structure, modules, and build instructions. |

## 5. Group Contribution Summary

This table records the documented project allocation and Week 4 activity described in individual reports. It should not be interpreted as proof that every member completed every assigned feature during Week 4.

| Member | Contribution area and Week 4 evidence described |
|---|---|
| Abalo Proscovia | `Value` and `Series` module responsibility. Confirm Week 4 changes and review activity against the member's report and repository history. |
| Aguti Jemimah | `DataFrame` module responsibility. Confirm Week 4 changes and review activity against the member's report and repository history. |
| Halima Ganyana | Reports staging selected value/statistics-related files, committing, and pushing a branch; pull-request review and integration remained separate next steps. |
| Mukose Divine | Reports grouped sum, minimum, maximum, and count operations, along with code review and integration/testing activity. |
| Ninsiima Arthur | Reports synchronising the personal branch with `main`, reviewing transformation functions, and identifying further test cases. |
| Robertbob Murungi | Reports reviewing sample datasets, usage example, and edge-case tests; preparing a contribution record and selectively staging assigned files. |
| Mike / group integrator | Shared integration, review, build organisation, project documentation, and group reporting. Add exact dated commits or meeting records for any specific Week 4 task claimed. |

## 6. Testing and Quality Assurance

The repository has test sources for general library behaviour, edge cases, and transformations. The README describes the intended build and test commands:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The test programme cover:

- DataFrame construction, selection, filtering, sorting, slicing, derived columns, and reshaping;
- Series indexing and slicing;
- descriptive statistics and grouped aggregation;
- numerical template behaviour for supported arithmetic types;
- normalisation, standardisation, conversion, and string transformations;
- CSV and JSON read/write operations;
- exporter inheritance and polymorphism;
- invalid inputs, missing values, and exception behaviour.



| Quality check | Status for this report |
|---|---|
| Source/header structure | Present in current repository. |
| CMake configuration | `CMakeLists.txt` is present; clean configure/build result must be attached. |
| Main test source | Present as `tests/test_library.cpp`; execution result must be recorded. |
| Edge-case test source | Present as `tests/test_edge_cases.cpp`; execution result must be recorded. |
| Transformation test source | Present as `tests/test_transform.cpp`; execution result must be recorded. |
| CSV/JSON examples and datasets | Present; end-to-end execution should be recorded. |
| External-machine test | Record the tester, environment, build result, and test result only after the test is performed. |

## 7. Challenges and Corrective Measures

### 7.1 Shared-header and integration dependencies

The Week 4 examples report describes missing shared headers during local inspection, which affected compilation and IntelliSense. The contributor restored the required headers locally for inspection while separating them from the files intended for the personal contribution.


### 7.2 Compiler and editor configuration

The examples contributor reported IntelliSense issues associated with an older GCC version and the project's C++17 requirements.

**Corrective measure:** Use a compiler with C++17 support, document the selected compiler, and distinguish editor diagnostics from actual compiler errors.

### 7.3 Git staging and branch management

The individual reports emphasise careful staging, correct branch selection, and the difference between pushing a branch and merging it into `main`.

**Corrective measure:** Inspect `git status` and `git diff`, stage specific files, use descriptive commits, and integrate through reviewed pull requests.

### 7.4 Test coverage and edge cases

Additional tests were identified for constant and non-constant data, mixed types, invalid conversions, blank strings, and grouped calculations.

**Corrective measure:** Convert each identified edge case into a repeatable test and record the actual result.

## 8. Project Documentation and Submission Readiness

The repository contains a detailed README describing project objectives, features, folder structure, requirements, build commands, basic usage, templates, inheritance/polymorphism, testing, sample data, group contributions, and OOP concepts.

The `docs/MODULES.md` file explains the principal module responsibilities and current limitations. The `docs/BRANCH_ASSIGNMENTS.md` file describes proposed member responsibilities and cautions that the allocation should be checked against the official course brief.

The repository also contains a final group report. The external-machine validation section in that report is intentionally left for actual test details; the group should complete it only after an independent person has built and run the project.

## 9. Work Remaining / Items Requiring Final Verification

1. Perform a clean CMake configure and build using a supported C++17 compiler.
2. Run the full registered test suite and the additional test executables as appropriate.
3. Record exact pass/fail totals and retain the test output.
4. Compile and run the examples using the documented sample-data paths.
5. Review all outstanding branches and pull requests; confirm which changes are merged into `main`.
6. Check that all public headers and implementation files are present in a clean clone.
7. Reconcile the README, module guide, group contributions, and final report with the actual code.
8. Complete independent-machine validation and record the tester's real results.
9. Confirm the official work allocation and any course-specific submission requirements.
10. Ensure the AI-use declaration is accurate for all contributors.

## 10. Plan for the Next Stage

| Activity | Deliverable | Evidence |
|---|---|---|
| Clean build and test | Reproducible successful build and test result, or documented defects | Build log and test output |
| Final code review | Reviewed module interfaces and resolved defects | Pull-request reviews / review notes |
| Example verification | Examples compile and run with documented input data | Terminal output or screenshots |
| Documentation audit | README and reports match the delivered code | Documentation commit |
| Independent testing | External tester's build and execution record | Completed validation table |
| Final submission preparation | Consistent source, tests, reports, and contribution evidence | Submission checklist |

## 11. AI Use Declaration

The individual Week 4 reports state that AI tools were used by contributors. Reported purposes include documentation assistance, algorithm review, understanding project structure, and support with development or version-control tasks.

**Group declaration:** AI assistance was used as a support tool by contributors as described in their individual reports. AI-generated suggestions or text must be reviewed, adapted, and verified by the responsible group members. The group remains responsible for understanding the submitted implementation, checking mathematical and programming correctness, acknowledging AI use, and following the institution's rules on academic integrity.


## 12. Conclusion

Week 4 focused on consolidating the major project modules and preparing the codebase for final verification. The individual reports describe progress in grouped aggregation, transformation integration, sample-data and example review, test planning, and version-control preparation. The shared repository contains the principal implementation modules, public headers, examples, datasets, tests, documentation, and build configuration expected of the project.

The project should now be treated as ready for final verification rather than automatically considered fully validated. A clean build, actual test results, example execution, reviewed integration history, and completed independent-machine validation will provide the evidence needed for a strong academic submission.

---

