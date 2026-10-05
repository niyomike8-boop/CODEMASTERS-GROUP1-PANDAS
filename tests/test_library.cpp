//
#include <codemasterspandas/codemasterspandas.hpp>
//
#include <cmath>
//
#include <cstdio>
//
#include <iostream>
//
#include <stdexcept>


using namespace codemasterspandas;
namespace {
int checks = 0;
void require(bool condition, const char* message) { ++checks; if (!condition) throw std::runtime_error(message); }

void near(double actual, double expected, const char* message) { require(std::abs(actual-expected)<1e-8, message); }
}

int main() {
    try {
        DataFrame frame({"team", "score", "name"}, {
            {std::string("A"), 10.0, std::string(" Mina ")},
            {std::string("B"), 20.0, std::string("JOHN")},
            {std::string("A"), 30.0, std::string("Lia")}
        });
        require(frame.rows()==3 && frame.cols()==3, "dimensions");
        require(frame.filter("score", [](const Value& v){return as_number(v)>10;}).rows()==2, "filter");
        near(as_number(frame.sort_by("score",false).at(0,"score")),30,"descending sort");
        near(mean(frame.column("score")),20,"mean"); near(median(frame.column("score")),20,"median");
        near(standard_deviation(frame.column("score")),std::sqrt(200.0/3.0),"population standard deviation");
        near(percentile(frame.column("score"),25),15,"percentile");
        near(correlation(frame.column("score"),Series("y",{2.0,4.0,6.0})),1,"correlation");
        require(group_count(frame,"team").at("A")==2,"group count");
        near(group_sum(frame,"team","score").at("A"),40,"group sum");
        near(group_min(frame,"team","score").at("A"),10,"group minimum");
        near(group_max(frame,"team","score").at("A"),30,"group maximum");
        require(count(frame.column("name"))==3,"non-missing count");
        near(sum(frame.column("score")),60,"sum"); near(minimum(frame.column("score")),10,"minimum");
        near(maximum(frame.column("score")),30,"maximum");
        require(trim_strings(frame.column("name")).at(0)==Value(std::string("Mina")),"trim transform");
        require(uppercase(frame.column("name")).at(0)==Value(std::string(" MINA ")),"uppercase transform");
        require(normalize(frame.column("score")).at(0)==Value(0.0),"normalize");
        require(to_numeric(Series("text",{std::string("12"),std::string("oops")})).at(0)==Value(12.0),"numeric conversion");
        require(std::holds_alternative<std::monostate>(to_numeric(Series("text",{std::string("oops")})).at(0)),"invalid numeric conversion becomes missing");
        require(standardize(Series("constant",{4.0,4.0})).at(0)==Value(0.0),"constant standardization");
        require(Series("letters",{1,2,3}).slice(1,3).size()==2,"series slice");
        require(frame.with_column("double",[](const auto& row){return as_number(row[1])*2;}).cols()==4,"derived column");
        auto long_frame=melt(frame,{"team"},{"score","name"},"field","entry");
        require(long_frame.rows()==6 && long_frame.cols()==3,"wide to long reshape");
        write_csv(frame,"test_roundtrip.csv"); auto csv=read_csv("test_roundtrip.csv");
        require(csv.rows()==3 && csv.at(1,"name")==Value(std::string("JOHN")),"CSV round trip"); std::remove("test_roundtrip.csv");
        write_json(frame,"test_roundtrip.json"); auto json=read_json("test_roundtrip.json");
        require(json.rows()==3 && json.at(2,"team")==Value(std::string("A")),"JSON round trip"); std::remove("test_roundtrip.json");
        bool threw=false;try{frame.column("missing");}catch(const std::out_of_range&){threw=true;}require(threw,"invalid column error");
        threw=false;try{frame.slice(0,9);}catch(const std::out_of_range&){threw=true;}require(threw,"invalid slice error");
        threw=false;try{quantile(frame.column("score"),2.0);}catch(const std::invalid_argument&){threw=true;}require(threw,"invalid quantile error");
        std::cout << "All " << checks << " checks passed.\n";
        return 0;
    } catch(const std::exception& error) {
        std::cerr << "Test failed after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
}
