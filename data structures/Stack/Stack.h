#include <stdexcept>
#include <utility>

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
        size_ = 0;
    }

    void copyFrom(const Stack &other)
    {
        if (other.head == nullptr) return;
        Stack<T> temp;
        for (Node *cur = other.head; cur != nullptr; cur = cur->prev)
            temp.push(cur->data);
        for (Node *cur = temp.head; cur != nullptr; cur = cur->prev)
            push(cur->data);
    }

public:
    Stack() : head(nullptr), size_(0) {}
    ~Stack() { clear(); }

    Stack(const Stack &other) : head(nullptr), size_(0)
    {
        copyFrom(other);
    }

    Stack &operator=(const Stack &other)
    {
        if (this != &other)
        {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    Stack(Stack &&other) noexcept : head(other.head), size_(other.size_)
    {
        other.head = nullptr;
        other.size_ = 0;
    }

    Stack &operator=(Stack &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            head = other.head;
            size_ = other.size_;
            other.head = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    template <typename... Args>
    void emplace(Args &&...args)
    {
        Node *newNode = new Node(T(std::forward<Args>(args)...));
        newNode->prev = head;
        head = newNode;
        size_++;
    }

    void push(const T &value)
    {
        Node *newNode = new Node(value);
        newNode->prev = head;
        head = newNode;
        size_++;
    }

    void pop()
    {
        if (empty())
            throw std::runtime_error("Stack empty can't pop");
        Node *temp = head;
        head = head->prev;
        delete temp;
        size_--;
    }

    T &top()
    {
        if (empty())
            throw std::runtime_error("Stack empty can't access top");
        return head->data;
    }

    const T &top() const
    {
        if (empty())
            throw std::runtime_error("Stack empty can't access top");
        return head->data;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    int size() const
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
};
