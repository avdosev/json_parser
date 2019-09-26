//
// Created by avdosev on 25.09.2019.
//

#include "json.h"

#include "parsing.h"

json::array_t json::asArray() {
    return json::array_t();
}

json::dict_t json::asDict() {
    return json::dict_t();
}

json::float_t json::asFloat() {
    auto vt = value->type();
    float_t res;
    switch (vt) {
        case value_type::integer: {
            auto ji = dynamic_cast<JsonInteger&>(*value);
            res = ji.value;
            break;
        } case value_type::floating_point: {
            auto jf = dynamic_cast<JsonFloat&>(*value);
            res = jf.value;
            break;
        } case value_type::boolean: {
            auto jb = dynamic_cast<JsonBool&>(*value);
            res = jb.value;
            break;
        } default:
            throw DynamicConvertException("can`t convert to integer");
    }
    return res;
}

json::integer_t json::asInteger() {
    auto vt = value->type();
    integer_t res;
    switch (vt) {
        case value_type::integer: {
            auto ji = dynamic_cast<JsonInteger&>(*value);
            res = ji.value;
            break;
        } case value_type::floating_point: {
            auto jf = dynamic_cast<JsonFloat&>(*value);
            res = jf.value;
            break;
        } case value_type::boolean: {
            auto jb = dynamic_cast<JsonBool&>(*value);
            res = jb.value;
            break;
        } default:
            throw DynamicConvertException("can`t convert to integer");
    }
    return res;
}

nullptr_t json::asNull() {
    auto vt = value->type();

    if (vt != value_type::null)
        throw DynamicConvertException("can`t convert to integer");

    return nullptr;
}

json json::parse(std::string str) {
    return json(parse_json(str.begin()));
}

json::DynamicConvertException::DynamicConvertException(const std::string &arg) : runtime_error(arg) {}
