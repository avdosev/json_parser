//
// Created by avdosev on 22.09.2019.
//

#include "objects.h"

using namespace std;

void JsonArray::push(unique_ptr<JsonObject> value) {
    arr.push_back(move(value));
}

string JsonArray::toString() const {
    string res;

    res += "[\n";
    for (size_t i = 0; i < arr.size(); i++) {
        const auto& item = arr[i];
        res += (item ? item->toString() : "") + (i < arr.size()-1 ? "," : "") ;
    }
    res += "\n]";

    return res;
}

value_type JsonArray::type() const {
    return value_type::array;
}

void JsonDict::push(string key, unique_ptr<JsonObject> value) {
    this->value.insert(make_pair(key, move(value)));
}

string JsonDict::toString() const {
    string res;

    res += "{\n";
    auto pre_end_it = value.end();
    --pre_end_it;
    for (auto it = value.begin(); it != value.end(); ++it) {
        const auto& item = *it;

        res += '\"' + item.first + "\":" + item.second->toString() + (it != pre_end_it ? "," : "");
    }
    res += "\n}";

    return res;
}

value_type JsonDict::type() const {
    return value_type::dict;
}

string JsonFloat::toString() const {
    return to_string(value);
}

value_type JsonFloat::type() const {
    return value_type::floating_point;
}

string JsonInteger::toString() const {
    return to_string(value);
}

value_type JsonInteger::type() const {
    return value_type::integer;
}

string JsonBool::toString() const {
    return value ? "true" : "false";
}

value_type JsonBool::type() const {
    return value_type::boolean;
}

string JsonString::get() const {
    return this->value;
}
string JsonString::toString() const {
    return this->get();
}

value_type JsonString::type() const {
    return value_type::string;
}

string JsonNull::toString() const {
    return "null";
}

value_type JsonNull::type() const {
    return value_type::null;
}