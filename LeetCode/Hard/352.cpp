class SummaryRanges {
private:
    map<int, int> left_to_right;

public:
    SummaryRanges() {
        left_to_right = map<int, int>();
    }
    
    void addNum(int value) {
        // check if it's already there
        auto containing = left_to_right.lower_bound(value);
        if (containing->first == value) {
            return;
        }
        if (containing != left_to_right.begin()) {
            --containing;
            if (containing->second >= value) {
                return;
            }
        }

        int l = value, r = value;

        // check right side
        auto above = left_to_right.upper_bound(value);
        if (above != left_to_right.end() && above->first == value+1) {
            r = above->second;
            left_to_right.erase(above);
        }

        // check left side
        auto below = left_to_right.lower_bound(value);
        if (below != left_to_right.begin()) {
            --below;
            if (below->second == value-1) {
                l = below->first;
                left_to_right.erase(below);
            }
        }

        left_to_right[l] = r;
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> result;
        for (const auto &pair : left_to_right) {
            result.push_back(vector<int>({pair.first, pair.second}));
        }
        return result;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
