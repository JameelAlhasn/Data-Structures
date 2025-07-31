#include <iostream>
#include <cassert>
#include "HashTableDoubleHashing.h"

int main() {
    HashMap<std::string, int> map;
    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);

    std::cout << map.find("one").value_or(-1) << "\n";
    std::cout << map.find("two").value_or(-1) << "\n";
    std::cout << map.find("missing").value_or(-1) << "\n";

    map.erase("two");
    std::cout << map.find("two").value_or(-1) << "\n";

    map["four"] = 4;
    std::cout << map["four"] << "\n";
    map["four"] += 1;
    std::cout << map["four"] << "\n";

    std::cout << "Size: " << map.size() << "\n";
}
