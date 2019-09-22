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
        for (size_t i = 0; i < arr.size(); i++) {
            const auto& item = arr[i];
            res += (item ? item->toString() : "") + (i < arr.size()-1 ? "," : "") ;
        }
        res += "\n]";

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

    string toString() const {
        string res;

        res += "{\n";
        auto pre_end_it = d.end();
        --pre_end_it;
        for (auto it = d.begin(); it != d.end(); ++it) {
            const auto& item = *it;

            res += item.first + ":" + item.second->toString() + (it != pre_end_it ? "," : "");
        }
        res += "\n}";

        return res;
    }
};

class JsonInt : public JsonObject {

};

class JsonFloat : public JsonObject {

};

class JsonBool : public JsonObject {

};

class JsonString : public JsonObject {
private:
    string str;
public:
    JsonString(string str) : JsonObject(value_type::string), str(move(str)) {}
    string get() const {
        return this->str;
    }
    string toString() const {
        return this->get();
    }
};

class JsonNull : public JsonObject {

};