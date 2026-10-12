/**
 * @file tests.cpp
 * @brief Comprehensive test suite for the codemasterspandas C++17 library.
 * @details Exercising core DataFrame and Series features, statistical 
 *          calculations, data transformations, file I/O, and error handling.
 * @date October 2026
 */

#include <codemasterspandas/codemasterspandas.hpp>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdexcept>

using namespace codemasterspandas;

// Using an anonymous namespace to keep helper utilities file-local
namespace {
    // Tracking the total number of assertions executed during the test run
    int checks = 0;

    /**
     * @brief Defining a custom assertion helper function.
     * @param condition The boolean expression being tested.
     * @param message Description of the test check for error tracking.
     * @throws std::runtime_error if the condition evaluates to false.
     */
    void require(bool condition, const char* message) {
        ++checks;
        if (!condition) {
            throw std::runtime_error(message);
        }
    }

    /**
     * @brief Comparing floating-point values using a fixed tolerance threshold.
     * @param actual The computed value from the library function.
     * @param expected The expected benchmark value.
     * @param message Description of the test check.
     * @throws std::runtime_error if the absolute difference exceeds 1e-8.
     */
    void near(double actual, double expected, const char* message) {
        require(std::abs(actual - expected) < 1e-8, message);
    }
}

int main() {
    try {
        // =========================================================================
        // 1. DATA INITIALIZATION
        // =========================================================================
        // Initializing a sample DataFrame with heterogeneous columns (team, score, name).
        // Note: Using synthetic student-score demonstration data, not real records.
        DataFrame frame({"team", "score", "name"}, {
            {std::string("A"), 10.0, std::string(" Mina ")},
            {std::string("B"), 20.0, std::string("JOHN")},
            {std::string("A"), 30.0, std::string("Lia")}
        });

        // =========================================================================
        // 2. STRUCTURAL & DIMENSIONAL INTEGRITY CHECKS
        // =========================================================================
        // Verifying that total row and column counts match the initialization size (3 rows, 3 cols)
        require(frame.rows() == 3 && frame.cols() == 3, "dimensions");
        
        // Testing row filtering: filtering rows where 'score' > 10 (expecting 2 matching rows)
        require(frame.filter("score", [](const Value& v){ return as_number(v) > 10; }).rows() == 2, "filter");
        
        // Testing sorting: sorting by 'score' in descending order and checking the top row score value
        near(as_number(frame.sort_by("score", false).at(0, "score")), 30, "descending sort");

        // =========================================================================
        // 3. STATISTICAL & AGGREGATION CHECKS
        // =========================================================================
        // Computing and validating central tendency and dispersion metrics on the 'score' column
        near(mean(frame.column("score")), 20, "mean");
        near(median(frame.column("score")), 20, "median");
        near(standard_deviation(frame.column("score")), std::sqrt(200.0 / 3.0), "population standard deviation");
        near(percentile(frame.column("score"), 25), 15, "percentile");
        
        // Testing bivariate statistics: calculating Pearson correlation between 'score' and a synthetic vector {2, 4, 6}
        near(correlation(frame.column("score"), Series("y", {2.0, 4.0, 6.0})), 1, "correlation");

        // =========================================================================
        // 4. GROUP-WISE OPERATIONS
        // =========================================================================
        // Grouping data by the 'team' column and testing group counts and aggregations
        require(group_count(frame, "team").at("A") == 2, "group count");
        near(group_sum(frame, "team", "score").at("A"), 40, "group sum");
        near(group_min(frame, "team", "score").at("A"), 10, "group minimum");
        near(group_max(frame, "team", "score").at("A"), 30, "group maximum");

        // =========================================================================
        // 5. BASIC SERIES METRICS
        // =========================================================================
        // Testing vector-level aggregation and non-missing element counts
        require(count(frame.column("name")) == 3, "non-missing count");
        near(sum(frame.column("score")), 60, "sum");
        near(minimum(frame.column("score")), 10, "minimum");
        near(maximum(frame.column("score")), 30, "maximum");

        // =========================================================================
        // 6. TRANSFORMATIONS & DATA CLEANING
        // =========================================================================
        // Testing string whitespace trimming, uppercase conversion, normalization, and standardization
        require(trim_strings(frame.column("name")).at(0) == Value(std::string("Mina")), "trim transform");
        require(uppercase(frame.column("name")).at(0) == Value(std::string(" MINA ")), "uppercase transform");
        require(normalize(frame.column("score")).at(0) == Value(0.0), "normalize");
        
        // Testing type casting: converting string series to numeric values while handling parse failures as missing
        require(to_numeric(Series("text", {std::string("12"), std::string("oops")})).at(0) == Value(12.0), "numeric conversion");
        require(std::holds_alternative<std::monostate>(to_numeric(Series("text", {std::string("oops")})).at(0)), "invalid numeric conversion becomes missing");
        
        // Testing constant standardization and series slicing range boundaries
        require(standardize(Series("constant", {4.0, 4.0})).at(0) == Value(0.0), "constant standardization");
        require(Series("letters", {1, 2, 3}).slice(1, 3).size() == 2, "series slice");
        
        // Testing dynamic column addition (`with_column`) to compute a derived column (score * 2)
        require(frame.with_column("double", [](const auto& row){ return as_number(row[1]) * 2; }).cols() == 4, "derived column");

        // =========================================================================
        // 7. RESHAPING (WIDE-TO-LONG)
        // =========================================================================
        // Reshaping the DataFrame from wide format to long format using `melt`
        auto long_frame = melt(frame, {"team"}, {"score", "name"}, "field", "entry");
        require(long_frame.rows() == 6 && long_frame.cols() == 3, "wide to long reshape");

        // =========================================================================
        // 8. SERIALIZATION (CSV & JSON ROUNDTRIP)
        // =========================================================================
        // Testing writing the DataFrame to CSV, reading it back, validating integrity, and cleaning up
        write_csv(frame, "test_roundtrip.csv");
        auto csv = read_csv("test_roundtrip.csv");
        require(csv.rows() == 3 && csv.at(1, "name") == Value(std::string("JOHN")), "CSV round trip");
        std::remove("test_roundtrip.csv");

        // Testing writing the DataFrame to JSON, reading it back, validating integrity, and cleaning up
        write_json(frame, "test_roundtrip.json");
        auto json = read_json("test_roundtrip.json");
        require(json.rows() == 3 && json.at(2, "team") == Value(std::string("A")), "JSON round trip");
        std::remove("test_roundtrip.json");

        // =========================================================================
        // 9. ERROR HANDLING & EXCEPTION SAFETY
        // =========================================================================
        // Verifying that accessing non-existent columns throws an out_of_range exception
        bool threw = false;
        try { frame.column("missing"); } catch (const std::out_of_range&) { threw = true; }
        require(threw, "invalid column error");

        // Verifying that out-of-bounds slicing triggers an out_of_range exception
        threw = false;
        try { frame.slice(0, 9); } catch (const std::out_of_range&) { threw = true; }
        require(threw, "invalid slice error");

        // Verifying that out-of-range quantiles trigger an invalid_argument exception
        threw = false;
        try { quantile(frame.column("score"), 2.0); } catch (const std::invalid_argument&) { threw = true; }
        require(threw, "invalid quantile error");

        // =========================================================================
        // 10. SUCCESS TERMINATION
        // =========================================================================
        std::cout << "All " << checks << " checks passed successfully.\n";
        return 0;

    } catch (const std::exception& error) {
        // Catching any assertion failure or unexpected exception, reporting the checkpoint count, and exiting with error code 1
        std::cerr << "Test failed after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
}