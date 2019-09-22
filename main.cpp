#include <iostream>
#include <string>
#include <memory>

#include "json.h"

using namespace std;


int main() {
    string json_str = "[[],[]]";
    string::const_iterator i = json_str.begin();
    auto p = parse_json(i);
    std::cout << p->toString() << std::endl;
    return 0;
}