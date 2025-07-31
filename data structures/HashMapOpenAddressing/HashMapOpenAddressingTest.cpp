#include <iostream>
#include <cassert>
#include <string>
#include "HashMapOpenAddressing.h"
int main() {
    HashMap<std::string, int> map;

    // Test 1: Insert and find
    map.insert("apple", 1);
    map.insert("banana", 2);
    map.insert("cherry", 3);

    assert(map.find("apple").has_value() && map.find("apple").value() == 1);
    assert(map.find("banana").has_value() && map.find("banana").value() == 2);
    assert(map.find("cherry").has_value() && map.find("cherry").value() == 3);
    assert(!map.find("date").has_value());

    // Test 2: Overwrite value
    map.insert("apple", 10);
    assert(map.find("apple").value() == 10);

    // Test 3: Erase
    assert(map.erase("banana"));
    assert(!map.find("banana").has_value());
    assert(!map.erase("banana"));  // Already deleted

    // Test 4: operator[]
    map["date"] = 4;
    assert(map.find("date").value() == 4);
    map["date"]++;
    assert(map["date"] == 5);

    // Test 5: size
    assert(map.size() == 3);  // apple, cherry, date

    // Test 6: rehash (triggered internally)
    for (int i = 0; i < 100; ++i) {
        map.insert("key" + std::to_string(i), i);
    }
    assert(map.find("key50").has_value() && map.find("key50").value() == 50);

    std::cout << "✅ All tests passed!\n";
    return 0;
}