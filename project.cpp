#if __has_include("Statistics.h")
#include "Statistics.h"
#else
#include <vector>

class Statistics
{
public:
    static int count(const std::vector<double>& data);
    static double minimum(const std::vector<double>& data);
    static double maximum(const std::vector<double>& data);
    static double mean(const std::vector<double>& data);
    static double median(const std::vector<double>& data);
    static double standardDeviation(const std::vector<double>& data);
    static double correlation(const std::vector<double>& x, const std::vector<double>& y);
    static double quantile(const std::vector<double>& data, double q);
    static double percentile(const std::vector<double>& data, double p);
};
#endif

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <vector>

namespace
{
void validateFiniteData(const std::vector<double>& data)
{
    for (double value : data)
    {
        if (!std::isfinite(value))
        {
            throw std::invalid_argument(
                "Dataset values must be finite."
            );
        }
    }
}

double interpolate(double lower, double upper, long double fraction)
{
    long double value =
        (1.0L - fraction) * lower + fraction * upper;
    double result = static_cast<double>(value);

    if (!std::isfinite(result))
    {
        throw std::overflow_error(
            "The calculated statistic is outside the range of double."
        );
    }

    return result;
}
}


// --------------------------------------------------
// COUNT
// --------------------------------------------------

int Statistics::count(const std::vector<double>& data)
{
    if (data.size() > static_cast<std::size_t>(
            std::numeric_limits<int>::max()))
    {
        throw std::overflow_error(
            "Dataset is too large for the count return type."
        );
    }

    return static_cast<int>(data.size());
}


// --------------------------------------------------
// MINIMUM
// --------------------------------------------------

double Statistics::minimum(const std::vector<double>& data)
{
    if (data.empty())
    {
        throw std::invalid_argument(
            "Cannot find minimum of an empty dataset."
        );
    }

    validateFiniteData(data);
    return *std::min_element(data.begin(), data.end());
}


// --------------------------------------------------
// MAXIMUM
// --------------------------------------------------

double Statistics::maximum(const std::vector<double>& data)
{
    if (data.empty())
    {
        throw std::invalid_argument(
            "Cannot find maximum of an empty dataset."
        );
    }

    validateFiniteData(data);
    return *std::max_element(data.begin(), data.end());
}


// --------------------------------------------------
// MEAN
// --------------------------------------------------

double Statistics::mean(const std::vector<double>& data)
{
    if (data.empty())
    {
        throw std::invalid_argument(
            "Cannot calculate mean of an empty dataset."
        );
    }

    validateFiniteData(data);

    double scale = 0.0;
    for (double value : data)
    {
        scale = std::max(scale, std::fabs(value));
    }

    if (scale == 0.0)
    {
        return 0.0;
    }

    long double normalizedTotal = 0.0L;
    for (double value : data)
    {
        normalizedTotal += value / scale;
    }

    double result = static_cast<double>(
        (normalizedTotal / data.size()) * scale
    );

    if (!std::isfinite(result))
    {
        throw std::overflow_error(
            "The calculated mean is outside the range of double."
        );
    }

    return result;
}


// --------------------------------------------------
// MEDIAN
// --------------------------------------------------

double Statistics::median(const std::vector<double>& data)
{
    if (data.empty())
    {
        throw std::invalid_argument(
            "Cannot calculate median of an empty dataset."
        );
    }

    validateFiniteData(data);

    // Make a copy so that the original data is not changed.
    std::vector<double> sortedData = data;

    std::sort(
        sortedData.begin(),
        sortedData.end()
    );

    std::size_t n = sortedData.size();

    // Odd number of values
    if (n % 2 != 0)
    {
        return sortedData[n / 2];
    }

    // Even number of values
    return interpolate(
        sortedData[(n / 2) - 1],
        sortedData[n / 2],
        0.5L
    );
}


// --------------------------------------------------
// STANDARD DEVIATION
// --------------------------------------------------

double Statistics::standardDeviation(
    const std::vector<double>& data
)
{
    if (data.size() < 2)
    {
        throw std::invalid_argument(
            "At least two values are required "
            "to calculate standard deviation."
        );
    }

    validateFiniteData(data);

    double scale = 0.0;
    for (double value : data)
    {
        scale = std::max(scale, std::fabs(value));
    }

    if (scale == 0.0)
    {
        return 0.0;
    }

    long double runningMean = 0.0L;
    long double sumSquaredDifferences = 0.0L;
    for (std::size_t i = 0; i < data.size(); ++i)
    {
        long double value = data[i] / scale;
        long double difference = value - runningMean;
        runningMean += difference / static_cast<long double>(i + 1);
        sumSquaredDifferences +=
            difference * (value - runningMean);
    }

    long double normalizedDeviation = std::sqrt(
        sumSquaredDifferences /
        static_cast<long double>(data.size() - 1)
    );
    double result = static_cast<double>(normalizedDeviation * scale);

    if (!std::isfinite(result))
    {
        throw std::overflow_error(
            "The calculated standard deviation is outside the range of double."
        );
    }

    return result;
}


