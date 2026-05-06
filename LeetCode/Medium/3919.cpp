class Solution {
public:
    vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> right(n, 2e9), left(n, 2e9);
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                right[i] = 1;
            } else if (i == n - 1) {
                left[i] = 1;
            } else {
                if (nums[i] - nums[i - 1] <= nums[i + 1] - nums[i]) {
                    left[i] = 1;
                } else {
                    right[i] = 1;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (i < n - 1) {
                right[i] = min(right[i], nums[i + 1] - nums[i]);
            }
            if (i > 0) {
                left[i] = min(left[i], nums[i] - nums[i - 1]);
            }
        }

        vector<long long> pref_left(n, 0), pref_right(n, 0);
        pref_left[0] = left[0];
        pref_right[0] = right[0];
        for (int i = 1; i < n; ++i) {
            pref_left[i] = pref_left[i - 1] + left[i];
            pref_right[i] = pref_right[i - 1] + right[i];
        }
        auto get_sum = [](int l, int r, vector<long long> &a) {
            long long result = a[r];
            if (l != 0) result -= a[l - 1];
            return result;
        };

        vector<int> ans;
        for (int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0], r = queries[i][1];
            if (l == r) {
                ans.push_back(0);
            } else if (l < r) {
                ans.push_back(get_sum(l, r - 1, pref_right));
            } else {
                ans.push_back(get_sum(r + 1, l, pref_left));
            }
        }
        return ans;
    }
};
