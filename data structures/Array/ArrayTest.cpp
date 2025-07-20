#include "Array.h"
// ======= Utility Function =======
void print(const Arr<int>& a, const std::string& label = "") {
    std::cout << label;
    for (auto x : a)
        std::cout << x << ' ';
    std::cout << '\n';
}

// ======= Test: Basic Insertion and Access =======
void testBasic() {
    std::cout << "=== Basic Push/Pop Test ===\n";
    Arr<int> a;
    a.push(5);
    a.push(10);
    a.push(15);
    print(a, "After push: ");  // Expect: 5 10 15

    a.pop();                   // Remove 15
    print(a, "After pop: ");   // Expect: 5 10

    std::cout << "Element at index 1: " << a[1] << "\n\n";  // Expect 10
}

// ======= Test: Insert at Index =======
void testInsert() {
    std::cout << "=== Insert Test ===\n";
    Arr<int> a;
    a.push(1);
    a.push(3);
    a.insert(1, 2);            // Insert 2 between 1 and 3
    print(a);                  // Expect: 1 2 3

    a.insert(0, 0);            // Insert 0 at front
    a.insert(a.size(), 4);     // Insert 4 at end
    print(a);                  // Expect: 0 1 2 3 4
    std::cout << '\n';
}

// ======= Test: Remove by Index & Value =======
void testRemove() {
    std::cout << "=== Remove Test ===\n";
    Arr<int> a;
    for (int i = 1; i <= 5; i++) a.push(i); // [1, 2, 3, 4, 5]
    a.removeIndex(2);                      // Remove element at index 2 -> [1, 2, 4, 5]
    print(a);

    a.removeCntNum(4);                     // Remove one '4' -> [1, 2, 5]
    print(a);

    a.push(2);
    a.push(2);
    print(a, "Before removeNum(2): ");
    a.removeNum(2);                        // Remove all '2' -> [1, 5]
    print(a, "After removeNum(2): ");
    std::cout << '\n';
}

// ======= Test: Copy Semantics =======
void testCopy() {
    std::cout << "=== Copy Semantics Test ===\n";
    Arr<std::string> a;
    a.push("apple");
    a.push("banana");

    Arr<std::string> b = a;  // Copy constructor
    Arr<std::string> c;
    c = a;                   // Copy assignment

    std::cout << "Original: ";
    for (auto& s : a) std::cout << s << ' ';
    std::cout << "\nCopy1: ";
    for (auto& s : b) std::cout << s << ' ';
    std::cout << "\nCopy2: ";
    for (auto& s : c) std::cout << s << ' ';
    std::cout << "\n\n";
}

// ======= Test: Bounds Checking =======
void testBounds() {
    std::cout << "=== Out-of-Range Test ===\n";
    Arr<int> a;
    a.push(42);
    try {
        std::cout << a[5] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }

    try {
        a.insert(100, 5);
    } catch (const std::out_of_range& e) {
        std::cout << "Insert error: " << e.what() << '\n';
    }

    try {
        a.removeIndex(-1);
    } catch (const std::out_of_range& e) {
        std::cout << "Remove error: " << e.what() << '\n';
    }

    a.clear();
    try {
        a.pop();
    } catch (const std::out_of_range& e) {
        std::cout << "Pop error: " << e.what() << '\n';
    }

    std::cout << '\n';
}

// ======= MAIN =======
int main() {
    testBasic();
    testInsert();
    testRemove();
    testCopy();
    testBounds();
    return 0;
}
