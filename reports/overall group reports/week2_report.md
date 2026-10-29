# CODEMASTERS-GROUP1-PANDAS

## Week 2 Project Progress Report

**Reporting period:** Week 2 --- week commencing 12 October 2026\
**Project:** C++ Pandas-style data-processing library\
**Repository:** `CODEMASTERS-GROUP1-PANDAS`\
**Report status:** Draft for team verification\
**Prepared by:** Project team leader niyonsaba michael


------------------------------------------------------------------------

## 1. Executive Summary

During Week 2, the team continued organising and developing the C++
project intended to provide data-processing functionality inspired by
the Pandas library. The repository is organised into source files,
public header files, reports, examples, tests, documentation, and data
directories. This structure supports separation of implementation,
interfaces, testing resources, sample usage, and project records.

The visible repository includes modules associated with data frames,
input/output, series, statistics, transformations, and values. It also
contains weekly reporting files and project documentation. These
components indicate the planned scope of the library; their presence
alone does not prove that every feature is complete or fully tested.

The main priorities for the next stage are to confirm the status of each
module, integrate contributions consistently, compile the project, run
relevant tests, document known limitations, and maintain clear Git
history through branches and reviewed pull requests.

## 2. Project Background

The project aims to build a C++ library for working with structured
data. The intended design draws on common data-analysis operations such
as storing tabular data, representing sequences, reading and writing
data, calculating descriptive statistics, and transforming values.

The project is being developed collaboratively through a shared GitHub
repository. A clear folder structure and reliable version-control
practices are important because multiple contributors may work on
different modules at the same time.

### 2.1 Main project objectives

The objectives are to:

1.  Develop reusable C++ components for common data-processing tasks.
2.  Define clear interfaces in header files and implement behaviour in
    source files.
3.  Provide examples that demonstrate how the library should be used.
4.  Create tests that help verify correctness and identify regressions.
5.  Maintain documentation that explains the project, its structure, and
    how to build and use it.
6.  Coordinate contributions through branches, commits, and pull
    requests.
7.  Keep weekly progress reports that record completed work, ongoing
    work, blockers, and next steps.

## 3. Repository Organisation

The repository contains several directories and files that separate
different parts of the project.

  -----------------------------------------------------------------------
  Directory or file                   Intended role
  ----------------------------------- -----------------------------------
  `src/`                              C++ implementation files for the
                                      library's modules.

  `include/codemasters pandas/`\*     Public or reusable header files
                                      that declare module interfaces.

  `tests/`                            Test code used to check expected
                                      behaviour.

  `examples/`                         Example programs or datasets
                                      demonstrating intended usage.

  `data/`                             Input data and other data resources
                                      used during development or testing.

  `docs/`                             Technical documentation and project
                                      guidance.

  `reports/`                          Weekly progress reports and the
                                      final report.

  `.vscode/`                          Optional editor-specific
                                      configuration; it is not part of
                                      the library's core functionality.

  `README.md`                         Project overview and instructions
                                      for contributors and users.

  `LICENSE`                           Terms governing use and
                                      distribution of the project.
  -----------------------------------------------------------------------

\*Confirm the exact header-directory spelling in the repository. The
screenshot shows the namespace folder as `codemasterspandas`.

This structure is useful because it reduces the mixing of implementation
code, interface declarations, test files, and administrative
documentation. Contributors should follow the existing structure when
adding new files.

## 4. Work Reviewed During Week 2

The following items are based on the visible project workspace and
should be checked against the team's actual work before the report is
submitted.

### 4.1 Codebase structure and module separation

The workspace shows source files and corresponding header files for
several areas, including data-frame handling, input/output, series,
statistics, transformations, and values. This suggests that the project
is being divided into focused modules rather than being written as one
large source file.

**Why this matters:** Modular design makes code easier to understand,
test, maintain, and extend. It also allows team members to work on
separate components with fewer unnecessary conflicts.

**Evidence to attach or verify:** - Relevant source and header files. -
Commits showing the creation or modification of modules. - A successful
build or compiler output, if available.

### 4.2 Header and implementation organisation

The visible workspace contains `.hpp` header files under the include
directory and `.cpp` implementation files under `src/`.

Headers should declare the interfaces that other parts of the library
need to use. Source files should contain the corresponding
implementations where appropriate. The team should verify that file
names, namespaces, declarations, and definitions are consistent.

**Quality checks:** - Include guards or `#pragma once` are used
consistently. - Headers include the declarations they depend on. -
Functions declared in headers have matching definitions where
required. - Namespaces and naming conventions are consistent. - Files do
not contain duplicate or obsolete declarations.

