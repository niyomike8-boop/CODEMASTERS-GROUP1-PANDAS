#pragma once

#include "codemasterspandas/dataframe.hpp"
#include <string>

namespace codemasterspandas {

/// Read/write simple CSV files. The first row contains column names.
DataFrame read_csv(const std::string& path);
void write_csv(const DataFrame& frame, const std::string& path);
/// Read/write a JSON array of objects with scalar values.
DataFrame read_json(const std::string& path);
void write_json(const DataFrame& frame, const std::string& path);

} // namespace codemasterspandas
