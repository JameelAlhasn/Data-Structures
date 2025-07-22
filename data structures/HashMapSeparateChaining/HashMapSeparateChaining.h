// #pragma once
#include <vector>
#include <list>
#include <utility>
#include <stdexcept>
#include <functional>
#include <cstdint>

template <typename K, typename V>
class HashMap {
    static const int BucketCount = 131;
    std::vector<std::list<std::pair<K, V>>> table;
    int size_;

    size_t hash(const K& key) const {
        std::hash<K> hasher;
        uint64_t x = hasher(key);
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        x = x ^ (x >> 31);
        return x % BucketCount;
    }

public:
    HashMap() : table(BucketCount), size_(0) {}

    HashMap(const HashMap& other) : table(BucketCount), size_(0) {
        for (int i = 0; i < BucketCount; ++i) {
            for (const auto& p : other.table[i]) {
                table[i].emplace_back(p.first, p.second);
                ++size_;
            }
        }
    }

    HashMap& operator=(const HashMap& other) {
        if (this != &other) {
            clear();
            for (int i = 0; i < BucketCount; ++i) {
                for (const auto& p : other.table[i]) {
                    table[i].emplace_back(p.first, p.second);
                    ++size_;
                }
            }
        }
        return *this;
    }

    V& operator[](const K& key) {
        size_t idx = hash(key);
        for (auto& [k, v] : table[idx])
            if (k == key)
                return v;
        table[idx].emplace_back(key, V{});
        ++size_;
        return table[idx].back().second;
    }

    V& at(const K& key) {
        size_t idx = hash(key);
        for (auto& [k, v] : table[idx])
            if (k == key)
                return v;
        throw std::out_of_range("Key not found");
    }

    bool insert(const K& key, const V& value) {
        size_t idx = hash(key);
        for (const auto& [k, _] : table[idx])
            if (k == key)
                return false;
        table[idx].emplace_back(key, value);
        ++size_;
        return true;
    }

    bool erase(const K& key) {
        size_t idx = hash(key);
        auto& bucket = table[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& key) const {
        size_t idx = hash(key);
        for (const auto& [k, _] : table[idx])
            if (k == key)
                return true;
        return false;
    }

    void clear() {
        for (auto& bucket : table)
            bucket.clear();
        size_ = 0;
    }

    int size() const { return size_; }
    bool empty() const { return size_ == 0; }

    class Iterator {
        using OuterIt = typename std::vector<std::list<std::pair<K, V>>>::const_iterator;
        using InnerIt = typename std::list<std::pair<K, V>>::const_iterator;

        OuterIt outer, outer_end;
        InnerIt inner;

        void advanceToValid() {
            while (outer != outer_end && inner == outer->end()) {
                ++outer;
                if (outer != outer_end) inner = outer->begin();
            }
        }

    public:
        Iterator(OuterIt o, OuterIt o_end) : outer(o), outer_end(o_end) {
            if (outer != outer_end) inner = outer->begin();
            advanceToValid();
        }

        const std::pair<K, V>& operator*() const { return *inner; }
        const std::pair<K, V>* operator->() const { return &(*inner); }

        Iterator& operator++() {
            ++inner;
            advanceToValid();
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return outer != other.outer || (outer != outer_end && inner != other.inner);
        }
    };

    Iterator begin() const {
        return Iterator(table.begin(), table.end());
    }

    Iterator end() const {
        return Iterator(table.end(), table.end());
    }
};
