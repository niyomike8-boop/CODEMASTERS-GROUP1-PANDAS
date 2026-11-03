#include "codemasterspandas/statistics.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace codemasterspandas {

namespace {

// Extract only numerical values from a Series
std::vector<double> numbers(const Series& series)
{
    std::vector<double> result;

    for (const auto& value : series.values())
    {
        if (is_numeric(value))
        {
            result.push_back(as_number(value));
        }
    }

    return result;
}

} 

// COUNT


std::size_t count(const Series& series)
{
    return static_cast<std::size_t>(
        std::count_if(
            series.values().begin(),
            series.values().end(),
            [](const Value& value)
            {
                return !std::holds_alternative<std::monostate>(value);
            }
        )
    );
}

// SUM


double sum(const Series& series)
{
    const auto values = numbers(series);

    return std::accumulate(
        values.begin(),
        values.end(),
        0.0
    );
}

// MINIMUM


double minimum(const Series& series)
{
    const auto values = numbers(series);

    if (values.empty())
    {
        throw std::domain_error(
            "minimum requires a numeric value"
        );
    }

    return *std::min_element(
        values.begin(),
        values.end()
    );
}
// MAXIMUM


double maximum(const Series& series)
{
    const auto values = numbers(series);

    if (values.empty())
    {
        throw std::domain_error(
            "maximum requires a numeric value"
        );
    }

    return *std::max_element(
        values.begin(),
        values.end()
    );
}

// MEAN


double mean(const Series& series)
{
    const auto values = numbers(series);

    if (values.empty())
    {
        throw std::domain_error(
            "mean requires a numeric value"
        );
    }

    const double total = std::accumulate(
        values.begin(),
        values.end(),
        0.0
    );

    return total / static_cast<double>(values.size());
}

// QUANTILE


double quantile(const Series& series, double q)
{
    if (q < 0.0 || q > 1.0)
    {
        throw std::invalid_argument(
            "quantile must be in [0,1]"
        );
    }

    auto values = numbers(series);

    if (values.empty())
    {
        throw std::domain_error(
            "quantile requires a numeric value"
        );
    }

    std::sort(values.begin(), values.end());

    const double index =
        q * static_cast<double>(values.size() - 1);

    const auto lower =
        static_cast<std::size_t>(index);

    const auto upper =
        static_cast<std::size_t>(std::ceil(index));

    return values[lower] +
           (values[upper] - values[lower]) *
           (index - static_cast<double>(lower));
}

// MEDIAN


double median(const Series& series)
{
    return quantile(series, 0.5);
}

// PERCENTILE


double percentile(const Series& series, double p)
{
    if (p < 0.0 || p > 100.0)
    {
        throw std::invalid_argument(
            "percentile must be in [0,100]"
        );
    }

    return quantile(series, p / 100.0);
}

// STANDARD DEVIATION


double standard_deviation(
    const Series& series,
    bool sample
)
{
    const auto values = numbers(series);

    if (values.empty() ||
        (sample && values.size() < 2))
    {
        throw std::domain_error(
            "not enough values for standard deviation"
        );
    }

    const double average =
        std::accumulate(
            values.begin(),
            values.end(),
            0.0
        ) / static_cast<double>(values.size());

    double squared_difference_sum = 0.0;

    for (double value : values)
    {
        const double difference =
            value - average;

        squared_difference_sum +=
            difference * difference;
    }

    const double denominator =
        static_cast<double>(
            values.size() - (sample ? 1 : 0)
        );

    return std::sqrt(
        squared_difference_sum / denominator
    );
}

// CORRELATION

double correlation(
    const Series& left,
    const Series& right
)
{
    if (left.size() != right.size())
    {
        throw std::invalid_argument(
            "series lengths differ"
        );
    }

    std::vector<std::pair<double, double>> pairs;

    for (std::size_t i = 0; i < left.size(); ++i)
    {
        if (is_numeric(left.at(i)) &&
            is_numeric(right.at(i)))
        {
            pairs.emplace_back(
                as_number(left.at(i)),
                as_number(right.at(i))
            );
        }
    }

    if (pairs.size() < 2)
    {
        throw std::domain_error(
            "correlation requires two paired numeric values"
        );
    }

    double left_mean = 0.0;
    double right_mean = 0.0;

    for (const auto& pair : pairs)
    {
        left_mean += pair.first;
        right_mean += pair.second;
    }

    left_mean /= static_cast<double>(pairs.size());
    right_mean /= static_cast<double>(pairs.size());

    double covariance = 0.0;
    double left_variance = 0.0;
    double right_variance = 0.0;

    for (const auto& pair : pairs)
    {
        const double x =
            pair.first - left_mean;

        const double y =
            pair.second - right_mean;

        covariance += x * y;
        left_variance += x * x;
        right_variance += y * y;
    }

    if (left_variance == 0.0 ||
        right_variance == 0.0)
    {
        throw std::domain_error(
            "correlation is undefined for constant values"
        );
    }

    return covariance /
           std::sqrt(
               left_variance * right_variance
           );
}

// GROUP SUM


std::map<std::string, double> group_sum(
    const DataFrame& frame,
    const std::string& group_column,
    const std::string& value_column
)
{
    std::map<std::string, double> result;

    for (std::size_t i = 0; i < frame.rows(); ++i)
    {
        const Value value =
            frame.at(i, value_column);

        if (is_numeric(value))
        {
            const std::string key =
                value_to_string(
                    frame.at(i, group_column)
                );

            result[key] += as_number(value);
        }
    }

    return result;
}

// GROUP MINIMUM


std::map<std::string, double> group_min(
    const DataFrame& frame,
    const std::string& group_column,
    const std::string& value_column
)
{
    std::map<std::string, double> result;

    for (std::size_t i = 0; i < frame.rows(); ++i)
    {
        const Value value =
            frame.at(i, value_column);

        if (!is_numeric(value))
        {
            continue;
        }

        const std::string key =
            value_to_string(
                frame.at(i, group_column)
            );

        const double number =
            as_number(value);

        const auto found =
            result.find(key);

        if (found == result.end() ||
            number < found->second)
        {
            result[key] = number;
        }
    }

    return result;
}

// GROUP MAXIMUM


std::map<std::string, double> group_max(
    const DataFrame& frame,
    const std::string& group_column,
    const std::string& value_column
)
{
    std::map<std::string, double> result;

    for (std::size_t i = 0; i < frame.rows(); ++i)
    {
        const Value value =
            frame.at(i, value_column);

        if (!is_numeric(value))
        {
            continue;
        }

        const std::string key =
            value_to_string(
                frame.at(i, group_column)
            );

        const double number =
            as_number(value);

        const auto found =
            result.find(key);

        if (found == result.end() ||
            number > found->second)
        {
            result[key] = number;
        }
    }

    return result;
}

// GROUP COUNT


std::map<std::string, std::size_t> group_count(
    const DataFrame& frame,
    const std::string& group_column
)
{
    std::map<std::string, std::size_t> result;

    for (std::size_t i = 0; i < frame.rows(); ++i)
    {
        const std::string key =
            value_to_string(
                frame.at(i, group_column)
            );

        ++result[key];
    }

    return result;
}

}