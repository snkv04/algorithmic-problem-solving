class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, pair<int, int>> intervals;
        for (int i = 0; i < n; ++i) {
            if (intervals.find(nums[i]) == intervals.end()) {
                intervals[nums[i]] = make_pair(i, i);
            } else {
                intervals[nums[i]].second = i;
            }
        }

        map<int, int> ordered_intervals;
        for (const pair<int, pair<int, int>> &entry : intervals) {
            pair<int, int> interval = entry.second;
            ordered_intervals[interval.first] = interval.second;
        }

        vector<pair<int, int>> joined;
        for (const pair<int, int> &interval : ordered_intervals) {
            if (
                joined.size() &&
                joined.back().second > interval.first
            ) {
                joined.back().second = max(
                    joined.back().second, interval.second
                );
            } else {
                joined.push_back(interval);
            }
        }

        int ans = 1;
        for (int i = 0; i < joined.size() - 1; ++i) {
            ans *= 2;
            ans %= static_cast<int>(1e9 + 7);
        }
        return ans;
    }
};