### 4.3 Reporting and project documentation

The `reports/` directory contains weekly reports and a final-report
file. Maintaining these records gives the team a history of progress and
makes it easier to prepare the final project submission.

A useful progress report should explain what changed, why it changed,
how it was checked, what remains incomplete, and what the team plans to
do next. A list of filenames alone is not enough to demonstrate
progress.

**Evidence to verify:** Review the relevant report files, their Git
history, and any agreed team notes. Replace scaffold instructions with
actual work completed before submitting this report.

### 4.4 Version-control collaboration

The repository is shared among multiple contributors and contains
branches and merged pull-request activity. This makes version-control
discipline important for coordinating work.

The team should use feature branches for independent tasks, meaningful
commit messages, and pull requests to review changes before merging them
into the main branch. Contributors should confirm the target branch
before pushing to avoid placing work in the wrong branch.

**Recommended practice:** 1. Pull or fetch the latest repository state
before beginning work. 2. Switch to the intended working branch. 3. Make
a focused change and run the relevant checks. 4. Review `git status`
before staging files. 5. Commit only the files related to the task. 6.
Push to the correct remote branch. 7. Open or update a pull request and
respond to review feedback. 8. Confirm that the merged changes appear in
the intended branch.

### 4.5 Editor-specific configuration

The workspace shows a `.vscode/` folder containing `tasks.json`. This
file may configure editor tasks, such as build or run commands. It is
not part of the library's core functionality.

The team should decide whether this configuration is useful to all
contributors. If it is machine-specific, unnecessary, or not agreed upon
by the team, it can be removed through a normal Git change. Before
deleting it, check whether other contributors rely on its task
definitions.

## 5. Module Status and Technical Review

The repository names indicate several intended modules. The table below
is a review checklist, not a claim that the modules are already
complete.

  -----------------------------------------------------------------------
  Module                  Expected responsibility Checks required
  ----------------------- ----------------------- -----------------------
  Data frame              Represent tabular data  Confirm the data model,
                          and support appropriate indexing rules, shape
                          row/column operations.  handling, and edge
                                                  cases.

  Series                  Represent a             Check construction,
                          one-dimensional         access, size reporting,
                          sequence of values.     and supported
                                                  operations.

  Input/output            Read or write data in   Check valid input,
                          the formats selected by missing files,
                          the team.               malformed data, and
                                                  error handling.

  Statistics              Calculate selected      Test normal data, empty
                          descriptive statistics. data, single-element
                                                  data, and invalid
                                                  values where relevant.

  Transformations         Apply defined           Check output
                          operations to stored    correctness, type
                          values or data          behaviour, and boundary
                          structures.             cases.

  Values                  Represent or manage     Confirm supported
                          values used by the      types, conversions, and
                          library.                error conditions.
  -----------------------------------------------------------------------

For every module, the team should record one of the following statuses:
**Not started**, **In progress**, **Implemented**, **Tested**, or
**Blocked**. A file existing in the repository should not automatically
be labelled "Implemented" or "Tested."

## 6. Testing and Quality Assurance

Testing is essential for establishing that the library behaves as
intended. The existence of a `tests/` directory does not, by itself,
prove that tests pass.

The team should use a consistent test process and record the results.

### 6.1 Recommended checks

1.  **Compilation:** Build the project using the agreed compiler and C++
    standard.
2.  **Unit tests:** Test individual functions and classes independently.
3.  **Integration tests:** Check whether modules work correctly
    together.
4.  **Boundary tests:** Include empty inputs, one-element inputs, large
    inputs, and invalid inputs where applicable.
5.  **Regression tests:** Re-run existing tests after changing code.
6.  **Example verification:** Compile and run the examples that are
    intended to be executable.
7.  **Repository review:** Confirm that generated binaries, temporary
    files, and editor-specific files are not committed unintentionally.

### 6.2 Test-results record

Complete this table with actual results before submission.

  -----------------------------------------------------------------------
  Check                   Result                  Evidence or notes
  ----------------------- ----------------------- -----------------------
  Project builds          Pending verification    Add compiler, command,
  successfully                                    and output.

  Unit tests pass         Pending verification    Add test command and
                                                  summary.

  Integration tests pass  Pending verification    Add test command and
                                                  summary.

  Examples compile and    Pending verification    List verified examples.
  run                                             

  No unintended files are Pending verification    Review `git status` and
  committed                                       the pull request diff.
  -----------------------------------------------------------------------

Do not change "Pending verification" to "Passed" until the check has
actually been performed.

## 7. Challenges and Risks

The following are risks to review with the team. They should be
described as actual blockers only if the team has experienced them.

