#include "codemasterspandas/io.hpp" 
#include <algorithm> 
#include <cctype> 
#include <fstream> 
#include <sstream> 
#include <stdexcept> 

namespace codemasterspandas { 

namespace { 

std::vector<std::string> parse_csv_line(const std::string& line) { 
    std::vector<std::string> fields; 
    std::string field;
    bool quoted = false;

    for (std::size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (quoted) {
            if (c == '"' && i + 1 < line.size() && line[i + 1] == '"') { 
                field += '"';
                ++i;
            } else if (c == '"') { 
                quoted = false;
            } else {
                field += c;
            } 
        } else if (c == '"') { 
            quoted = true;
        } else if (c == ',') {
            fields.push_back(field); 
            field.clear();
        } else {
            field += c; 
        } 
    }

    if (quoted)
        throw std::runtime_error("unterminated quoted CSV field"); 

    fields.push_back(field);
    return fields;
}

std::string csv_escape(const std::string& value) {
    if (value.find_first_of(",\"\r\n") == std::string::npos) 
        return value;

    std::string out = "\""; 
    for (char c : value) {
        if (c == '"') out += '"'; 
        out += c;
    }
    return out + '"'; 
}

std::string read_all(const std::string& path) { 
    std::ifstream in(path); 

    if (!in)
        throw std::runtime_error("cannot open input file: " + path);

    std::ostringstream out; 
    out << in.rdbuf(); 
    return out.str(); 
}

std::string json_escape(const std::string& text) { 
    std::string out;

    for (char c : text) {
        if (c == '"' || c == '\\') out += '\\'; 

        if (c == '\n') out += "\\n";
        else if (c == '\r') out += "\\r";
        else out += c;
    }

    return out; 
}

class JsonRows {
private: 
    std::string text;
    std::size_t pos = 0;

    void skip() {
        while (pos < text.size() &&
               std::isspace(static_cast<unsigned char>(text[pos]))) 
            ++pos;
    }

    bool take(char c) {
        skip();

        if (pos < text.size() && text[pos] == c) {
            ++pos;
            return true;
        }

        return false;
    }

    void expect(char c) {
        if (!take(c))
            throw std::runtime_error("invalid JSON");
    }

    std::string read_string() {
        expect('"');
        std::string result;

        while (pos < text.size()) {
            char c = text[pos++];

            if (c == '"')
                return result;

            if (c == '\\' && pos < text.size()) {
                char next = text[pos++];

                if (next == 'n') result += '\n';
                else if (next == 'r') result += '\r';
                else if (next == 't') result += '\t';
                else result += next;
            } else {
                result += c;
            }
        }

        throw std::runtime_error("unterminated JSON string");
    }

    Value read_value() {
        skip();

        if (text[pos] == '"')
            return read_string();

        std::size_t start = pos;

        while (pos < text.size() &&
               text[pos] != ',' &&
               text[pos] != '}' &&
               !std::isspace(static_cast<unsigned char>(text[pos])))
            ++pos;

        std::string value = text.substr(start, pos - start);

        if (value == "null") return std::monostate{};
        if (value == "true") return true;
        if (value == "false") return false;

        return parse_value(value);
    }

public:
    explicit JsonRows(std::string data) : text(std::move(data)) {}

    DataFrame parse() {
        expect('[');
        skip();

        if (take(']'))
            return {};

        std::vector<std::string> names;
        std::vector<std::vector<Value>> rows;

        do {
            expect('{');

            std::vector<std::pair<std::string, Value>> values;

            if (!take('}')) {
                do {
                    std::string key = read_string();
                    expect(':');
                    values.emplace_back(key, read_value());
                } while (take(','));

                expect('}');
            }

            if (names.empty()) {
                for (const auto& item : values)
                    names.push_back(item.first);
            }

            std::vector<Value> row(names.size());

            for (const auto& item : values) {
                auto it = std::find(names.begin(), names.end(), item.first);

                if (it == names.end())
                    throw std::runtime_error("JSON objects must have the same keys");

                row[it - names.begin()] = item.second;
            }

            rows.push_back(row);

        } while (take(','));

        expect(']');

        return DataFrame(names, rows);
    }
};

} // anonymous namespace


DataFrame read_csv(const std::string& path) {
    std::ifstream in(path);

    if (!in)
        throw std::runtime_error("cannot open input file: " + path);

    std::string line;

    if (!std::getline(in, line))
        return {};

    auto names = parse_csv_line(line);
    std::vector<std::vector<Value>> rows;

    while (std::getline(in, line)) {
        auto fields = parse_csv_line(line);

        if (fields.size() != names.size())
            throw std::runtime_error("CSV row has wrong number of fields"); 

        std::vector<Value> row;

        for (const auto& field : fields) 
            row.push_back(parse_value(field));

        rows.push_back(row);
    }

    return DataFrame(names, rows);
}


void write_csv(const DataFrame& frame, const std::string& path) {
    std::ofstream out(path);

    if (!out)
        throw std::runtime_error("cannot open output file: " + path);

    for (std::size_t c = 0; c < frame.cols(); ++c) {
        if (c) out << ',';
        out << csv_escape(frame.columns()[c]);
    }

    out << '\n';

    for (std::size_t r = 0; r < frame.rows(); ++r) {
        for (std::size_t c = 0; c < frame.cols(); ++c) {
            if (c) out << ',';

            out << csv_escape(
                value_to_string(
                    frame.column(frame.columns()[c]).at(r)
                )
            );
        }

        out << '\n';
    }
}


DataFrame read_json(const std::string& path) {
    return JsonRows(read_all(path)).parse();
}


void write_json(const DataFrame& frame, const std::string& path) {
    std::ofstream out(path);

    if (!out)
        throw std::runtime_error("cannot open output file: " + path);

    out << "[\n";

    for (std::size_t r = 0; r < frame.rows(); ++r) {
        out << "  {";

        for (std::size_t c = 0; c < frame.cols(); ++c) {
            if (c) out << ", ";

            const auto& name = frame.columns()[c];
            const auto& value = frame.column(name).at(r);

            out << '"' << json_escape(name) << "\": ";

            if (std::holds_alternative<std::monostate>(value))
                out << "null";
            else if (std::holds_alternative<std::string>(value))
                out << '"' << json_escape(std::get<std::string>(value)) << '"';
            else
                out << value_to_string(value);
        }

        out << '}' << (r + 1 == frame.rows() ? "\n" : ",\n");
    }

    out << "]\n";
}


// Inheritance and polymorphism implementations

void CSVExporter::exportData(const DataFrame& data, const std::string& path) {
    write_csv(data, path);
}

void JSONExporter::exportData(const DataFrame& data, const std::string& path) {
    write_json(data, path);
}

} // namespace codemasterspandas