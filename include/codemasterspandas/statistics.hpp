#pragma once

#include "codemasterspandas/dataframe.hpp"
#include <map>
#include <string>
#include <vector>

namespace codemasterspandas {

std::size_t count(const Series& series);
double sum(const Series& series);
double minimum(const Series& series);
double maximum(const Series& series);
double mean(const Series& series);
double median(const Series& series);
double standard_deviation(const Series& series, bool sample = false);
double quantile(const Series& series, double q);
double percentile(const Series& series, double p);
double correlation(const Series& left, const Series& right);
/// Return group label -> aggregate for a numeric column.
std::map<std::string, double> group_sum(const DataFrame& frame,
                                       const std::string& group_column,
                                       const std::string& value_column);
std::map<std::string, double> group_min(const DataFrame& frame,
                                       const std::string& group_column,
                                       const std::string& value_column);
std::map<std::string, double> group_max(const DataFrame& frame,
                                       const std::string& group_column,
                                       const std::string& value_column);
std::map<std::string, std::size_t> group_count(const DataFrame& frame,
                                              const std::string& group_column);

} // namespace codemasterspandas
