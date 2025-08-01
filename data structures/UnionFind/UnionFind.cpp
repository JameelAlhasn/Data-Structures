#include <iostream>
#include <string>
#include <cassert>
#include "UnionFind.h"
using namespace std;

int main() {
    UnionFind<string> uf;

    // === Test make_set ===
    vector<string> names = {"a", "b", "c", "d", "e"};
    for (auto &name : names) uf.make_set(name);
    for (auto &name : names) assert(uf.find(name) == name);

    // === Test union_sets and same_set ===
    uf.union_sets("a", "b");
    assert(uf.same_set("a", "b") == true);
    assert(uf.find("a") == uf.find("b"));

    uf.union_sets("c", "d");
    assert(uf.same_set("c", "d") == true);
    assert(uf.same_set("a", "c") == false);

    uf.union_sets("b", "c"); // Now a-b-c-d are connected
    assert(uf.same_set("a", "d") == true);

    // === Test redundant union ===
    uf.union_sets("a", "d"); // already connected, should do nothing
    assert(uf.same_set("a", "d") == true);

    // === Test isolated node ===
    assert(uf.same_set("e", "a") == false);

    // === Connect all ===
    uf.union_sets("e", "a");
    assert(uf.same_set("e", "d") == true);
    assert(uf.same_set("e", "b") == true);

    // === Final Group Check ===
    string leader = uf.find("a");
    for (auto &name : names)
        assert(uf.find(name) == leader);

    cout << "✅ All Union-Find tests passed!\n";
    return 0;
}
