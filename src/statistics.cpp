#include "codemasterspandas/statistics.hpp"

#include <algorithm>

#include <cmath>//this enables you to use math squares aquare root operands

#include <numeric>//

#include <stdexcept>

namespace codemasterspandas {

    namespace {std::vector<double> numbers(const Series& s){std::vector<double> out;for(const auto& v:s.values())if(is_numeric(v))out.push_back(as_number(v));return out;}}
std::size_t count(const Series& s){return static_cast<std::size_t>(std::count_if(s.values().begin(),s.values().end(),[](const Value& v){return !std::holds_alternative<std::monostate>(v);}));}

double sum(const Series& s){auto v=numbers(s);return std::accumulate(v.begin(),v.end(),0.0);}
double minimum(const Series& s){auto v=numbers(s);if(v.empty())throw std::domain_error("minimum requires a numeric value");return *std::min_element(v.begin(),v.end());}
double maximum(const Series& s){auto v=numbers(s);if(v.empty())throw std::domain_error("maximum requires a numeric value");return *std::max_element(v.begin(),v.end());}
double mean(const Series& s){auto v=numbers(s);if(v.empty())throw std::domain_error("mean requires a numeric value");return std::accumulate(v.begin(),v.end(),0.0)/v.size();}
double quantile(const Series& s,double q){if(q<0||q>1)throw std::invalid_argument("quantile must be in [0,1]");auto v=numbers(s);if(v.empty())throw std::domain_error("quantile requires a numeric value");std::sort(v.begin(),v.end());double index=q*(v.size()-1);auto lo=static_cast<std::size_t>(index),hi=static_cast<std::size_t>(std::ceil(index));return v[lo]+(v[hi]-v[lo])*(index-lo);}
double median(const Series& s){return quantile(s,0.5);}
double percentile(const Series& s,double p){if(p<0||p>100)throw std::invalid_argument("percentile must be in [0,100]");return quantile(s,p/100.0);}
double standard_deviation(const Series& s,bool sample){auto v=numbers(s);if(v.empty()||(sample&&v.size()<2))throw std::domain_error("not enough values for standard deviation");double avg=std::accumulate(v.begin(),v.end(),0.0)/v.size();double squares=0;for(double x:v)squares+=(x-avg)*(x-avg);return std::sqrt(squares/(v.size()-(sample?1:0)));}
double correlation(const Series& a,const Series& b){if(a.size()!=b.size())throw std::invalid_argument("series lengths differ");std::vector<std::pair<double,double>> pairs;for(std::size_t i=0;i<a.size();++i)if(is_numeric(a.at(i))&&is_numeric(b.at(i)))pairs.emplace_back(as_number(a.at(i)),as_number(b.at(i)));if(pairs.size()<2)throw std::domain_error("correlation requires two paired numeric values");double ax=0,by=0;for(auto p:pairs){ax+=p.first;by+=p.second;}ax/=pairs.size();by/=pairs.size();double cov=0,vx=0,vy=0;for(auto p:pairs){double x=p.first-ax,y=p.second-by;cov+=x*y;vx+=x*x;vy+=y*y;}if(vx==0||vy==0)throw std::domain_error("correlation is undefined for constant values");return cov/std::sqrt(vx*vy);}

std::map<std::string,double> group_sum(const DataFrame& f,const std::string& g,const std::string& v){std::map<std::string,double> out;for(std::size_t i=0;i<f.rows();++i)if(is_numeric(f.at(i,v)))out[value_to_string(f.at(i,g))]+=as_number(f.at(i,v));return out;}
std::map<std::string,double> group_min(const DataFrame& f,const std::string& g,const std::string& v){std::map<std::string,double> out;for(std::size_t i=0;i<f.rows();++i)if(is_numeric(f.at(i,v))){auto key=value_to_string(f.at(i,g));double n=as_number(f.at(i,v));auto it=out.find(key);if(it==out.end()||n<it->second)out[key]=n;}return out;}
std::map<std::string,double> group_max(const DataFrame& f,const std::string& g,const std::string& v){std::map<std::string,double> out;for(std::size_t i=0;i<f.rows();++i)if(is_numeric(f.at(i,v))){auto key=value_to_string(f.at(i,g));double n=as_number(f.at(i,v));auto it=out.find(key);if(it==out.end()||n>it->second)out[key]=n;}return out;}
std::map<std::string,std::size_t> group_count(const DataFrame& f,const std::string& g){std::map<std::string,std::size_t> out;for(std::size_t i=0;i<f.rows();++i)++out[value_to_string(f.at(i,g))];return out;}
} // namespace codemasterspandas



