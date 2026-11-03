// Robertbob Murungi
// Contribution: Usage example for CodeMasters Pandas

#include <codemasterspandas/codemasterspandas.hpp> 

#include <iostream> 

using namespace codemasterspandas; 

int main() 
{
    try
    {
        // Read the sample CSV dataset 
        DataFrame employees =
            read_csv("data/input/robert_sample_data.csv"); 

        std::cout << "Dataset loaded successfully.\n"; 
        std::cout << "Rows: " << employees.rows() << '\n'; 
        std::cout << "Columns: " << employees.cols() << "\n\n"; 

        // Salary statistics
        Series salaries = employees.column("salary"); 

        std::cout << "Average salary: " << mean(salaries)<< '\n'; 
                   
        std::cout << "Minimum salary: " << minimum(salaries) << '\n'; 

        std::cout << "Maximum salary: "<< maximum(salaries) << "\n\n";
                  
        // Performance statistics
        Series performance =
            employees.column("performance");

        std::cout << "Average performance: "<< mean(performance)<< '\n';         

        // Filter high performers
        DataFrame highPerformers =
            employees.filter(
                "performance",
                [](const Value& value)
                {
                    return is_numeric(value) &&
                           as_number(value) >= 90.0;
                }
            );

        std::cout
            << "Employees with performance >= 90: "<< highPerformers.rows()<< "\n\n";
            
            // Count employees by department
        auto departmentCounts =
            group_count(employees, "department");

        std::cout << "Employees by department:\n";

        for (const auto& item : departmentCounts)
        {
            std::cout
                << item.first
                << ": "
                << item.second
                << '\n';
        }

        std::cout << '\n';

        // Sort by performance from highest to lowest
        DataFrame ranked =
            employees.sort_by(
                "performance",
                false
            );

        std::cout
            << "Highest performance score: "
            << value_to_string(
                   ranked.at(0, "performance")
               )
            << "\n\n";

        // Export high performers
        write_csv(
            highPerformers,
            "robert_high_performers.csv"
        );

        write_json(
            highPerformers,
            "robert_high_performers.json"
        );

        std::cout
            << "High performers exported successfully.\n";

        // Read the JSON version of the sample data
        DataFrame jsonEmployees =
            read_json(
                "data/input/robert_sample_data.json"
            );

        std::cout
            << "JSON dataset contains "
            << jsonEmployees.rows()
            << " rows.\n";

        std::cout
            << "\nRobertbob Murungi usage example completed.\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Error: "
            << error.what()
            << '\n';

        return 1;
    }
}