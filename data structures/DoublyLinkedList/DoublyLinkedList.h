#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    int size_;
    Node *head;
    Node *tail;

    void checkIndex(int index, bool allowEqual = false) const
    {
        if (index < 0 || index > size_ || (!allowEqual && index == size_))
        {
            throw std::out_of_range("Index out of range");
        }
    }

public:
    DoublyLinkedList() : size_(0), head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList() { clear(); }

    void clear()
    {
        Node *cur = head;
        while (cur)
        {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        size_ = 0;
    }
    int size() const { return size_; }
    bool empty() const { return !(size_); }
    void push_back(const T &value) { insert(size_, value); }
    void push_front(const T &value) { insert(0, value); }
    void insert(int index, const T &value)
    {
        checkIndex(index, true);
        Node *newNode = new Node(value);

        if (index == 0)
        {
            newNode->next = head;
            if (head)
                head->prev = newNode;
            head = newNode;
            if (!tail)
                tail = newNode;
        }
        else if (index == size_)
        {
            newNode->prev = tail;
            if (tail)
                tail->next = newNode;
            tail = newNode;
            if (!head)
                head = newNode;
        }
        else
        {
            Node *cur;
            if (index < size_ / 2)
            {
                cur = head;
                for (int i = 0; i < index; ++i)
                    cur = cur->next;
            }
            else
            {
                cur = tail;
                for (int i = size_ - 1; i > index; --i)
                    cur = cur->prev;
            }

            newNode->prev = cur->prev;
            newNode->next = cur;
            if (cur->prev)
                cur->prev->next = newNode;
            cur->prev = newNode;
        }

        ++size_;
    }
    void pop_front() { remove(0); }
    void pop_back() { remove(size_ - 1); }
    void remove(int index)
    {
        checkIndex(index);
        Node *cur;

        if (index < size_ / 2)
        {
            cur = head;
            for (int i = 0; i < index; ++i)
                cur = cur->next;
        }
        else
        {
            cur = tail;
            for (int i = size_ - 1; i > index; --i)
                cur = cur->prev;
        }

        if (cur->prev)
            cur->prev->next = cur->next;
        else
            head = cur->next;

        if (cur->next)
            cur->next->prev = cur->prev;
        else
            tail = cur->prev;

        delete cur;
        --size_;
    }
    T pop()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }
        T value = back();
        pop_back();
        return value;
    }
    T front() const
    {
        if (empty())
            throw std::runtime_error("List is empty");
        return head->data;
    }

    T back() const
    {
        if (empty())
            throw std::runtime_error("List is empty");
        return tail->data;
    }

    int find(const T &value) const
    {
        Node *cur = head;
        int index = 0;
        while (cur)
        {
            if (cur->data == value)
                return index;
            cur = cur->next;
            ++index;
        }
        return -1;
    }
    bool contains(const T &value) const { return find(value) != -1; }
    void print_forward() const
    {
        Node *cur = head;
        while (cur)
        {
            std::cout << cur->data << ' ';
            cur = cur->next;
        }
        std::cout << "\n";
    }

    void print_backward() const
    {
        Node *cur = tail;
        while (cur)
        {
            std::cout << cur->data << ' ';
            cur = cur->prev;
        }
        std::cout << "\n";
    }
    T &operator[](int index)
    {
        checkIndex(index);
        Node *cur;
        if (index < size_ / 2)
        {
            cur = head;
            for (int i = 0; i < index; i++)
                cur = cur->next;
        }
        else
        {
            cur = tail;
            for (int i = size_ - 1; i > index; i--)
                cur = cur->prev;
        }
        return cur->data;
    }
    DoublyLinkedList(const DoublyLinkedList &other) : size_(0), head(nullptr), tail(nullptr)
    {
        for (Node *cur = other.head; cur; cur = cur->next)
        {
            push_back(cur->data);
        }
    }
    DoublyLinkedList &operator=(const DoublyLinkedList &other)
    {
        if (this != &other)
        {
            clear();
            for (Node *cur = other.head; cur; cur = cur->next)
            {
                push_back(cur->data);
            }
        }
        return *this;
    }

    class iterator
    {
    private:
        Node *node;

    public:
        iterator(Node *ptr) : node(ptr) {}

        T &operator*() const { return node->data; }

        iterator &operator++()
        {
            node = node->next;
            return *this;
        }
        iterator &operator--()
        {
            node = node->prev;
            return *this;
        }

        bool operator!=(const iterator &other) const { return node != other.node; }
        bool operator==(const iterator &other) const { return node == other.node; }
    };
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    class const_iterator
    {
    private:
        const Node *node;

    public:
        const_iterator(const Node *ptr) : node(ptr) {}

        const T &operator*() const { return node->data; }

        const_iterator &operator++()
        {
            node = node->next;
            return *this;
        }

        const_iterator &operator--()
        {
            node = node->prev;
            return *this;
        }

        bool operator!=(const const_iterator &other) const { return node != other.node; }
        bool operator==(const const_iterator &other) const { return node == other.node; }
    };

    const_iterator begin() const { return const_iterator(head); }
    const_iterator end() const { return const_iterator(nullptr); }
};

