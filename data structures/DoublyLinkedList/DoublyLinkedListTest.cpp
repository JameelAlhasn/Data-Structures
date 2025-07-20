#include "DoublyLinkedList.h"

void test_basic_operations() {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_front(5);
    list.insert(1, 7); // [5, 7, 10]

    std::cout << "Forward: ";
    list.print_forward(); // 5 7 10

    std::cout << "Backward: ";
    list.print_backward(); // 10 7 5

    std::cout << "Front: " << list.front() << "\n";   // 5
    std::cout << "Back: " << list.back() << "\n";     // 10
    std::cout << "Size: " << list.size() << "\n";     // 3
}

void test_remove_pop_find() {
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 5; i++) list.push_back(i); // [1, 2, 3, 4, 5]
    
    std::cout << "Original: ";
    list.print_forward(); // 1 2 3 4 5

    list.remove(2); // remove 3 → [1, 2, 4, 5]
    std::cout << "After remove(2): ";
    list.print_forward();

    list.pop_front(); // remove 1 → [2, 4, 5]
    list.pop_back();  // remove 5 → [2, 4]

    std::cout << "After pops: ";
    list.print_forward();

    std::cout << "Find 4: " << list.find(4) << "\n";       // 1
    std::cout << "Contains 7? " << list.contains(7) << "\n"; // 0
}

void test_copy_behavior() {
    DoublyLinkedList<int> original;
    original.push_back(100);
    original.push_back(200);

    DoublyLinkedList<int> copy = original;
    copy.push_back(300);

    std::cout << "Original list: ";
    original.print_forward(); // 100 200

    std::cout << "Copied list: ";
    copy.print_forward();     // 100 200 300
}

void test_operator_index() {
    DoublyLinkedList<char> list;
    list.push_back('A');
    list.push_back('B');
    list.push_back('C');

    std::cout << "List: ";
    list.print_forward(); // A B C

    list[1] = 'Z';         // change B to Z
    std::cout << "After list[1] = 'Z': ";
    list.print_forward(); // A Z C

    try {
        std::cout << "Accessing invalid index: ";
        std::cout << list[10]; // Should throw
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
}

void test_iterators() {
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 5; ++i) list.push_back(i);

    std::cout << "Using iterator: ";
    for (auto it = list.begin(); it != list.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "Using const_iterator: ";
    const DoublyLinkedList<int> constList = list;
    for (auto it = constList.begin(); it != constList.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "--- Basic Operations ---\n";
    test_basic_operations();

    std::cout << "\n--- Remove, Pop, Find ---\n";
    test_remove_pop_find();

    std::cout << "\n--- Copy Behavior ---\n";
    test_copy_behavior();

    std::cout << "\n--- Operator[] Test ---\n";
    test_operator_index();

    std::cout << "\n--- Iterator Test ---\n";
    test_iterators();

    return 0;
}
