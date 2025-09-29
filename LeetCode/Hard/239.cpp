class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> result(n - k + 1, 0);
        deque<pair<int, int>> d;
        for (int i = 0; i < n; ++i) {
            if (i >= k && d.size() && d.front().second <= i - k) {
                d.pop_front();
            }

            while (d.size() && d.back().first <= nums[i]) {
                d.pop_back();
            }
            d.push_back(make_pair(nums[i], i));

            if (i >= k-1) {
                result[i-k+1] = d.front().first;
            }
        }
        return result;
    }
};
