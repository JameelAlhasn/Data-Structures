#include <iostream>
#include "LinkedList.h"
// ==============================
// Test Functions
// ==============================

void testIntList() {
    LinkedList<int> list;

    std::cout << "=== Integer List Tests ===\n";

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);         // [5, 10, 20]
    list.insert(1, 7);          // [5, 7, 10, 20]

    std::cout << "After insertions: ";
    list.print();

    std::cout << "Size: " << list.size() << '\n';           // Expect 4
    std::cout << "Element at index 2: " << list[2] << '\n'; // Expect 10

    list.remove(1);             // [5, 10, 20]
    std::cout << "After removing index 1: ";
    list.print();

    list.pop(10);               // [5, 20]
    std::cout << "After popping 10: ";
    list.print();

    list.pop_front();           // [20]
    list.pop_back();            // []
    std::cout << "After popping front and back: ";
    list.print();

    std::cout << "Empty? " << std::boolalpha << list.empty() << "\n\n";
}

void testCopy() {
    std::cout << "=== Copy Constructor & Assignment Tests ===\n";

    LinkedList<std::string> names;
    names.push_back("Alice");
    names.push_back("Bob");

    LinkedList<std::string> copy1 = names;  // Copy constructor
    LinkedList<std::string> copy2;
    copy2 = names;                          // Copy assignment

    std::cout << "Original list: ";
    names.print();

    std::cout << "Copy1: ";
    copy1.print();

    std::cout << "Copy2: ";
    copy2.print();

    std::cout << "Modifying Copy1[0] to Zara...\n";
    copy1[0] = "Zara";

    std::cout << "Copy1: ";
    copy1.print();

    std::cout << "Original should remain unchanged: ";
    names.print();

    std::cout << '\n';
}

void testOutOfRange() {
    std::cout << "=== Out-of-Range Test ===\n";
    LinkedList<char> letters;
    letters.push_back('A');
    try {
        std::cout << letters[5] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }

    try {
        letters.insert(3, 'Z');
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception on insert: " << e.what() << '\n';
    }

    try {
        letters.remove(-1);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception on remove: " << e.what() << '\n';
    }
    std::cout << '\n';
}

// ==============================
// Main Function
// ==============================

int main() {
    testIntList();
    testCopy();
    testOutOfRange();
    return 0;
}