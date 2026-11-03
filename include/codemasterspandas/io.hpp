#pragma once

#include "codemasterspandas/dataframe.hpp"

#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace codemasterspandas {

// Basic statistics
std::size_t count(const Series& series);
double sum(const Series& series);
double minimum(const Series& series);
double maximum(const Series& series);
double mean(const Series& series);
double median(const Series& series);

double standard_deviation(
    const Series& series,
    bool sample = false
);

double quantile(
    const Series& series,
    double q
);

double percentile(
    const Series& series,
    double p
);

double correlation(
    const Series& left,
    const Series& right
);

// Grouped statistics
std::map<std::string, double> group_sum(
    const DataFrame& frame,
    const std::string& group_column,
    const std::string& value_column
);

std::map<std::string, double> group_min(
    const DataFrame& frame,
    const std::string& group_column,
    const std::string& value_column
);

std::map<std::string, double> group_max(
    const DataFrame& frame,
    const std::string& group_column,
    const std::string& value_column
);

std::map<std::string, std::size_t> group_count(
    const DataFrame& frame,
    const std::string& group_column
);

// Template function for numerical data types
template <typename T>
double numeric_mean(const std::vector<T>& data)
{
    static_assert(
        std::is_arithmetic_v<T>,
        "numeric_mean requires a numerical data type"
    );

    if (data.empty())
    {
        throw std::invalid_argument(
            "Data cannot be empty"
        );
    }

    double total = 0.0;

    for (const T& value : data)
    {
        total += static_cast<double>(value);
    }

    return total / static_cast<double>(data.size());
}

} // namespace codemasterspandas
