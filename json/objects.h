//
// Created by avdosev on 22.09.2019.
//

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>




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
    virtual std::string toString() const = 0;
    virtual ~JsonObject() {}
};

class JsonArray : public JsonObject {
private:
    using container_t = std::vector<std::shared_ptr<JsonObject>>;
    container_t arr;
public:
    void push(std::unique_ptr<JsonObject> value);

    container_t& get() {
        return arr;
    }

    std::string toString() const;
    value_type type() const;
};

class JsonDict : public JsonObject {
public:
    using container_t = std::map<std::string, std::shared_ptr<JsonObject>>;
    container_t value;

    void push(std::string key, std::unique_ptr<JsonObject> value) ;

    std::string toString() const;

    value_type type() const;
};

class JsonFloat : public JsonObject {
public:
    using num_t = double;
    num_t value;

    JsonFloat(num_t value) : value(value) {}

    std::string toString() const;

    value_type type() const;
};

class JsonInteger : public JsonObject {
public:
    using num_t = long long int;
    num_t value;

    JsonInteger(num_t value) : value(value) {}

    std::string toString() const;

    value_type type() const;
};

class JsonBool : public JsonObject {
public:
    bool value;
    JsonBool(bool value) : value(value) {}

    std::string toString() const;

    value_type type() const;
};

class JsonString : public JsonObject {
public:
    std::string value;
    JsonString(std::string str) : value(move(str)) {}

    std::string get() const;
    std::string toString() const;
    value_type type() const;
};

class JsonNull : public JsonObject {
public:
    std::string toString() const;
    value_type type() const;
};