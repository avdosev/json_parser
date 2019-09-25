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
    json(std::unique_ptr<JsonObject> vl);
    json() {}
public:
    using dict_t = std::map<std::string, std::shared_ptr<JsonObject>>;
    using array_t = std::vector<std::shared_ptr<JsonObject>>;
    static json parse(std::string);
    std::shared_ptr<JsonObject> value;
};
