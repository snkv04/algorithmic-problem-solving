class RandomizedSet {
private:
    unordered_map<int, int> val_to_idx;
    vector<int> list;

public:
    RandomizedSet() {
        // do nothing, as all instance variables are default-initialized
    }
    
    bool insert(int val) {
        if (val_to_idx.find(val) != val_to_idx.end()) {
            return false;
        }

        val_to_idx[val] = list.size();
        list.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (val_to_idx.find(val) == val_to_idx.end()) {
            return false;
        }

        // swaps the value with the last one in the list
        int index = val_to_idx[val];
        swap(list[list.size() - 1], list[index]);

        // removes the value at the end of the list
        list.pop_back();
        val_to_idx.erase(val);

        // updates the index of the moved value
        if (index < list.size()) {
            val_to_idx[list[index]] = index;
        }

        return true;
    }
    
    int getRandom() {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> dist = uniform_int_distribution<int>(
            0, list.size() - 1
        );
        // calling the distribution basically samples from it
        int index = dist(rng);
        return list[index];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
