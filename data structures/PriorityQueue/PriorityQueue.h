#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;
    int size_;
    std::unordered_map<T, int> mp;

    void up(int i) {
        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            int p = (i - 1) / 2;
            std::swap(heap[i], heap[p]);
            mp[heap[i]] = i;
            mp[heap[p]] = p;
            i = p;
        }
    }

    void down(int i) {
        while (2 * i + 1 < size_) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < size_ && heap[left] > heap[largest]) largest = left;
            if (right < size_ && heap[right] > heap[largest]) largest = right;
            if (largest == i) break;
            std::swap(heap[i], heap[largest]);
            mp[heap[i]] = i;
            mp[heap[largest]] = largest;
            i = largest;
        }
    }

public:
    PriorityQueue() : size_(0) {}

    PriorityQueue& operator=(const PriorityQueue& other) {
        if (this != &other) {
            heap = other.heap;
            mp = other.mp;
            size_ = other.size_;
        }
        return *this;
    }

    int size() const { return size_; }

    bool empty() const { return size_ == 0; }

    void push(T value) {
        heap.push_back(value);
        mp[value] = size_;
        up(size_);
        size_++;
    }

    void pop() {
        if (empty()) return;
        mp.erase(heap[0]);
        heap[0] = heap[size_ - 1];
        mp[heap[0]] = 0;
        heap.pop_back();
        size_--;
        down(0);
    }

    T top() {
        if (empty()) throw std::runtime_error("Empty PriorityQueue");
        return heap[0];
    }
};
