#include <vector>
#include <functional>
#include <stdexcept>
#include <optional>

template <typename K, typename V>
class HashMap
{
    enum class State
    {
        EMPTY,
        FILLED,
        DELETED
    };

    struct Entry
    {
        K key;
        V value;
        State state = State::EMPTY;
    };

    std::vector<Entry> table;
    size_t current_size;
    float max_load = 0.6;

    size_t hash1(const K &key) const
    {
        return std::hash<K>{}(key) % table.size();
    }

    size_t hash2(const K &key) const
    {
        return 1 + (std::hash<K>{}(key) % (table.size() - 1)); // must be non-zero
    }

    void rehash()
    {
        std::vector<Entry> old_table = table;
        table = std::vector<Entry>(old_table.size() * 2);
        current_size = 0;
        for (const auto &entry : old_table)
        {
            if (entry.state == State::FILLED)
            {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashMap(size_t initial_capacity = 8) : table(initial_capacity), current_size(0) {}

    void insert(const K &key, const V &value)
    {
        if ((float)(current_size + 1) / table.size() > max_load)
            rehash();

        size_t h1 = hash1(key);
        size_t h2 = hash2(key);
        size_t idx = h1;

        for (size_t i = 0; i < table.size(); ++i)
        {
            idx = (h1 + i * h2) % table.size();
            if (table[idx].state == State::EMPTY || table[idx].state == State::DELETED || table[idx].key == key)
            {
                if (table[idx].state != State::FILLED)
                    current_size++;
                table[idx] = {key, value, State::FILLED};
                return;
            }
        }
        throw std::overflow_error("HashMap full (should not happen with rehashing)");
    }

    std::optional<V> find(const K &key) const
    {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        for (size_t i = 0; i < table.size(); ++i)
        {
            size_t idx = (h1 + i * h2) % table.size();
            if (table[idx].state == State::EMPTY)
                break;
            if (table[idx].state == State::FILLED && table[idx].key == key)
                return table[idx].value;
        }
        return std::nullopt;
    }

    bool erase(const K &key)
    {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);

        for (size_t i = 0; i < table.size(); ++i)
        {
            size_t idx = (h1 + i * h2) % table.size();
            if (table[idx].state == State::EMPTY)
                break;
            if (table[idx].state == State::FILLED && table[idx].key == key)
            {
                table[idx].state = State::DELETED;
                current_size--;
                return true;
            }
        }
        return false;
    }

    V &operator[](const K &key)
    {
        size_t h1 = hash1(key);
        size_t h2 = hash2(key);
        size_t first_deleted = table.size(); // marker for first deleted spot

        for (size_t i = 0; i < table.size(); ++i)
        {
            size_t idx = (h1 + i * h2) % table.size();
            if (table[idx].state == State::FILLED && table[idx].key == key)
                return table[idx].value;

            if (table[idx].state == State::DELETED && first_deleted == table.size())
                first_deleted = idx;

            if (table[idx].state == State::EMPTY)
            {
                size_t insert_at = (first_deleted != table.size()) ? first_deleted : idx;
                current_size++;
                table[insert_at] = {key, V(), State::FILLED};
                return table[insert_at].value;
            }
        }

        throw std::overflow_error("HashMap full (should not happen with rehashing)");
    }

    size_t size() const
    {
        return current_size;
    }
};
