#include <codemasterspandas/codemasterspandas.hpp>
#include <iostream>

int main() {
    using namespace codemasterspandas;
    DataFrame scores({"name", "class", "score"}, {
        {std::string("Amina"), std::string("A"), 82.0},
        {std::string("Brian"), std::string("B"), 74.0},
        {std::string("Diana"), std::string("A"), 91.0}
    });
    auto passing = scores.filter("score", [](const Value& value) {
        return is_numeric(value) && as_number(value) >= 80.0;
    }).sort_by("score", false);
    std::cout << "Students scoring at least 80:\n" << passing.to_string();
    std::cout << "Mean score: " << mean(scores.column("score")) << '\n';
    std::cout << "Score totals by class:\n";
    for (const auto& group : group_sum(scores, "class", "score"))
        std::cout << "  " << group.first << ": " << group.second << '\n';
}
