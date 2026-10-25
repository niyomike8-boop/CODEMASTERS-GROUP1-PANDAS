/**
 * @file series_mapping.cpp
 * @brief Demonstration of element-wise transformations using map.
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
        // Initialize base series for mapping
        Series scores("student_scores", {55.0, 80.5, 92.0, 43.5, 67.0});

        // =========================================================================
        // MAPPING OPERATIONS
        // =========================================================================
        // Applying a transformation function across each element in the Series (map) 
        // to scale or modify values (e.g., adding a bonus of 5.0 points to each score).
        Series adjusted_scores = scores.map([](const Value& v) {
            return Value(as_number(v) + 5.0);
        });
        std::cout << "First mapped score: " << as_number(adjusted_scores.at(0)) << '\n';

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error encountered: " << e.what() << '\n';
        return 1;
    }
}