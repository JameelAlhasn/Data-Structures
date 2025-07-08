#include <iostream>
#include <stdexcept>
template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node(const T &val) : data(val), prev(nullptr) {}
    };
    Node *head;
    int size_;
    void clear()
    {
        while (head)
        {
            Node *temp = head;
            head = head->prev;
            delete temp;
        }
    }

public:
    Stack() : head(nullptr), size_(0) {}
    ~Stack() { clear(); }
    template <typename... Args>
    void emplace(Args &&...args)
    {
        Node *newNode = new Node(T(std::forward<Args>(args)...));
        newNode->prev = head;
        head = newNode;
        size_++;
    }
    bool empty()
    {
        return !(size_);
    }
    void pop()
    {
        if (empty())
            throw std::runtime_error("Stack empty cant pop");
        Node *temp = head;
        head = head->prev;
        delete temp;
        size_--;
    }
    void push(T value)
    {
        Node *newNode = new Node(value);
        newNode->prev = head;
        head = newNode;
        size_++;
    }
    int size()
    {
        return size_;
    }
    void swap(Stack &other)
    {
        std::swap(head, other.head);
        std::swap(size_, other.size_);
    }
    friend void swap(Stack &a, Stack &b)
    {
        a.swap(b);
    }
    T &top()
    {
        if (empty())
            throw std::runtime_error("Stack empty cant pop");
        return head->data;
    }
    const T &top() const
    {
        if (empty())
            throw std::runtime_error("Stack empty cant pop");
        return head->data;
    }
};
