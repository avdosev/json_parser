#include <iostream>
#include <string>

#include "json/json.h"

using namespace std;

map<string, string> testkeys{
        {"array test", R"([ ["test"   ,  "test2" , true , false ], [ null ] ])"},
        {"dict test",R"({"test" : "test_value", "next_test": null})"},
        {"numbers test", "[ 1231, 4564, 456464, 4897546, 0.12315 ]"}
};

int main() {
    for (auto item : testkeys) {
        string key_of_test = item.first, json_str = item.second;
        auto p = json::parse(json_str);
        cout << key_of_test << endl;
    }
    return 0;
}