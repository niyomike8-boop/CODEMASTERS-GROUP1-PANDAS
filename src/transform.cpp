#include "codemasterspandas/transform.hpp"
#include "codemasterspandas/statistics.hpp"
#include <algorithm>
#include <cctype>

namespace codemasterspandas {
Series normalize(const Series& s){double lo=minimum(s),hi=maximum(s);return s.map([=](const Value& v)->Value{if(!is_numeric(v))return std::monostate{};return hi==lo?0.0:(as_number(v)-lo)/(hi-lo);});}
Series standardize(const Series& s){double avg=mean(s),sd=standard_deviation(s);return s.map([=](const Value& v)->Value{if(!is_numeric(v))return std::monostate{};return sd==0?0.0:(as_number(v)-avg)/sd;});}
Series to_numeric(const Series& s){return s.map([](const Value& v)->Value{if(std::holds_alternative<std::monostate>(v))return v;if(is_numeric(v))return as_number(v);try{return as_number(parse_value(value_to_string(v)));}catch(...){return std::monostate{};}});}
Series to_string_series(const Series& s){return s.map([](const Value& v)->Value{if(std::holds_alternative<std::monostate>(v))return std::monostate{};return value_to_string(v);});}
Series lowercase(const Series& s){return s.map([](const Value& v)->Value{if(!std::holds_alternative<std::string>(v))return v;auto out=std::get<std::string>(v);std::transform(out.begin(),out.end(),out.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});return out;});}
Series uppercase(const Series& s){return s.map([](const Value& v)->Value{if(!std::holds_alternative<std::string>(v))return v;auto out=std::get<std::string>(v);std::transform(out.begin(),out.end(),out.begin(),[](unsigned char c){return static_cast<char>(std::toupper(c));});return out;});}
Series trim_strings(const Series& s){return s.map([](const Value& v)->Value{if(!std::holds_alternative<std::string>(v))return v;auto out=std::get<std::string>(v);auto first=std::find_if_not(out.begin(),out.end(),[](unsigned char c){return std::isspace(c);});auto last=std::find_if_not(out.rbegin(),out.rend(),[](unsigned char c){return std::isspace(c);}).base();return first<last?std::string(first,last):std::string{};});}
} // namespace codemasterspandas
