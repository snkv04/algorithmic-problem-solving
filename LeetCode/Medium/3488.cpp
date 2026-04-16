class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        unordered_map<int, set<int>> indices;
        for (int i = 0; i < n; ++i) {
            indices[nums[i]].insert(i);
        }

        int q = queries.size();
        vector<int> ans(q);
        for (int i = 0; i < q; ++i) {
            int qidx = queries[i];
            int val = nums[qidx];
            if (indices[val].size() == 1) {
                ans[i] = -1;
            } else {
                int left;
                auto it = indices[val].lower_bound(qidx);
                if (it != indices[val].begin()) {
                    --it;
                    left = qidx - *it;
                } else {
                    left = qidx + n - *indices[val].rbegin();
                }

                int right;
                it = indices[val].upper_bound(qidx);
                if (it != indices[val].end()) {
                    right = *it - qidx;
                } else {
                    right = n - qidx + *indices[val].begin();
                }

                ans[i] = min(left, right);
            }
        }
        return ans;
    }
};
