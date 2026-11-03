#pragma once

#include "codemasterspandas/dataframe.hpp"
#include <string>

namespace codemasterspandas {

// Reads data from a CSV file and returns it as a DataFrame
DataFrame read_csv(const std::string& path);

// Writes a DataFrame to a CSV file
void write_csv(const DataFrame& frame, const std::string& path);

// Reads data from a JSON file and returns it as a DataFrame
DataFrame read_json(const std::string& path);

// Writes a DataFrame to a JSON file
void write_json(const DataFrame& frame, const std::string& path);


// Base class for all data exporters.
// It provides a common interface for exporting data.
class DataExporter {
public:

    // Pure virtual function.
    // Each derived class must define how it exports the data.
    virtual void exportData(
        const DataFrame& data,
        const std::string& path
    ) = 0;

    // Virtual destructor allows safe deletion through base-class pointers.
    virtual ~DataExporter() = default;
};


// CSVExporter inherits from DataExporter.
// It exports a DataFrame in CSV format.
class CSVExporter : public DataExporter {
public:

    // Overrides the exportData() function from DataExporter.
    void exportData(
        const DataFrame& data,
        const std::string& path
    ) override;
};


// JSONExporter also inherits from DataExporter.
// It exports a DataFrame in JSON format.
class JSONExporter : public DataExporter {
public:

    // Overrides the exportData() function for JSON files.
    void exportData(
        const DataFrame& data,
        const std::string& path
    ) override;
};

} // namespace codemasterspandas
