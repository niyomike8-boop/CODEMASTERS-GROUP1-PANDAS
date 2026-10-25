Weekly Progress Report --- Week 4

Student: Robertbob Murungi
Project: CODEMASTERS-GROUP1-PANDAS
Reporting period: Week 4
Focus: Finalising contribution and version-control preparation

Objectives

- Finalise the files belonging to my assigned contribution.
- Document the work completed during the project.
- Stage only my own contribution files without accidentally including unrelated project files.
- Prepare the work for commit, push, and group review.

Work carried out

- Reviewed the CSV and JSON sample datasets and confirmed their intended locations.
- Reviewed "examples/usage_example.cpp" and corrected dataset file paths where necessary.
- Reviewed "tests/test_edge_cases.cpp" and confirmed the intended edge-case checks.
- Created "reports/robertbob-contribution.md" describing my contribution to the project.
- Investigated missing shared header files when the example and test files reported include errors.
- Confirmed that existing project examples use "codemasterspandas/codemasterspandas.hpp".
- Restored shared header files locally for project inspection without including them in my personal contribution.
- Used "git status" to distinguish my five contribution files from unrelated or shared files.
- Staged only:
  - "data/input/sample_data.csv" 
  - "data/input/sample_data.json" 
  - "examples/usage_example.cpp"   
  - "tests/test_edge_cases.cpp" 
  - "reports/robertbob-contribution.md" 

Skills and knowledge gained 

- Improved understanding of Git staging and selective commits. 
- Learnt why "git add ." may be undesirable when unrelated files are present. 
- Improved understanding of Git branches and how each group member can keep their contribution separate. 
- Practised troubleshooting C++ header and compiler configuration problems. 
- Improved understanding of the difference between errors caused by application code and errors caused by project integration or development environment configuration. 

Challenges 

- Shared header files required by the project were not present in the integrated repository at one stage. 
- VS Code continued to report IntelliSense errors because the local GCC version was older than the C++17 requirements. 
- Care was required to prevent shared restored headers and unrelated modified files from being included in my personal commit. 
- File naming and paths had to remain consistent between the datasets and C++ example. 

Next steps 

- Commit the five staged contribution files with a descriptive commit message. 
- Push the "robertbob-murungi" branch to GitHub. 
- Verify that the contribution appears correctly on the remote branch. 
- Open or participate in the pull-request process for review by the group integrator.v
- Make any corrections requested during group review.

Reflection 

This week brought together the testing, sample-data, example, documentation, and Git aspects of my contribution. I gained a better understanding of how individual work should be prepared in a group software project so that it can be reviewed and integrated without interfering with other members' files. 

AI was used. 