#include <iostream>
#include <string>

#include "json/parsing.h"

using namespace std;

map<string, string> testkeys{
        {"array test", "[ [\"test\"   ,  \"test2\" , true , false ], [ null ] ]"},
        {"dict test","{\"test\" : \"test_value\", \"next_test\": null}"},
        {"numbers test", "[ 1231, 4564, 456464, 4897546, 0.12315 ]"}
};

int main() {
    for (auto item : testkeys) {
        string key_of_test = item.first, json_str = item.second;
        auto i = json_str.begin();
        auto p = parse_json(i);
        cout << key_of_test << endl;
        cout << p->toString() << endl;
    }
    return 0;
}