Robertbob Murungi - Final Contribution Report 

Project Title 

CodeMasters Group 1 Pandas 

Project Overview

The project is a C++ data-analysis library inspired by Python Pandas. It is designed to support tabular data storage, filtering, sorting, transformations, statistical analysis, grouping, and CSV/JSON file handling. 

My Assigned Contribution 

My assigned responsibility was: 

- Test coverage 
- Generated sample datasets 
- Usage examples 

I focused on testing the library without changing the implementation modules developed by other group members. 

Work Completed 

1. Sample Datasets 

I created sample employee datasets in both CSV and JSON formats. 

Files created: 

- "sample_data.csv" 
- "sample_data.json" 

The datasets contain employee information including: 

- Employee ID 
- Name 
- Department 
- Age 
- Salary  
- Performance score 

The datasets can be used to demonstrate filtering, sorting, statistical calculations, grouping, CSV reading, and JSON reading. 

2. Edge-Case Testing 

I created: 

- "test_edge_cases.cpp" 

The tests check unusual and invalid situations including: 

- Filtering when no rows match  
- Invalid percentile values 
- Negative percentile values 
- Normalization of constant values 
- Conversion of strings to numbers 
- Invalid numeric conversion 
- Trimming spaces from strings 
- Uppercase string conversion 
- Reading a missing CSV file 
- CSV files with an incorrect number of fields 
- CSV values containing commas 
- CSV write/read round-trip 
- Correlation using Series of different lengths 
- Correlation with constant values 

These tests help confirm that the library handles both valid and invalid data correctly. 

3. Usage Example 

I created: 

- "usage_example.cpp" 

The example demonstrates how a user can: 

1. Read a CSV dataset. 
2. Create a DataFrame. 
3. Select salary and performance columns. 
4. Calculate mean, minimum, and maximum values. 
5. Filter high-performing employees. 
6. Group employees by department. 
7. Export filtered results to CSV and JSON. 

Challenges 

One challenge was understanding how the different modules developed by other group members interact with each other. 

I also had to ensure that my work remained within my assigned responsibilities and did not interfere with the implementation work of other group members. 

Conclusion

My contribution improves the reliability and usability of the CodeMasters Pandas project by providing test coverage, reusable sample datasets, and a practical example demonstrating how the library can be used. 

AI Use

ChatGPT was used to help understand the project structure, Git workflow, and test-case design.