//
// Created by avdosev on 22.09.2019.
//

#pragma once

#include "objects.h"

unique_ptr<JsonObject> parse_json(string::const_iterator str);
unique_ptr<JsonObject> parse_array(string::const_iterator& str);
unique_ptr<JsonObject> parse_dict(string::const_iterator& str);
unique_ptr<JsonObject> parse_value(string::const_iterator& str);
unique_ptr<JsonObject> parse_boolean(string::const_iterator& str);
unique_ptr<JsonObject> parse_null(string::const_iterator& str);
unique_ptr<JsonObject> parse_number(string::const_iterator& str);
unique_ptr<JsonObject> parse_float(string str);
unique_ptr<JsonObject> parse_integer(string str);
unique_ptr<JsonObject> parse_string(string::const_iterator& str);