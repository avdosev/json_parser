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
    virtual value_type type() const = 0;
    virtual string toString() const = 0;
    virtual ~JsonObject() {}
};

class JsonArray : public JsonObject {
private:
    vector<unique_ptr<JsonObject>> arr;
public:
    void push(unique_ptr<JsonObject> value) {
        arr.push_back(move(value));
    }

    vector<unique_ptr<JsonObject>>& get() {
        return arr;
    }

    string toString() const {
        string res;

        res += "[\n";
        for (size_t i = 0; i < arr.size(); i++) {
            const auto& item = arr[i];
            res += (item ? item->toString() : "") + (i < arr.size()-1 ? "," : "") ;
        }
        res += "\n]";

        return res;
    }

    value_type type() const {
        return value_type::array;
    }
};

class JsonDict : public JsonObject {
public:
    using container_t = map<string, unique_ptr<JsonObject>>;
    container_t value;

    void push(string key, unique_ptr<JsonObject> value) {
        this->value.insert(make_pair(key, move(value)));
    }

    string toString() const {
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

    value_type type() const {
        return value_type::dict;
    }
};

class JsonFloat : public JsonObject {
public:
    using num_t = double;
    num_t value;

    JsonFloat(num_t value) : value(value) {}

    string toString() const {
        return to_string(value);
    }

    value_type type() const {
        return value_type::floating_point;
    }
};

class JsonInteger : public JsonObject {
public:
    using num_t = long long int;
    num_t value;

    JsonInteger(num_t value) : value(value) {}

    string toString() const {
        return to_string(value);
    }

    value_type type() const {
        return value_type::integer;
    }
};

class JsonBool : public JsonObject {
public:
    bool value;
    JsonBool(bool value) : value(value) {

    }

    string toString() const {
        return value ? "true" : "false";
    }

    value_type type() const {
        return value_type::boolean;
    }
};

class JsonString : public JsonObject {
public:
    string value;
    JsonString(string str) : value(move(str)) {}
    string get() const {
        return this->value;
    }
    string toString() const {
        return this->get();
    }

    value_type type() const {
        return value_type::string;
    }
};

class JsonNull : public JsonObject {
public:
    nullptr_t value = nullptr;

    string toString() const {
        return "null";
    }

    value_type type() const {
        return value_type::null;
    }
};