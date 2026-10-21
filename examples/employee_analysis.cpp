#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>

using namespace codemasterspandas;

int main() {
    try {
        DataFrame employees =

            read_csv("data/input/employee_performance.csv");
        std::cout << "EMPLOYEE PERFORMANCE DATA\n";
        
        std::cout << employees.to_string() << '\n';

        DataFrame highPerformers =
            employees.filter("score", [](const Value& value) 
            {
                return is_numeric(value) &&
                       as_number(value) >= 80.0;
            }
        );
        std::cout << "\nEMPLOYEES SCORING 80 OR ABOVE\n";
        std::cout << highPerformers.to_string() << '\n';

        DataFrame ranked =
            employees.sort_by("score", false);

        std::cout << "\nEMPLOYEES RANKED BY SCORE\n";
        std::cout << ranked.to_string() << '\n';

        Series scores = employees.column("score");

        std::cout << "\nSCORE STATISTICS\n";
        std::cout << "Mean: " << mean(scores) << '\n';
        std::cout << "Median: " << median(scores) << '\n';
        std::cout << "Minimum: " << minimum(scores) << '\n';
        std::cout << "Maximum: " << maximum(scores) << '\n';

        std::cout << "\nTOTAL SCORE BY DEPARTMENT\n";

        auto totals =
            group_sum(employees, "department", "score");

        for (const auto& group : totals) {
            std::cout << group.first
                      << ": "
                      << group.second
                      << '\n';
        }

        return 0;
    }
    catch (const std::exception& error) {
        std::cerr << "Error: "
                  << error.what()
                  << '\n';

        return 1;
    }
}