### 7.1 Integration conflicts

When several contributors modify related files, declarations and
implementations can become inconsistent or produce merge conflicts.

**Mitigation:** Agree on interfaces early, communicate changes to shared
headers, keep branches focused, and review pull requests before merging.

### 7.2 Incomplete or unverified functionality

A module may have files in place without implementing all required
behaviour or handling edge cases.

**Mitigation:** Define acceptance criteria for each module and require
relevant tests before marking it complete.

### 7.3 Unclear contribution history

Pushing work to the wrong branch or including unrelated files in a
commit can make it difficult to identify ownership and progress.

**Mitigation:** Confirm the branch before committing, inspect staged
changes, use descriptive commit messages, and review the pull-request
diff.

### 7.4 Documentation that does not match the code

Documentation can become outdated as interfaces and functionality
change.

**Mitigation:** Update examples and documentation alongside code changes
and verify commands against the current repository.

### 7.5 Build-environment differences

Different compiler versions or build settings may produce inconsistent
results.

**Mitigation:** Document the supported compiler, required C++ standard,
dependencies, and build instructions. Where possible, use a shared or
automated build check.

## 8. Work in Progress

Update this section to reflect the team's real status.

-   Confirm the implementation status of each module.
-   Review consistency between header declarations and source
    definitions.
-   Compile the project using the agreed development environment.
-   Run available tests and record failures.
-   Verify examples against the current API.
-   Review pull requests and resolve outstanding integration issues.
-   Replace report scaffolds with evidence-based descriptions of work
    completed.

## 9. Plan for the Next Week

  -----------------------------------------------------------------------
  Task                    Expected output         Completion evidence
  ----------------------- ----------------------- -----------------------
  Audit module interfaces Consistent declarations Code review and
                          and definitions         successful build

  Compile the project     Build result recorded   Compiler output or
                                                  build log

  Expand module tests     Tests for core          Test files and test
                          behaviour and edge      summary
                          cases                   

  Verify examples         Examples consistent     Successful compilation
                          with the current API    and execution

  Review repository       Only intended files     Reviewed Git status and
  hygiene                 tracked                 pull-request diff

  Improve documentation   Updated build and usage README or documentation
                          instructions            commit

  Update progress records Accurate weekly report  Reviewed report
                                                  committed to the
                                                  correct branch
  -----------------------------------------------------------------------

The team should assign an owner and target date to each task during its
planning meeting.

## 10. Team Coordination and Version-Control Procedure

To improve coordination, each contributor should have a clearly defined
task and should communicate interface changes that affect other modules.

A recommended task workflow is:

1.  Agree on the task and acceptance criteria.
2.  Create or switch to the correct branch.
3.  Implement the change.
4.  Run relevant checks locally.
5.  Review the changed files using `git diff` and `git status`.
6.  Commit the intended changes with a clear message.
7.  Push to the matching remote branch.
8.  Open a pull request with a summary and test evidence.
9.  Review and merge the change after resolving feedback.
10. Confirm that the target branch contains the intended result.

Useful commands include:

``` bash
git status
git branch
git pull
git diff
git add <specific-file>
git commit -m "Describe the change"
git push origin <branch-name>
```

Replace placeholders such as `<specific-file>` and `<branch-name>` with
actual names. Avoid using broad staging commands when unrelated or
temporary files are present.

## 11. Use of AI Tools

The existing Week 2 scaffold mentions the use of OpenAI Codex during
initial project scaffolding and Week 1 drafting. The team should confirm
whether any AI tools were used during Week 2 and describe that use
accurately.

Complete the following entries:

-   **Tool used:** \[Name the tool, or write "None" if no AI tool was
    used this week.\]
-   **Purpose:** \[Explain the specific task for which it was used.\]
-   **Reason:** \[Explain why the tool was useful.\]
-   **Verification:** \[Explain how generated suggestions or content
    were reviewed, tested, or corrected.\]

AI-generated code and text should be reviewed by the team. Contributors
remain responsible for correctness, originality, appropriate
attribution, and compliance with course or institutional rules.

## 12. Conclusion

Week 2 provides an opportunity to strengthen the organisation,
integration process, and verification practices of the C++
data-processing project. The visible repository structure separates
implementation files, headers, tests, examples, documentation, data
resources, and reports, providing a useful foundation for collaborative
development.

The next priority is to turn this structure into demonstrably working
functionality. The team should verify module behaviour, compile the
project, run tests, document results, and maintain an accurate record of
contributions. The final submitted report should distinguish completed
work from work in progress and should include evidence from commits,
pull requests, test results, or meeting records.

