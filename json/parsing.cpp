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
    unique_ptr<JsonDict> aarr(new JsonDict);
    ++str;
    while(*str != '}') {
        auto key = parse_string(str)->toString();
        key = move(string(key.begin()+1, key.end()-1));
        aarr->push(key, move(parse_value(str)));
        skipSpaces(str);
    }
    ++str;
    return unique_ptr<JsonObject>(move(aarr));
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

unique_ptr<JsonObject> parse_float(string::const_iterator& str) {
    return nullptr;
}

unique_ptr<JsonObject> parse_integer(string::const_iterator& str) {
    return nullptr;
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