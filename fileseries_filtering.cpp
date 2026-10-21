/**
 * @file series_filtering.cpp
 * @brief Demonstration of conditional filtering on a Series container.
 * @author Abalo Proscovia
 * @reg_no 25/U/26390/PS
 * @program Computer and Communications Engineering
 * @date October 2026
 */

#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace codemasterspandas;

int main() {
    try {
        // Initialize base series for filtering
        Series scores("student_scores", {55.0, 80.5, 92.0, 43.5, 67.0});

        // =========================================================================
        // FILTERING OPERATIONS
        // =========================================================================
        // Filtering the Series elements based on a conditional predicate 
        // (retaining only scores greater than or equal to 60.0).
        Series passing_scores = scores.filter([](const Value& v) {
            return as_number(v) >= 60.0;
        });
        std::cout << "Number of passing scores after filtering: " << passing_scores.size() << '\n';

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error encountered: " << e.what() << '\n';
        return 1;
    }
}