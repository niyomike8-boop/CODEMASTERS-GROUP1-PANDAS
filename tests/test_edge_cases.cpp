// Robertbob Murungi
// Contribution: Edge-case testing for CodeMasters Pandas

#include <codemasterspandas/codemasterspandas.hpp>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <variant>

using namespace codemasterspandas;

int checks = 0;

void require(bool condition, const std::string& message)
{
    ++checks;

    if (!condition)
    {
        throw std::runtime_error(message);
    }
}

int main()
{
    try
    {
        // TEST 1: Filter where no rows match

        DataFrame employees(
            {"name", "salary"},
            {
                {std::string("Robert"), 1500000.0},
                {std::string("Amina"), 1800000.0},
                {std::string("John"), 1200000.0}
            }
        );

        DataFrame filtered =
            employees.filter(
                "salary",
                [](const Value& value)
                {
                    return is_numeric(value) &&
                           as_number(value) > 5000000.0;
                }
            );

        require(
            filtered.rows() == 0,
            "Filter with no matches failed"
        );

        // TEST 2: Invalid percentile
    

        Series scores(
            "scores",
            {60.0, 70.0, 80.0, 90.0}
        );

        bool percentileError = false;

        try
        {
            percentile(scores, 120.0);
        }
        catch (const std::invalid_argument&)
        {
            percentileError = true;
        }

        require(
            percentileError,
            "Percentile above 100 should produce an error"
        );

        // TEST 3: Negative percentile

        bool negativePercentileError = false;

        try
        {
            percentile(scores, -10.0);
        }
        catch (const std::invalid_argument&)
        {
            negativePercentileError = true;
        }

        require(
            negativePercentileError,
            "Negative percentile should produce an error"
        );

        // TEST 4: Normalize constant values

        Series constantValues(
            "constant",
            {50.0, 50.0, 50.0}
        );

        Series normalized =
            normalize(constantValues);

        require(
            normalized.at(0) == Value(0.0),
            "Constant values should normalize to zero"
        );

        require(
            normalized.at(1) == Value(0.0),
            "Constant normalization failed"
        );

        // TEST 5: Convert valid strings to numbers

        Series numberText(
            "numbers",
            {
                std::string("25"),
                std::string("42.5")
            }
        );

        Series converted =
            to_numeric(numberText);

        require(
            converted.at(0) == Value(25.0),
            "Integer string conversion failed"
        );

        require(
            converted.at(1) == Value(42.5),
            "Decimal string conversion failed"
        );

        // TEST 6: Invalid numeric conversion

        Series invalidNumber(
            "invalid",
            {
                std::string("Robert")
            }
        );

        Series invalidConverted =
            to_numeric(invalidNumber);

        require(
            std::holds_alternative<std::monostate>(
                invalidConverted.at(0)
            ),
            "Invalid text should become a missing value"
        );

        // TEST 7: Trim spaces

        Series names(
            "names",
            {
                std::string("   Robert Bob   "),
                std::string("  Amina"),
                std::string("  Mukose")
            }
        );

        Series trimmed =
            trim_strings(names);

        require(
            trimmed.at(0) ==
                Value(std::string("Robert Bob")),
            "Trim failed for both sides"
        );

        require(
            trimmed.at(1) ==
                Value(std::string("Amina")),
            "Leading spaces were not removed"
        );

        require(
            trimmed.at(2) ==
                Value(std::string("Mukose")),
            "Trailing spaces were not removed"
        );

        // TEST 8: Uppercase transformation

        Series words(
            "words",
            {
                std::string("robert"),
                std::string("codemasters")
            }
        );

        Series upper =
            uppercase(words);

        require(
            upper.at(0) ==
                Value(std::string("ROBERT")),
            "Uppercase conversion failed"
        );

        require(
            upper.at(1) ==
                Value(std::string("CODEMASTERS")),
            "Uppercase conversion failed"
        );
        // TEST 9: Missing CSV file

        bool missingFileError = false;

        try
        {
            read_csv(
                "file_that_does_not_exist.csv"
            );
        }
        catch (const std::runtime_error&)
        {
            missingFileError = true;
        }

        require(
            missingFileError,
            "Missing CSV file should produce an error"
        );

        // TEST 10: CSV with wrong number of fields

        {
            std::ofstream file(
                "robert_bad_test.csv"
            );

            file << "name,age,department\n";
            file << "Robert,24\n";

            file.close();

            bool csvError = false;

            try
            {
                read_csv(
                    "robert_bad_test.csv"
                );
            }
            catch (const std::runtime_error&)
            {
                csvError = true;
            }

            require(
                csvError,
                "Invalid CSV should produce an error"
            );

            std::remove(
                "robert_bad_test.csv"
            );
        }

        // TEST 11: CSV quoted comma

        {
            std::ofstream file(
                "robert_comma_test.csv"
            );

            file << "name,department\n";
            file << "\"Robert, Bob\",Engineering\n";

            file.close();

            DataFrame csvData =
                read_csv(
                    "robert_comma_test.csv"
                );

            require(
                csvData.at(0, "name") ==
                    Value(
                        std::string("Robert, Bob")
                    ),
                "Quoted comma was not handled correctly"
            );

            std::remove(
                "robert_comma_test.csv"
            );
        }

        // TEST 12: CSV write and read


        DataFrame original(
            {"name", "score"},
            {
                {std::string("Robert"), 82.0},
                {std::string("Amina"), 91.0}
            }
        );

        write_csv(
            original,
            "robert_roundtrip.csv"
        );

        DataFrame loaded =
            read_csv(
                "robert_roundtrip.csv"
            );

        require(
            loaded.rows() == 2,
            "CSV round trip changed row count"
        );

        require(
            loaded.at(0, "name") ==
                Value(std::string("Robert")),
            "CSV round trip changed data"
        );

        std::remove(
            "robert_roundtrip.csv"
        );


        
        // TEST 13: Correlation length mismatch
    

        Series x(
            "x",
            {1.0, 2.0, 3.0}
        );

        Series y(
            "y",
            {2.0, 4.0}
        );

        bool correlationError = false;

        try
        {
            correlation(x, y);
        }
        catch (const std::invalid_argument&)
        {
            correlationError = true;
        }

        require(
            correlationError,
            "Correlation should reject different Series lengths"
        );


    
        // TEST 14: Constant correlation


        Series constantX(
            "x",
            {5.0, 5.0, 5.0}
        );

        Series changingY(
            "y",
            {1.0, 2.0, 3.0}
        );

        bool constantCorrelationError = false;

        try
        {
            correlation(
                constantX,
                changingY
            );
        }
        catch (const std::domain_error&)
        {
            constantCorrelationError = true;
        }

        require(
            constantCorrelationError,
            "Correlation should reject constant values"
        );
        // FINAL RESULT

        std::cout
            << "\nRobertbob Murungi test contribution completed.\n";

        std::cout
            << "All "
            << checks
            << " edge-case checks passed.\n";

        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "\nTest failed after "
            << checks
            << " checks.\n";

        std::cerr
            << "Reason: "
            << error.what()
            << '\n';

        return 1;
    }
}