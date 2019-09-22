//
// Created by avdosev on 22.09.2019.
//

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>


using namespace std; // TODO пока так, но потом уберу

enum class value_type {
    array,
    dict,
    floating_point,
    integer,
    string,
    boolean,
    null
};

class JsonObject {
public:
    JsonObject(value_type type) : type(type) {}
    value_type type;
    virtual string toString() const = 0;
    virtual ~JsonObject() {}
};

class JsonArray : public JsonObject {
private:
    vector<unique_ptr<JsonObject>> arr;
public:
    JsonArray() : JsonObject(value_type::array) {

    }

    void push(unique_ptr<JsonObject> value) {
        arr.push_back(move(value));
    }

    vector<unique_ptr<JsonObject>>& get() {
        return arr;
    }

    string toString() const {
        string res;

        res += "[\n";
        for (const auto& item : arr) {
            res += (item ? item->toString() : "") + "," ;
        }
        res += "]\n";

        return res;
    }
};

class JsonDict : public JsonObject {
private:
    using container_t = map<string, unique_ptr<JsonObject>>;
    container_t d;
public:
    JsonDict() : JsonObject(value_type::dict) {

    }

    void push(string key, unique_ptr<JsonObject> value) {
        d.insert(make_pair(key, move(value)));
    }

    container_t& get() {
        return d;
    }
};

class JsonInt : public JsonObject {

};

class JsonFloat : public JsonObject {

};

class JsonBool : public JsonObject {

};

class JsonString : public JsonObject {

};

class JsonNull : public JsonObject {

};

unique_ptr<JsonObject> parse_json(string::const_iterator str);
unique_ptr<JsonObject> parse_array(string::const_iterator& str);
unique_ptr<JsonObject> parse_dict(string::const_iterator& str);
unique_ptr<JsonObject> parse_value(string::const_iterator& str);
unique_ptr<JsonObject> parse_boolean(string::const_iterator& str);
unique_ptr<JsonObject> parse_float(string::const_iterator& str);
unique_ptr<JsonObject> parse_integer(string::const_iterator& str);
unique_ptr<JsonObject> parse_string(string::const_iterator& str);