template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &val) : data(val), next(nullptr) {}
    };

    Node *front_;
    Node *back_;
    int size_;

    void clear()
    {
        while (!empty())
            pop();
    }

public:
    Queue() : front_(nullptr), back_(nullptr), size_(0) {}

    ~Queue() { clear(); }

    Queue(const Queue &other) : front_(nullptr), back_(nullptr), size_(0)
    {
        for (Node *cur = other.front_; cur; cur = cur->next)
            push(cur->data);
    }

    Queue &operator=(const Queue &other)
    {
        if (this != &other)
        {
            Queue temp(other);
            swap(temp);
        }
        return *this;
    }

    void swap(Queue &other)
    {
        std::swap(front_, other.front_);
        std::swap(back_, other.back_);
        std::swap(size_, other.size_);
    }

    int size() const { return size_; }

    bool empty() const { return size_ == 0; }

    void push(const T &value)
    {
        Node *newNode = new Node(value);
        if (empty())
        {
            front_ = back_ = newNode;
        }
        else
        {
            back_->next = newNode;
            back_ = newNode;
        }
        ++size_;
    }

    void pop()
    {
        if (empty())
            throw std::runtime_error("Queue is empty");

        Node *temp = front_;
        front_ = front_->next;
        delete temp;
        --size_;
        if (!front_)
            back_ = nullptr;
    }

    T &front()
    {
        if (empty())
            throw std::runtime_error("Queue is empty");
        return front_->data;
    }

    const T &front() const
    {
        if (empty())
            throw std::runtime_error("Queue is empty");
        return front_->data;
    }
};
