#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main() {
    BinarySearchTree<int> bst;

    cout << "Initial size: " << bst.size() << "\n\n";

    // Insertion test
    cout << "Inserting: 50, 30, 70, 20, 40, 60, 80\n";
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int x : values) {
        bst.insert(x);
    }

    cout << "Size after insertions: " << bst.size() << "\n";

    cout << "Inorder (should be sorted): ";
    bst.printInorder();

    cout << "Preorder: ";
    bst.printPreorder();

    cout << "Postorder: ";
    bst.printPostorder();

    // Remove leaf
    cout << "\nRemoving leaf node 20...\n";
    bst.remove(20);
    bst.printInorder();
    cout << "Size: " << bst.size() << "\n";

    // Remove node with one child
    cout << "\nRemoving node with one child 30...\n";
    bst.remove(30);
    bst.printInorder();
    cout << "Size: " << bst.size() << "\n";

    // Remove node with two children
    cout << "\nRemoving node with two children 50...\n";
    bst.remove(50);
    bst.printInorder();
    cout << "Size: " << bst.size() << "\n";

    // Remove non-existent value
    cout << "\nTrying to remove non-existent value 100...\n";
    bst.remove(100);
    bst.printInorder();
    cout << "Size: " << bst.size() << "\n";

    // Insert duplicate
    cout << "\nTrying to insert duplicate 60...\n";
    bst.insert(60);
    bst.printInorder();
    cout << "Size (should not increase): " << bst.size() << "\n";

    // Cleanup message
    cout << "\nProgram completed.\n";
}
