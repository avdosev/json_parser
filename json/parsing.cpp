//
// Created by avdosev on 22.09.2019.
//

#include "parsing.h"

void skipSpaces(string::const_iterator& it);

unique_ptr<JsonObject> parse_json(string::const_iterator str) {
    unique_ptr<JsonObject> res;
    skipSpaces(str);
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
    unique_ptr<JsonArray> arr(new JsonArray);
    ++str;
    while(*str != ']') {
        arr->push(parse_value(str));
        skipSpaces(str);
        if (*str == ',') ++str;
    }
    ++str;
    return unique_ptr<JsonObject>(move(arr));
}

unique_ptr<JsonObject> parse_dict(string::const_iterator& str) {
    unique_ptr<JsonDict> dict(new JsonDict);
    ++str;
    while(*str != '}') {
        skipSpaces(str);
        auto key = parse_string(str)->toString();
        key = move(string(key.begin()+1, key.end()-1));
        skipSpaces(str);
        if (*str != ':')
            throw runtime_error("dict parse error");
        else
            ++str;
        skipSpaces(str);
        dict->push(key, move(parse_value(str)));
        skipSpaces(str);
        if (*str == ',') ++str;
        skipSpaces(str);
    }
    ++str;
    return unique_ptr<JsonObject>(move(dict));
}

unique_ptr<JsonObject> parse_value(string::const_iterator& str) {
    unique_ptr<JsonObject> res;
    skipSpaces(str);
    switch(*str) {
        case '\"':
            res = move(parse_string(str));
            break;
        case '[':
            res = move(parse_array(str));
            break;
        case '{':
            res = move(parse_dict(str));
            break;
        case 't':
        case 'f':
            res = move(parse_boolean(str));
            break;
        case 'n':
            res = move(parse_null(str));
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-': // типо минусик
            res = move(parse_number(str));
            break;
        default:
            throw runtime_error("value parse error");
    }
    return res;
}

unique_ptr<JsonObject> parse_boolean(string::const_iterator& str) {
    bool isTrue = *str == 't';
    string test_str = isTrue ? "true" : "false";

    auto it = test_str.begin();
    for (; it < test_str.end(); ++it) {
        if (*str == *it)
            ++str;
        else
            break;
    }

    if (it != test_str.end() || isalpha(*str )) {
        throw runtime_error("boolean parse error");
    }

    return unique_ptr<JsonObject>(new JsonBool(isTrue));
}

unique_ptr<JsonObject> parse_null(string::const_iterator& str) {
    // тут как бы повтор кода, но как бы и не повтор так шо нормально
    string test_str = "null";

    auto it = test_str.begin();
    for (; it < test_str.end(); ++it) {
        if (*str == *it)
            ++str;
        else
            break;
    }

    if (it != test_str.end() || isalpha(*str)) {
        throw runtime_error("null parse error");
    }

    return unique_ptr<JsonObject>(new JsonNull);
}

unique_ptr<JsonObject> parse_number(string::const_iterator& it) {

    bool isFloat = false;
    auto start_it = it;
    char c = *it; // stopgap for already consumed character
    // integral part
    while (c >= '0' && c <= '9')
        c = *it++;

    // fractional part
    if (c == '.') {
        isFloat = true;
        c = *it++;
        while (c >= '0' && c <= '9')
            c = *it++;
    }

    // exponential part
    if (c == 'e' || c == 'E') {
        isFloat = true;
        c = *it++;
        if (c == '+' || c == '-')
            c = *it++;
        while (c >= '0' && c <= '9')
            c = *it++;
    }

    string number_str(start_it, it);

    unique_ptr<JsonObject> res;
    if (isFloat)
        res = move(parse_float(number_str));
    else
        res = move(parse_integer(number_str));

    return res;
}

unique_ptr<JsonObject> parse_float(string str) {
    double num = stod(str);
    return unique_ptr<JsonObject>(new JsonFloat(num));
}

unique_ptr<JsonObject> parse_integer(string str) {
    long long int num = stoll(str);
    return unique_ptr<JsonObject>(new JsonInteger(num));
}

unique_ptr<JsonObject> parse_string(string::const_iterator& str) {
    auto start_iterator = str;
    do {
        ++str;
    } while(*str != '\"');
    auto end_iterator = ++str;
    return unique_ptr<JsonObject>(new JsonString(string(start_iterator, end_iterator)));
}

void skipSpaces(string::const_iterator& it) {
    while (true) {
        auto c = *it;
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            ++it;
        else
            break;
    }
}