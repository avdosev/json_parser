//
// Created by avdosev on 22.09.2019.
//

#pragma once

#include "objects.h"

std::unique_ptr<JsonObject> parse_json(std::string::const_iterator str);
std::unique_ptr<JsonObject> parse_array(std::string::const_iterator& str);
std::unique_ptr<JsonObject> parse_dict(std::string::const_iterator& str);
std::unique_ptr<JsonObject> parse_value(std::string::const_iterator& str);
std::unique_ptr<JsonObject> parse_boolean(std::string::const_iterator& str);
std::unique_ptr<JsonObject> parse_null(std::string::const_iterator& str);
std::unique_ptr<JsonObject> parse_number(std::string::const_iterator& str);
std::unique_ptr<JsonObject> parse_float(std::string str);
std::unique_ptr<JsonObject> parse_integer(std::string str);
std::unique_ptr<JsonObject> parse_string(std::string::const_iterator& str);