// --------------------------------------------------
// CORRELATION
// --------------------------------------------------

double Statistics::correlation(
    const std::vector<double>& x,
    const std::vector<double>& y
)
{
    if (x.size() != y.size())
    {
        throw std::invalid_argument(
            "The two datasets must have the same size."
        );
    }

    if (x.size() < 2)
    {
        throw std::invalid_argument(
            "At least two values are required "
            "to calculate correlation."
        );
    }

    validateFiniteData(x);
    validateFiniteData(y);

    double valueScaleX = 0.0;
    double valueScaleY = 0.0;
    for (std::size_t i = 0; i < x.size(); ++i)
    {
        valueScaleX = std::max(valueScaleX, std::fabs(x[i]));
        valueScaleY = std::max(valueScaleY, std::fabs(y[i]));
    }

    long double meanX = 0.0L;
    long double meanY = 0.0L;
    for (std::size_t i = 0; i < x.size(); ++i)
    {
        if (valueScaleX != 0.0)
        {
            meanX += (x[i] / valueScaleX) / x.size();
        }
        if (valueScaleY != 0.0)
        {
            meanY += (y[i] / valueScaleY) / y.size();
        }
    }

    long double scaleX = 0.0L;
    long double scaleY = 0.0L;

    for (std::size_t i = 0; i < x.size(); ++i)
    {
        long double differenceX = valueScaleX == 0.0
            ? 0.0L
            : (x[i] / valueScaleX) - meanX;
        long double differenceY = valueScaleY == 0.0
            ? 0.0L
            : (y[i] / valueScaleY) - meanY;

        scaleX = std::max(scaleX, std::fabs(differenceX));
        scaleY = std::max(scaleY, std::fabs(differenceY));
    }

    if (scaleX == 0.0L || scaleY == 0.0L)
    {
        throw std::invalid_argument(
            "Correlation is undefined when "
            "one dataset has zero variance."
        );
    }

    long double numerator = 0.0L;
    long double sumX = 0.0L;
    long double sumY = 0.0L;

    for (std::size_t i = 0; i < x.size(); ++i)
    {
        long double differenceX =
            ((x[i] / valueScaleX) - meanX) / scaleX;
        long double differenceY =
            ((y[i] / valueScaleY) - meanY) / scaleY;

        numerator += differenceX * differenceY;
        sumX += differenceX * differenceX;
        sumY += differenceY * differenceY;
    }

    long double denominator = std::sqrt(sumX) * std::sqrt(sumY);
    return static_cast<double>(numerator / denominator);
}


// --------------------------------------------------
// QUANTILE
// --------------------------------------------------

double Statistics::quantile(
    const std::vector<double>& data,
    double q
)
{
    if (data.empty())
    {
        throw std::invalid_argument(
            "Cannot calculate quantile of an empty dataset."
        );
    }

    if (!std::isfinite(q) || q < 0.0 || q > 1.0)
    {
        throw std::invalid_argument(
            "Quantile must be between 0 and 1."
        );
    }

    validateFiniteData(data);

    std::vector<double> sortedData = data;

    std::sort(
        sortedData.begin(),
        sortedData.end()
    );

    if (sortedData.size() == 1)
    {
        return sortedData[0];
    }

    // Position using linear interpolation
    long double position =
        static_cast<long double>(q) * (sortedData.size() - 1);

    std::size_t lower =
        static_cast<std::size_t>(std::floor(position));

    std::size_t upper =
        static_cast<std::size_t>(std::ceil(position));

    if (lower == upper)
    {
        return sortedData[lower];
    }

    long double fraction = position - lower;

    return interpolate(
        sortedData[lower], sortedData[upper], fraction
    );
}


// --------------------------------------------------
// PERCENTILE
// --------------------------------------------------

double Statistics::percentile(
    const std::vector<double>& data,
    double p
)
{
    if (!std::isfinite(p) || p < 0.0 || p > 100.0)
    {
        throw std::invalid_argument(
            "Percentile must be between 0 and 100."
        );
    }

    // Convert percentile to quantile
    double q = p / 100.0;

    return quantile(data, q);
}