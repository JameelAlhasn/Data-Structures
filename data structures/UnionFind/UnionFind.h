#include <vector>
#include <unordered_map>

template <typename T>
class UnionFind {
private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> rank;

public:
    void make_set(const T &x) {
        parent[x] = x;
        rank[x] = 0;
    }

    T find(const T &x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_sets(const T &x, const T &y) {
        T px = find(x);
        T py = find(y);
        if (px != py) {
            if (rank[px] < rank[py])
                parent[px] = py;
            else if (rank[px] > rank[py])
                parent[py] = px;
            else {
                parent[py] = px;
                rank[px]++;
            }
        }
    }

    bool same_set(const T& x, const T& y) {
        return find(x) == find(y);
    }
};
