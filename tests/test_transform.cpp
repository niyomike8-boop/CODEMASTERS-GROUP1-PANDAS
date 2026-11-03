#include <codemasterspandas/codemasterspandas.hpp>

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace codemasterspandas;

namespace {

int checks = 0;

void require(bool condition, const std::string& message)
{
    ++checks;

    if (!condition)
        throw std::runtime_error(message);
}

void near(double actual, double expected, const std::string& message)
{
    require(std::abs(actual - expected) < 1e-8, message);
}

}

int main()
{
    try
    {
        // 1. NORMALIZATION
        Series scores("scores", {10.0, 20.0, 30.0});

        Series normalized = normalize(scores);

        near(as_number(normalized.at(0)), 0.0,
             "Minimum should normalize to 0");

        near(as_number(normalized.at(1)), 0.5,
             "Middle value should normalize to 0.5");

        near(as_number(normalized.at(2)), 1.0,
             "Maximum should normalize to 1");


        // Constant normalization
        Series constant("constant", {5.0, 5.0, 5.0});

        Series normalized_constant = normalize(constant);

        near(as_number(normalized_constant.at(0)), 0.0,
             "Constant normalization failed");


        // 2. STANDARDIZATION
        Series values("values", {10.0, 20.0, 30.0});

        Series standardized = standardize(values);

        near(mean(standardized), 0.0,
             "Standardized data should have mean 0");


        Series standardized_constant = standardize(constant);

        near(as_number(standardized_constant.at(0)), 0.0,
             "Constant standardization failed");


        // 3. STRING TO NUMERIC CONVERSION
        Series text_numbers(
            "text_numbers",
            {
                std::string("12"),
                std::string("3.5"),
                std::string("invalid")
            }
        );

        Series numeric = to_numeric(text_numbers);

        near(as_number(numeric.at(0)), 12.0,
             "Integer string conversion failed");

        near(as_number(numeric.at(1)), 3.5,
             "Decimal string conversion failed");

        require(
            std::holds_alternative<std::monostate>(numeric.at(2)),
            "Invalid number should become missing"
        );


        // 4. CONVERSION TO STRING
        Series mixed(
            "mixed",
            {
                25,
                3.5,
                true,
                std::string("Arthur")
            }
        );

        Series strings = to_string_series(mixed);

        require(
            std::holds_alternative<std::string>(strings.at(0)),
            "Integer should convert to string"
        );

        require(
            std::holds_alternative<std::string>(strings.at(1)),
            "Double should convert to string"
        );

        require(
            std::holds_alternative<std::string>(strings.at(2)),
            "Boolean should convert to string"
        );


        // 5. LOWERCASE
        Series names(
            "names",
            {
                std::string("ARTHUR"),
                std::string("JoHn"),
                std::string("MARY")
            }
        );

        Series lower = lowercase(names);

        require(
            lower.at(0) == Value(std::string("arthur")),
            "Lowercase conversion failed"
        );

        require(
            lower.at(1) == Value(std::string("john")),
            "Mixed-case lowercase conversion failed"
        );


        // 6. UPPERCASE
        Series upper = uppercase(names);

        require(
            upper.at(0) == Value(std::string("ARTHUR")),
            "Uppercase conversion failed"
        );

        require(
            upper.at(1) == Value(std::string("JOHN")),
            "Mixed-case uppercase conversion failed"
        );


        // 7. TRIMMING STRINGS
        Series dirty(
            "dirty",
            {
                std::string("   Arthur   "),
                std::string(" John"),
                std::string("Mary "),
                std::string("     ")
            }
        );

        Series clean = trim_strings(dirty);

        require(
            clean.at(0) == Value(std::string("Arthur")),
            "Trim both sides failed"
        );

        require(
            clean.at(1) == Value(std::string("John")),
            "Trim left side failed"
        );

        require(
            clean.at(2) == Value(std::string("Mary")),
            "Trim right side failed"
        );

        require(
            clean.at(3) == Value(std::string("")),
            "Blank string trimming failed"
        );


        std::cout
            << "All "
            << checks
            << " transformation tests passed.\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Transformation test failed after "
            << checks
            << " checks: "
            << error.what()
            << '\n';

        return 1;
    }
}
