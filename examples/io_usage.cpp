#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>//

int main(int argc, char** argv) {
    using namespace codemasterspandas;//

    const std::string input = argc > 1 ? argv[1] : "data/input/student_scores.csv";
    try {
        auto frame = read_csv(input);
        std::cout << "Loaded " << frame.rows() << " rows and " << frame.cols() << " columns\n";
        std::cout << frame.to_string();
        
        write_json(frame, "data/output/student_scores.json");
        std::cout << "Wrote data/output/student_scores.json\n";
    } catch (const std::exception& error) {
        std::cerr << "Could not process input: " << error.what() << '\n';
        return 1;
    }
}
