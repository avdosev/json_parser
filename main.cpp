#include <iostream>
#include <string>
#include <memory>

#include "json/parsing.h"

using namespace std;

map<string, string> testkeys{
        {"array test", "[ [\"test\"   ,  \"test2\" , true , false ], [ null ] ]"},
        {"dict test","{\"test\" : \"test_value\", \"next_test\": null}"}
};

int main() {
    for (auto item : testkeys) {
        string key_of_test = item.first, json_str = item.second;
        auto i = json_str.begin();
        auto p = parse_json(i);
        cout << key_of_test << endl;
        std::cout << p->toString() << std::endl;
    }
    return 0;
}