// Robertbob Murungi — sample dataset and library usage
#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>
#include <stdexcept>

using namespace codemasterspandas;

int main()
{
    try
    {
        // Run this example from the repository root directory.
        DataFrame employees = read_csv("data/input/sample_data.csv");

        if (employees.rows() == 0)
        {
            throw std::runtime_error("The employee dataset is empty");
        }

        std::cout << "Dataset loaded successfully.\n";
        std::cout << "Rows: " << employees.rows() << '\n';
        std::cout << "Columns: " << employees.cols() << "\n\n";

        const Series& salaries = employees.column("salary");
        std::cout << "Average salary: " << mean(salaries) << '\n';
        std::cout << "Minimum salary: " << minimum(salaries) << '\n';
        std::cout << "Maximum salary: " << maximum(salaries) << "\n\n";

        const Series& performance = employees.column("performance");
        std::cout << "Average performance: " << mean(performance) << '\n';

        DataFrame highPerformers = employees.filter(
            "performance",
            [](const Value& value)
            {
                return is_numeric(value) && as_number(value) >= 90.0;
            }
        );

        std::cout << "Employees with performance >= 90: "
                  << highPerformers.rows() << "\n\n";

        const auto departmentCounts = group_count(employees, "department");
        std::cout << "Employees by department:\n";
        for (const auto& item : departmentCounts)
        {
            std::cout << item.first << ": " << item.second << '\n';
        }

        DataFrame ranked = employees.sort_by("performance", false);
        std::cout << "\nHighest performance score: "
                  << value_to_string(ranked.at(0, "performance"))
                  << "\n\n";

        write_csv(highPerformers, "data/output/robert_high_performers.csv");
        write_json(highPerformers, "data/output/robert_high_performers.json");
        std::cout << "High performers exported to data/output/.\n";

        DataFrame jsonEmployees = read_json("data/input/sample_data.json");
        if (jsonEmployees.rows() != employees.rows())
        {
            throw std::runtime_error("CSV and JSON sample row counts differ");
        }
        std::cout << "JSON dataset contains " << jsonEmployees.rows()
                  << " rows.\n";
        std::cout << "\nRobertbob Murungi usage example completed.\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
