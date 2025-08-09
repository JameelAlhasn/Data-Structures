#include "AVL.h"
#include <cassert>
#include <iostream>

int main() {
    AVLTree<int> tree;

    // Insert some values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30); // causes RR rotation
    tree.insert(25); // causes RL rotation
    tree.insert(5);  // normal insert
    tree.insert(4);  // causes LL rotation

    // Check presence
    assert(tree.find(10) == true);
    assert(tree.find(20) == true);
    assert(tree.find(30) == true);
    assert(tree.find(25) == true);
    assert(tree.find(5) == true);
    assert(tree.find(4) == true);

    // Check absence
    assert(tree.find(100) == false);
    assert(tree.find(-1) == false);

    // Erase some elements
    tree.erase(30);
    tree.erase(5);

    // Check they are gone
    assert(tree.find(30) == false);
    assert(tree.find(5) == false);

    // Remaining elements should still be there
    assert(tree.find(10) == true);
    assert(tree.find(20) == true);
    assert(tree.find(25) == true);
    assert(tree.find(4) == true);

    std::cout << "All AVL tests passed!\n";
    return 0;
}
