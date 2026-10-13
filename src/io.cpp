#include "codemasterspandas/io.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace codemasterspandas {
namespace {
std::vector<std::string> parse_csv_line(const std::string& line) {
    std::vector<std::string> fields; std::string field; bool quoted=false;
    for(std::size_t i=0;i<line.size();++i){char c=line[i]; if(quoted){if(c=='"'&&i+1<line.size()&&line[i+1]=='"'){field+='"';++i;}else if(c=='"')quoted=false;else field+=c;}
        else if(c=='"')quoted=true; else if(c==','){fields.push_back(field);field.clear();}else field+=c;}
    if (quoted) throw std::runtime_error("unterminated quoted CSV field");
    fields.push_back(field);
    return fields;
}
std::string csv_escape(const std::string& value){if(value.find_first_of(",\"\r\n")==std::string::npos)return value;std::string out="\"";for(char c:value){if(c=='"')out+='"';out+=c;}return out+'"';}
std::string read_all(const std::string& path){std::ifstream in(path,std::ios::binary);if(!in)throw std::runtime_error("cannot open input file: "+path);std::ostringstream out;out<<in.rdbuf();return out.str();}
std::string json_escape(const std::string& s){std::string o;for(char c:s){if(c=='"'||c=='\\')o+='\\';if(c=='\n'){o+="\\n";continue;}if(c=='\r'){o+="\\r";continue;}o+=c;}return o;}
class JsonRows {
public:
    explicit JsonRows(std::string text):s(std::move(text)){}
    DataFrame parse(){skip();expect('[');skip();if(take(']'))return {};std::vector<std::string> names;std::vector<std::vector<Value>> rows;
        do{skip();expect('{');skip();std::vector<std::pair<std::string,Value>> pairs;if(!take('}')){do{skip();auto key=string();skip();expect(':');skip();pairs.emplace_back(key,value());skip();}while(take(','));expect('}');}
            if(names.empty())for(const auto& p:pairs)names.push_back(p.first);
            std::vector<Value> row(names.size());for(const auto& p:pairs){auto it=std::find(names.begin(),names.end(),p.first);if(it==names.end())throw std::runtime_error("JSON objects must have the same keys");row[static_cast<std::size_t>(it-names.begin())]=p.second;} rows.push_back(std::move(row));skip();}while(take(','));expect(']');skip();if(pos!=s.size())fail("trailing JSON content");return DataFrame(names,rows);}
private:
    std::string s;std::size_t pos=0;
    [[noreturn]]void fail(const std::string& why){throw std::runtime_error("invalid JSON near byte "+std::to_string(pos)+": "+why);}
    void skip(){while(pos<s.size()&&std::isspace(static_cast<unsigned char>(s[pos])))++pos;}
    bool take(char c){skip();if(pos<s.size()&&s[pos]==c){++pos;return true;}return false;}
    void expect(char c){if(!take(c))fail(std::string("expected '")+c+"'");}
    std::string string(){expect('"');std::string o;while(pos<s.size()){char c=s[pos++];if(c=='"')return o;if(c=='\\'){if(pos>=s.size())fail("bad escape");char e=s[pos++];switch(e){case 'n':o+='\n';break;case 'r':o+='\r';break;case 't':o+='\t';break;case '"':case '\\':case '/':o+=e;break;default:fail("unsupported escape");}}else o+=c;}fail("unterminated string");}
    Value value(){if(pos>=s.size())fail("expected value");if(s[pos]=='"')return string();auto start=pos;while(pos<s.size()&&s[pos]!=','&&s[pos]!='}'&&!std::isspace(static_cast<unsigned char>(s[pos])))++pos;auto token=s.substr(start,pos-start);if(token=="null")return std::monostate{};if(token=="true")return true;if(token=="false")return false;return parse_value(token);}
};
}
DataFrame read_csv(const std::string& path){std::ifstream in(path);if(!in)throw std::runtime_error("cannot open input file: "+path);std::string line;if(!std::getline(in,line))return {};if(!line.empty()&&line.back()=='\r')line.pop_back();auto names=parse_csv_line(line);std::vector<std::vector<Value>> rows;
    while(std::getline(in,line)){if(!line.empty()&&line.back()=='\r')line.pop_back();auto fields=parse_csv_line(line);if(fields.size()!=names.size())throw std::runtime_error("CSV row has wrong number of fields");std::vector<Value> row;for(const auto& field:fields)row.push_back(parse_value(field));rows.push_back(std::move(row));}return DataFrame(names,rows);}
void write_csv(const DataFrame& frame,const std::string& path){std::ofstream out(path);if(!out)throw std::runtime_error("cannot open output file: "+path);for(std::size_t c=0;c<frame.cols();++c){if(c)out<<',';out<<csv_escape(frame.columns()[c]);}out<<'\n';for(std::size_t r=0;r<frame.rows();++r){for(std::size_t c=0;c<frame.cols();++c){if(c)out<<',';out<<csv_escape(value_to_string(frame.column(frame.columns()[c]).at(r)));}out<<'\n';}}
DataFrame read_json(const std::string& path){return JsonRows(read_all(path)).parse();}
void write_json(const DataFrame& frame,const std::string& path){std::ofstream out(path);if(!out)throw std::runtime_error("cannot open output file: "+path);out<<"[\n";for(std::size_t r=0;r<frame.rows();++r){out<<"  {";for(std::size_t c=0;c<frame.cols();++c){if(c)out<<", ";const auto& name=frame.columns()[c];const auto& v=frame.column(name).at(r);out<<'"'<<json_escape(name)<<"\": ";if(std::holds_alternative<std::monostate>(v))out<<"null";else if(std::holds_alternative<std::string>(v))out<<'"'<<json_escape(std::get<std::string>(v))<<'"';else out<<value_to_string(v);}out<<'}'<<(r+1==frame.rows()?"\n":",\n");}out<<"]\n";}
} // namespace codemasterspandas
