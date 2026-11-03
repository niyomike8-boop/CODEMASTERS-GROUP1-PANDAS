# Week 2 Progress Report

**Project:** CODEMASTERS-GROUP1-PANDAS  
**Member:** Ninsiima Aurthur  
**Branch:** `ninsiima-aurthur`

## Work Completed

During this week, I implemented the transformation module assigned to me.

The following functions were implemented:

- `normalize()`
- `standardize()`
- `to_numeric()`
- `to_string_series()`
- `lowercase()`
- `uppercase()`
- `trim_strings()`

The function declarations were placed in:

`include/codemasterspandas/transform.hpp`

The implementations were placed in:

`src/transform.cpp`

## Normalization

I implemented normalization to scale numeric values to the range 0 to 1.

The function uses the minimum and maximum values of the series and also handles constant values safely to avoid division by zero.

## Standardization

I implemented standardization using the mean and standard deviation of the numeric values.

A constant series with zero standard deviation is handled safely by returning zero for its standardized values.

## Type Conversion

The `to_numeric()` function converts values that can be interpreted as numbers into numeric values.

Values that cannot be converted are represented as missing values.

The `to_string_series()` function converts supported values into their string representations.

## String Transformations

I implemented functions for:

- converting strings to lowercase;
- converting strings to uppercase;
- removing spaces from the beginning and end of strings.

## Challenges

The main challenge was ensuring that transformations worked correctly with different value types while preserving missing and non-applicable values.

## What I Learned

I improved my understanding of C++ functions, lambdas, `std::variant`, string manipulation, and working with values stored inside a `Series`.

## Next Week

I planned to test the transformation functions, review edge cases, and integrate my work with the other project modules.
