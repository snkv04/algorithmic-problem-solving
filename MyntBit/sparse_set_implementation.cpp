#include <vector>
#include <algorithm>

class SparseSet {
private:
    std::vector<int> dense, sparse;
    int start;

public:
    SparseSet(int max_id) {
        start = 0;
        sparse = std::vector<int>(max_id + 1, -1);
    }

    bool insert(int val) {
        if (sparse[val] >= start) {
            return false;
        } else {
            sparse[val] = dense.size() + start;
            dense.push_back(val);
            return true;
        }
    }

    bool remove(int val) {
        if (sparse[val] < start) {
            return false;
        } else {
            int idx = sparse[val] - start;
            if (idx != dense.size() - 1) {
                int other_val = dense.back();
                std::swap(dense[idx], dense[dense.size() - 1]);
                std::swap(sparse[val], sparse[other_val]);
            }
            sparse[val] = -1;
            dense.pop_back();
            return true;
        }
    }

    bool contains(int val) const {
        return sparse[val] >= start;
    }

    void clear() {
        start += dense.size();
        dense.clear();
    }

    int size() const {
        return dense.size();
    }

    const std::vector<int>& get_dense() const {
        return dense;
    }
};
