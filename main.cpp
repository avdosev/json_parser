#include <iostream>
#include <string>

#include "json/json.h"

using namespace std;

map<string, string> testkeys{
        {"array test", R"([ ["test"   ,  "test2" , true , false ], [ null ] ])"},
        {"dict test",R"({
"test" : "test_value",
"next_test": null,
"number": 1223,
"arr" : [1,2,3,4, null]
        })"},
        {"numbers test", "[ 1231, 4564, 456464, 4897546, 0.12315 ]"}
};

int main() {
    for (auto item : testkeys) {
        string key_of_test = item.first, json_str = item.second;
        auto p = json::parse(json_str);
        cout << key_of_test << endl;
    }

    auto p = json::parse(testkeys["numbers test"]);
    cout << p.asArray()[4].asFloat() << endl;

    auto p2 = json::parse(testkeys["dict test"]);
    cout << p2.asDict()["number"].asFloat() << endl;
    for (auto item : p2.asDict()["arr"].asArray()) {
        try {
            cout << item.asInteger() << endl;
        } catch (json::DynamicConvertException &exc) {
            cout << "not converted" << endl;
        }
    }

    return 0;
}