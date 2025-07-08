#include <iostream>
#include "Queue.h"
int main()
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    std::cout << "Front: " << q.front() << "\n"; // 1
    q.pop();
    std::cout << "Front after pop: " << q.front() << "\n"; // 2
    std::cout << "Size: " << q.size() << "\n";             // 2

    Queue<int> q2 = q;
    std::cout << "Copy front: " << q2.front() << "\n"; // 2

    return 0;
}
