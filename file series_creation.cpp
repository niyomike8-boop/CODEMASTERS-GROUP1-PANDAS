/**
 * @file series_creation_indexing.cpp
 * @brief Demonstration of Series creation and explicit position indexing.
 * @author Abalo Proscovia
 * @reg_no 25/U/26390/PS
 * @program Computer and Communications Engineering
 */

#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace codemasterspandas;

int main() {
    try {
        // =========================================================================
        // 'Series' CREATION & INDEXING
        // =========================================================================
        // Creating a homogeneous 'Series' container and performing indexing 
        // to retrieve elements by their explicit position.
        Series scores("student_scores", {55.0, 80.5, 92.0, 43.5, 67.0});
        
        // Accessing individual elements via indexing
        double first_score = as_number(scores.at(0));
        std::cout << "First score via indexing: " << first_score << '\n';

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error encountered: " << e.what() << '\n';
        return 1;
    }
}