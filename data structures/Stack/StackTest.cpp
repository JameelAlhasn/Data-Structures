#include <iostream>
#include "Stack.h"
void test_basic_operations()
{
    std::cout << "--- Basic Stack Operations ---\n";
    Stack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);
    std::cout << "Top: " << st.top() << "\n"; // 30
    st.pop();
    std::cout << "Top after pop: " << st.top() << "\n"; // 20
    std::cout << "Size: " << st.size() << "\n";         // 2
}

void test_emplace()
{
    std::cout << "\n--- Emplace Test ---\n";
    Stack<std::pair<int, std::string>> st;
    st.emplace(1, "hello");
    st.emplace(2, "world");
    std::cout << "Top pair: " << st.top().first << ", " << st.top().second << "\n"; // 2, world
}

void test_swap()
{
    std::cout << "\n--- Swap Test ---\n";
    Stack<int> a, b;
    a.push(1);
    a.push(2);
    b.push(9);

    std::cout << "Before swap:\n";
    std::cout << "A top: " << a.top() << ", B top: " << b.top() << "\n";

    a.swap(b);

    std::cout << "After swap:\n";
    std::cout << "A top: " << a.top() << ", B top: " << b.top() << "\n";
}

void test_exceptions()
{
    std::cout << "\n--- Exception Handling ---\n";
    Stack<int> st;
    try
    {
        st.pop();
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught: " << e.what() << "\n";
    }

    try
    {
        st.top();
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught: " << e.what() << "\n";
    }
}
int main()
{
    test_basic_operations();
    test_emplace();
    test_swap();
    test_exceptions();
    return 0;
}
