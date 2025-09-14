class RandomizedCollection {
private:
    unordered_map<int, unordered_set<int>> val_to_indices;
    vector<int> vals;

public:
    RandomizedCollection() {
        // do nothing
    }
    
    bool insert(int val) {
        bool result = val_to_indices.find(val) == val_to_indices.end();
        val_to_indices[val].insert(vals.size());
        vals.push_back(val);
        return result;
    }
    
    bool remove(int val) {
        if (val_to_indices.find(val) == val_to_indices.end()) {
            return false;
        }

        int index = *(val_to_indices[val].begin());
        if (val_to_indices[val].size() == 1) {
            val_to_indices.erase(val);
        } else {
            val_to_indices[val].erase(index);
        }

        if (index == vals.size() - 1) {
            vals.pop_back();
        } else {
            int other_val = vals.back();
            swap(vals.back(), vals[index]);
            vals.pop_back();
            val_to_indices[other_val].erase(vals.size());
            val_to_indices[other_val].insert(index);
        }
        return true;
    }
    
    int getRandom() {
        // mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        // uniform_int_distribution<int> dist = uniform_int_distribution<int>(0, vals.size() - 1);
        // return vals[dist(rng)];

        // much faster of an RNG but less dependable; see https://codeforces.com/blog/entry/61587
        return vals[rand() % vals.size()];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
