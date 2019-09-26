//
// Created by avdosev on 25.09.2019.
//

#include "json.h"

#include "parsing.h"

json::json(std::shared_ptr<JsonObject> vl) : value(vl) {

}

json::array_t json::asArray() {
    auto vt = value->type();

    if (vt != value_type::dict && vt != value_type::array)
        throw DynamicConvertException("can`t convert to array");

    array_t arr;
    if(vt == value_type::array) {
        auto ja = dynamic_cast<JsonArray&>(*value);
        auto it_end = ja.get().end(), it_begin = ja.get().begin();
        arr.reserve(ja.get().size());
        for (auto it = it_begin; it < it_end; it++) {
            arr.push_back(*it);
        }
    } else {
        auto jd = dynamic_cast<JsonDict&>(*value);
        auto it_end = jd.value.end(), it_begin = jd.value.begin();
        arr.reserve(jd.value.size());
        for (auto it = it_begin; it != it_end; it++) {
            arr.push_back(it->second);
        }
    }

    return arr;
}

json::dict_t json::asDict() {
    auto vt = value->type();

    if (vt != value_type::dict)
        throw DynamicConvertException("can`t convert to dict");


    auto jd = dynamic_cast<JsonDict&>(*value);
    auto it_end = jd.value.end(), it_begin = jd.value.begin();
    dict_t dict;

    for (const auto& pa : jd.value) {
        dict.insert(std::make_pair(pa.first, json(pa.second)));
    }

    return dict;
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
