#include <vector>
#include <functional>
#include <stdexcept>
#include <optional>

template <typename K, typename V>
class HashMap {
    enum class State { EMPTY, FILLED, DELETED };

    struct Entry {
        K key;
        V value;
        State state = State::EMPTY;
    };

    std::vector<Entry> table;
    size_t current_size;
    float max_load = 0.6;

    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % table.size();
    }

    void rehash() {
        std::vector<Entry> old_table = table;
        table = std::vector<Entry>(old_table.size() * 2);
        current_size = 0;
        for (const auto& entry : old_table) {
            if (entry.state == State::FILLED) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashMap(size_t initial_capacity = 8) : table(initial_capacity), current_size(0) {}

    void insert(const K& key, const V& value) {
        if ((float)(current_size + 1) / table.size() > max_load)
            rehash();

        size_t idx = hash(key);
        while (table[idx].state == State::FILLED && table[idx].key != key) {
            idx = (idx + 1) % table.size();
        }

        if (table[idx].state != State::FILLED) current_size++;
        table[idx] = {key, value, State::FILLED};
    }

    std::optional<V> find(const K& key) const {
        size_t idx = hash(key);
        size_t start = idx;
        while (table[idx].state != State::EMPTY) {
            if (table[idx].state == State::FILLED && table[idx].key == key)
                return table[idx].value;
            idx = (idx + 1) % table.size();
            if (idx == start) break;
        }
        return std::nullopt;
    }
    bool erase(const K& key) {
        size_t idx = hash(key);
        size_t start = idx;
        while (table[idx].state != State::EMPTY) {
            if (table[idx].state == State::FILLED && table[idx].key == key) {
                table[idx].state = State::DELETED;
                current_size--;
                return true;
            }
            idx = (idx + 1) % table.size();
            if (idx == start) break;
        }
        return false;
    }

    V& operator[](const K& key) {
        size_t idx = hash(key);
        while (table[idx].state == State::FILLED && table[idx].key != key) {
            idx = (idx + 1) % table.size();
        }
        if (table[idx].state != State::FILLED) {
            current_size++;
            table[idx] = {key, V(), State::FILLED};
        }
        return table[idx].value;
    }

    size_t size() const {
        return current_size;
    }

};
