class RangeModule {
    std::map<int, int> l_to_r;

public:
    RangeModule() {
        
    }
    
    void addRange(int left, int right) {
        while (
            l_to_r.lower_bound(left) != l_to_r.end() &&
            l_to_r.lower_bound(left)->first <= right
        ) {
            auto it = l_to_r.lower_bound(left);
            int prev_right = it->second;
            l_to_r.erase(it);
            right = max(prev_right, right);
        }

        auto it = l_to_r.upper_bound(left);
        if (it != l_to_r.begin()) {
            --it;
            if (it->second >= left) {
                left = it->first;
                right = max(right, it->second);
                l_to_r.erase(it);
            }
        }

        l_to_r[left] = right;
    }
    
    bool queryRange(int left, int right) {
        auto it = l_to_r.upper_bound(left);
        if (it != l_to_r.begin()) {
            --it;
            if (it->second >= right) {
                return true;
            }
        }
        return false;
    }
    
    void removeRange(int left, int right) {
        auto it = l_to_r.lower_bound(left);
        if (it != l_to_r.begin()) {
            --it;
            if (it->second > right) {
                l_to_r[right] = it->second;
            }
            if (it->second > left) {
                it->second = left;
            }
        }

        while (
            l_to_r.lower_bound(left) != l_to_r.end() &&
            l_to_r.lower_bound(left)->first < right
        ) {
            auto it = l_to_r.lower_bound(left);
            if (it->second > right) {
                int ins_l = right, ins_r = it->second;
                l_to_r.erase(it);
                l_to_r[ins_l] = ins_r;
                break;
            } else {
                l_to_r.erase(it);
            }
        }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
