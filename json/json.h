//
// Created by avdosev on 25.09.2019.
//

#pragma once

#include <string>
#include <map>
#include <vector>
#include "objects.h"

class json {
protected:
    std::shared_ptr<JsonObject> value;
    json(std::shared_ptr<JsonObject> vl);
    json() = default;
public:
    using dict_t = std::map<std::string, json>;
    using array_t = std::vector<json>;
    using integer_t = long long;
    using float_t = double;
    using null_t = nullptr_t;

    class DynamicConvertException : public std::runtime_error {
    public:
        DynamicConvertException(const std::string &arg);
    };
    array_t asArray();
    dict_t asDict();
    float_t asFloat();
    integer_t asInteger();
    nullptr_t asNull();


    static json parse(std::string);
};
