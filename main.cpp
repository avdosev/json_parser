#include <iostream>
#include <string>
#include <memory>

using namespace std;

namespace json {

    class JsonObject {
    public:
        enum class value_type {
            array,
            dict,
            floating_point,
            integer,
            string,
            boolean,
            null
        };
        value_type type;
        virtual string toString() = 0;
        virtual ~JsonObject() {}
    };



    unique_ptr<JsonObject> parse_array(string::const_iterator& str);
    unique_ptr<JsonObject> parse_dict(string::const_iterator& str);
    unique_ptr<JsonObject> parse_value(string::const_iterator& str);
    unique_ptr<JsonObject> parse_boolean(string::const_iterator& str);
    unique_ptr<JsonObject> parse_float(string::const_iterator& str);
    unique_ptr<JsonObject> parse_integer(string::const_iterator& str);
    unique_ptr<JsonObject> parse_string(string::const_iterator& str);

    unique_ptr<JsonObject> parse_json(string::const_iterator& str) {
        unique_ptr<JsonObject> res;
        switch(*str) {
            case '{':
                res = move(parse_dict(str));
                break;
            case '[':
                res = move(parse_array(str));
                break;
            default:
                throw runtime_error("i don`t know");
        }
        return move(res);
    }

    unique_ptr<JsonObject> parse_array(string::const_iterator& str) {

        while(*str != ']') {
            parse_value(str);
            if (*str == ',') ++str;
        }

    }

    unique_ptr<JsonObject> parse_dict(string::const_iterator& str) {

    }

    unique_ptr<JsonObject> parse_value(string::const_iterator& str) {
        switch(*str) {
            case '\"':
                parse_string(str);
            case '[':
                parse_array(str);
            case '{':
                parse_dict(str);
            case 't':
            case 'f':
                parse_boolean(str);

        }
    }

    unique_ptr<JsonObject> parse_boolean(string::const_iterator& str) {

    }

    unique_ptr<JsonObject> parse_float(string::const_iterator& str) {

    }

    unique_ptr<JsonObject> parse_integer(string::const_iterator& str) {

    }

    unique_ptr<JsonObject> parse_string(string::const_iterator& str) {

    }

} // end namespace json


int main() {

    string json_str = "{ \"value\": true }";
    std::cout << "Hello, World!" << std::endl;
    return 0;
}