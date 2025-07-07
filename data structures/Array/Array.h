#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class Arr {
private:
    T* data;
    int Size;
    int Capacity;

    void resize() {
        if (Capacity == 0) Capacity = 1;
        Capacity *= 2;
        T* newData = new T[Capacity];
        for (int i = 0; i < Size; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

    void CheckRange(int index) const {
        if (index < 0 || index >= Size)
            throw std::out_of_range("Index Out Of Range");
    }

public:
    Arr() : data(new T[2]), Size(0), Capacity(2) {}

    ~Arr() {
        delete[] data;
    }


    Arr(const Arr& other) : Size(other.Size), Capacity(other.Capacity) {
        data = new T[Capacity];
        for (int i = 0; i < Size; i++)
            data[i] = other.data[i];
    }

    
    Arr& operator=(const Arr& other) {
        if (this != &other) {
            delete[] data;
            Size = other.Size;
            Capacity = other.Capacity;
            data = new T[Capacity];
            for (int i = 0; i < Size; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    void push(const T& value) {
        if (Size == Capacity)
            resize();
        data[Size++] = value;
    }

    void pop() {
        if (empty())
            throw std::out_of_range("Array Is Empty");
        Size--;
    }

    void insert(int index, const T& value) {
        if (index < 0 || index > Size)
            throw std::out_of_range("Index Out Of Range");
        if (Size == Capacity)
            resize();
        for (int i = Size; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        Size++;
    }

    void removeIndex(int index) {
        CheckRange(index);
        for (int i = index; i < Size - 1; i++)
            data[i] = data[i + 1];
        Size--;
    }

    void removeCntNum(const T& value, int count = 1) {
        for (int i = 0; i < Size && count > 0; i++) {
            if (data[i] == value) {
                removeIndex(i);
                i--;
                count--;
            }
        }
    }

    void removeNum(const T& value) {
        removeCntNum(value, Size);
    }

    bool empty() const noexcept {
        return Size == 0;
    }

    int size() const noexcept {
        return Size;
    }

    void clear() noexcept {
        Size = 0;
    }

    T& operator[](int index) {
        CheckRange(index);
        return data[index];
    }

    const T& operator[](int index) const {
        CheckRange(index);
        return data[index];
    }

    T* begin() { return data; }
    T* end() { return data + Size; }

    const T* begin() const { return data; }
    const T* end() const { return data + Size; }
};
