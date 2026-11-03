#pragma once

#include "codemasterspandas/dataframe.hpp"

namespace codemasterspandas {

Series normalize(const Series& series);
Series standardize(const Series& series);
Series to_numeric(const Series& series);
Series to_string_series(const Series& series);
Series lowercase(const Series& series);
Series uppercase(const Series& series);
Series trim_strings(const Series& series);

} // namespace codemasterspandas
