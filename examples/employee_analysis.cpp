#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>
#include <stdexcept>

using namespace codemasterspandas;

int main()
{
    try
    {
        // Run this program from the repository root.
        DataFrame employees = read_csv("data/input/sample_employees.csv");

        std::cout << "=== 1. ORIGINAL DATA ===\n";
        std::cout << employees.to_string();
        std::cout << "Rows: " << employees.rows()
                  << ", Columns: " << employees.cols() << "\n\n";

        std::cout << "=== 2. SELECT COLUMNS ===\n";
        DataFrame staff_report =
            employees.select({"name", "department", "salary"});
        std::cout << staff_report.to_string() << '\n';

        std::cout << "=== 3. FILTER HIGH PERFORMERS (>= 90) ===\n";
        DataFrame high_performers = employees.filter(
            "performance",
            [](const Value& value)
            {
                return is_numeric(value) && as_number(value) >= 90.0;
            }
        );
        std::cout << high_performers.to_string() << '\n';

        std::cout << "=== 4. SORT BY SALARY (DESCENDING) ===\n";
        DataFrame salary_ranking = employees.sort_by("salary", false);
        std::cout << salary_ranking.to_string() << '\n';

        const Series& salaries = employees.column("salary");
        std::cout << "=== 5. SALARY STATISTICS ===\n";
        std::cout << "Average salary: " << mean(salaries) << '\n';
        std::cout << "Minimum salary: " << minimum(salaries) << '\n';
        std::cout << "Maximum salary: " << maximum(salaries) << "\n\n";

        std::cout << "=== 6. EMPLOYEES PER DEPARTMENT ===\n";
        for (const auto& item : group_count(employees, "department"))
            std::cout << item.first << ": " << item.second << '\n';
        std::cout << '\n';

        std::cout << "=== 7. PAYROLL TOTAL PER DEPARTMENT ===\n";
        for (const auto& item : group_sum(employees, "department", "salary"))
            std::cout << item.first << ": " << item.second << '\n';
        std::cout << '\n';

        std::cout << "=== 8. FIRST THREE ROWS ===\n";
        DataFrame first_three = employees.slice(0, 3);
        std::cout << first_three.to_string() << '\n';

        write_csv(high_performers, "data/output/high_performers.csv");
        write_json(high_performers, "data/output/high_performers.json");
        std::cout << "Filtered results exported to data/output/.\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
