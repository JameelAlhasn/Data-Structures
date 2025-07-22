#include <iostream>
#include <cassert>
#include "HashMapSeparateChaining.h"
using namespace std;
void basic_insert_and_access() {
    HashMap<int, string> map;
    map[1] = "one";
    map[2] = "two";
    map[10] = "ten";

    assert(map[1] == "one");
    assert(map[2] == "two");
    assert(map[10] == "ten");

    cout << "✅ basic_insert_and_access passed.\n";
}

void test_at_and_contains() {
    HashMap<int, int> map;
    map[5] = 100;
    assert(map.contains(5));
    assert(map.at(5) == 100);

    try {
        map.at(999);  // should throw
        assert(false);
    } catch (const std::out_of_range&) {
        cout << "✅ test_at_and_contains passed.\n";
    }
}

void test_erase() {
    HashMap<string, int> map;
    map["a"] = 1;
    map["b"] = 2;
    assert(map.erase("a"));
    assert(!map.contains("a"));
    assert(map.size() == 1);
    assert(!map.erase("not_found"));
    cout << "✅ test_erase passed.\n";
}

void test_copy_constructor_and_assignment() {
    HashMap<int, string> a;
    a[3] = "three";
    a[4] = "four";

    HashMap<int, string> b = a;
    assert(b[3] == "three");

    HashMap<int, string> c;
    c = a;
    assert(c[4] == "four");
    cout << "✅ test_copy_constructor_and_assignment passed.\n";
}

void test_empty_and_clear() {
    HashMap<int, int> m;
    assert(m.empty());
    m[1] = 10;
    assert(!m.empty());
    m.clear();
    assert(m.empty());
    assert(m.size() == 0);
    cout << "✅ test_empty_and_clear passed.\n";
}

void test_iterator() {
    HashMap<int, int> m;
    for (int i = 0; i < 10; ++i)
        m[i] = i * i;

    int count = 0;
    for (auto& [k, v] : m) {
        assert(v == k * k);
        ++count;
    }
    assert(count == 10);
    cout << "✅ test_iterator passed.\n";
}

int main() {
    basic_insert_and_access();
    test_at_and_contains();
    test_erase();
    test_copy_constructor_and_assignment();
    test_empty_and_clear();
    test_iterator();
    cout << "\n🎉 All tests passed successfully!\n";
    return 0;
}
