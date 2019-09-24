#include <iostream>
#include <string>
#include <memory>

#include "json/parsing.h"

using namespace std;


int main() {
    string json_str = "[ [\"test\"   ,  \"test2\" , true , false, null ], [  ] ]";
    string::const_iterator i = json_str.begin();
    auto p = parse_json(i);
    std::cout << p->toString() << std::endl;
    return 0;
}