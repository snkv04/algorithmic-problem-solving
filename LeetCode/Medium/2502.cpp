class Allocator {
    map<int, int> free;
    map<int, unordered_map<int, int>> allocated;

    void release(const pair<int, int> &block) {
        int ptr = block.first, size = block.second;

        // check to the right
        if (
            free.upper_bound(ptr) != free.end() &&
            free.upper_bound(ptr)->first == ptr + size
        ) {
            size += free[ptr + size];
            free.erase(free.upper_bound(ptr));
        }
        
        // check to the left
        auto it = free.lower_bound(ptr);
        if (it != free.begin()) {
            --it;
            if (it->first + it->second == ptr) {
                ptr = it->first;
                size += it->second;
                free.erase(ptr);
            }
        }

        free[ptr] = size;
    }

public:
    Allocator(int n) {
        free[0] = n;
    }
    
    int allocate(int size, int mID) {
        pair<int, int> freeing = {-1, -1};
        for (const pair<int, int> &block : free) {
            if (block.second >= size) {
                freeing = block;
                break;
            }
        }

        if (freeing.first == -1) {
            return -1;
        } else {
            free.erase(freeing.first);
            if (freeing.second > size) {
                free[freeing.first + size] = freeing.second - size;
            }
            allocated[mID].insert(make_pair(freeing.first, size));
            return freeing.first;
        }
    }
    
    int freeMemory(int mID) {
        if (
            allocated.find(mID) == allocated.end() ||
            allocated[mID].empty()
        ) {
            return 0;
        }

        int count = 0;
        for (const pair<int, int> &block : allocated[mID]) {
            release(block);
            count += block.second;
        }
        allocated.erase(mID);
        return count;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */
