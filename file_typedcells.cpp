/**
 * @file typed_cells_demo.cpp
 * @brief Demonstration of typed cell 'Value' initialization and inspection.
 * @author Abalo Proscovia
 * @reg_no 25/U/26390/PS
 * @program Computer and Communications Engineering
 
 */

#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace codemasterspandas;

int main() {
    try {
        // =========================================================================
        // TYPED CELLS ('Value') INITIALIZATION & INSPECTION
        // =========================================================================
        // Initializing typed cell 'Value' containers holding different data types 
        // (integer, double, string) to represent individual data points.
        Value int_cell(42);
        Value double_cell(3.14);
        Value string_cell(std::string("Makerere"));

        std::cout << "Typed cells initialized successfully.\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error encountered: " << e.what() << '\n';
        return 1;
    }
}