# Library module guide

The project uses C++17 and has no third-party dependencies. Public declarations live in `include/codemasterspandas/`; corresponding implementation files are in `src/`.

## Values and Series

`Value` is a tagged union of missing, integer, double, Boolean, and string cells. `Series` owns a name and an ordered vector of values. It provides checked indexing, slicing, mapping, and filtering. Numeric helpers reject non-numeric inputs rather than silently coercing them.

## DataFrame

`DataFrame` stores columns as `Series` objects. Every column has the same length. Construct a frame from names and row vectors, then access columns by name. Selection, slicing, filtering, sorting, and derived-column operations return a new frame, which keeps those operations easy to chain.

`melt` reshapes selected wide columns to variable/value rows while carrying identifier columns through the result.

## Input and output

`read_csv` and `write_csv` handle a header row, commas, quotes, and escaped quote characters. `read_json` and `write_json` support an array of objects with scalar values. These readers intentionally cover the project's sample-data format, not every feature in the CSV or JSON standards.

## Statistics and grouping

Statistics skip missing and non-numeric cells. `count` counts all non-missing cells; numeric aggregates use integer and double cells. Quantiles use linear interpolation between neighboring sorted values. Standard deviation defaults to the population formula; pass `true` for the sample formula. Correlation uses rows where both series have numeric values and reports an error for too few pairs or a constant series.

`group_sum` aggregates numeric cells by a string representation of each group value. `group_count` counts rows in each group.

## Transformations

`normalize` rescales numeric values to [0, 1], and `standardize` uses the population mean and standard deviation. `to_numeric` converts parseable values and marks unparseable values missing. String helpers only modify string cells.

## Errors and current scope

Invalid column names and indices throw standard exceptions. A `DataFrame` cannot contain duplicate or differently sized columns. Date/time types, joins, arbitrary JSON nesting, locale-specific number formats, and full pandas compatibility are outside this teaching project's current scope.
