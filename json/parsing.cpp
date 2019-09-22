//
// Created by avdosev on 22.09.2019.
//

#include "parsing.h"

unique_ptr<JsonObject> parse_json(string::const_iterator str) {
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
    unique_ptr<JsonArray> arr(new JsonArray);
    ++str;
    while(*str != ']') {
        arr->push(parse_value(str));
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
    }
    ++str;
    return unique_ptr<JsonObject>(move(aarr));
}

unique_ptr<JsonObject> parse_value(string::const_iterator& str) {
    unique_ptr<JsonObject> res;
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

    }
    return res;
}

unique_ptr<JsonObject> parse_boolean(string::const_iterator& str) {
    return nullptr;
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
    auto end_iterator = str;
    ++str;
    return new JsonString(string(start_iterator, end_iterator));
}