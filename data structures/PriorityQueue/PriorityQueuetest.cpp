#include <iostream>
#include "PriorityQueue.h"
using namespace std;
int main() {
    cout << "===== Testing PriorityQueue with int =====" << endl;
    PriorityQueue<int> pq;

    pq.push(10);
    pq.push(30);
    pq.push(20);

    cout << "Top: " << pq.top() << " (Expected: 30)" << endl;

    pq.pop();
    cout << "Top after 1st pop: " << pq.top() << " (Expected: 20)" << endl;

    pq.push(40);
    cout << "Top after pushing 40: " << pq.top() << " (Expected: 40)" << endl;

    while (!pq.empty()) {
        cout << "Popping: " << pq.top() << endl;
        pq.pop();
    }

    cout << "Queue empty? " << (pq.empty() ? "Yes" : "No") << endl;

    return 0;
}
