#include <bits/stdc++.h>

// differs from std::multiset<T> in that all objects with identical keys are considered identical,
// so then count() is O(1) instead of up to O(frequency of key)
template <typename T>
struct Multiset {
    void add(T object) {
        counts[object] += 1;
    }

    void remove(T object) {
        if (counts.find(object) == counts.end()) {
            throw std::logic_error("Object not found in multiset");
        }

        counts[object] -= 1;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    void add(T object, long long delta) {
        assert(delta >= 0);
        counts[object] += delta;
    }

    void remove(T object, long long delta) {
        assert(delta >= 0);
        if (counts.find(object) == counts.end() || counts[object] < delta) {
            throw std::logic_error("Not enough instances of object in multiset");
        }

        counts[object] -= delta;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    long long count(T object) {
        if (counts.find(object) == counts.end()) {
            return 0;
        } else {
            return counts[object];
        }
    }
    
    bool empty() {
        return counts.empty();
    }

private:
    std::unordered_map<T, long long> counts;
};
