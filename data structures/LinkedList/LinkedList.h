#include <iostream>
// #include <string>
// #include <stdexcept>

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        explicit Node(const T &val) : data(val), next(nullptr) {}
    };
    Node *head;
    int size_;

    void checkIndex(int index, bool allowEqual = false) const
    {
        if (index < 0 || index > size_ || (!allowEqual && index == size_))
        {
            throw std::out_of_range("Index Out Of Range");
        }
    }

public:
    LinkedList() : head(nullptr), size_(0) {}

    ~LinkedList()
    {
        clear();
    }

    LinkedList(const LinkedList &other) : head(nullptr), size_(0)
    {
        Node *cur = other.head;
        while (cur)
        {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    LinkedList &operator=(const LinkedList &other)
    {
        if (this != &other)
        {
            clear();
            Node *cur = other.head;
            while (cur)
            {
                push_back(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    void clear() noexcept
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        size_ = 0;
    }

    int size() const
    {
        return size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    void push_front(const T &value)
    {
        insert(0, value);
    }

    void push_back(const T &value)
    {
        insert(size_, value);
    }

    void insert(int index, const T &value)
    {
        checkIndex(index, true);

        Node *newNode = new Node(value);

        if (index == 0)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; ++i)
                current = current->next;

            newNode->next = current->next;
            current->next = newNode;
        }
        ++size_;
    }

    void remove(int index)
    {
        checkIndex(index);

        if (index == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; ++i)
                current = current->next;

            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
        }

        --size_;
    }

    void pop(const T &value)
    {
        if (!head)
            return;

        if (head->data == value)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            --size_;
            return;
        }

        Node *current = head;
        while (current->next && current->next->data != value)
            current = current->next;

        if (current->next)
        {
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
            --size_;
        }
    }

    void pop_back()
    {
        remove(size_ - 1);
    }

    void pop_front()
    {
        remove(0);
    }
    T& operator[](int index) const
    {
        checkIndex(index);
        Node *current = head;
        for (int i = 0; i < index; ++i)
            current = current->next;
        return current->data;
    }

    void print(const std::string &sep = " ", const std::string &end = "\n") const
    {
        Node *current = head;
        while (current)
        {
            std::cout << current->data << sep;
            current = current->next;
        }
        std::cout << end;
    }
};

