/**
 * @file series_slicing.cpp
 * @brief Demonstration of slicing sub-ranges from a Series container.
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
        // Initialize base series for slicing
        Series scores("student_scores", {55.0, 80.5, 92.0, 43.5, 67.0});

        // =========================================================================
        // SERIES SLICING
        // =========================================================================
        // Slicing the Series to isolate a sub-range of elements 
        // (from index 1 inclusive up to index 4 exclusive).
        Series sliced_scores = scores.slice(1, 4);
        std::cout << "Sliced series size: " << sliced_scores.size() << '\n';

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error encountered: " << e.what() << '\n';
        return 1;
    }
}