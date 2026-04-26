class Solution {
public:
    vector<int> kthRemainingInteger(vector<int>& nums, vector<vector<int>>& queries) {
        vector<pair<int, int>> pos;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] % 2 == 0) {
                pos.push_back(make_pair(nums[i], i));
            }
        }

        vector<int> ans;
        for (int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0], r = queries[i][1], k = queries[i][2];
            if (pos.empty()) {
                ans.push_back(2 * k);
                continue;
            }

            int l_idx = -1, lo = 0, hi = pos.size() - 1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (pos[mid].second >= l) {
                    l_idx = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            int r_idx = -1; lo = 0; hi = pos.size() - 1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (pos[mid].second <= r) {
                    r_idx = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (
                l_idx == -1 ||
                r_idx == -1 ||
                r_idx < l_idx
            ) {
                ans.push_back(2 * k);
                continue;
            }

            int x = -1; lo = 1; hi = 1e9 + 1e6;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                int mid_val = mid * 2;

                int num_avail = mid;
                int num_del = 0;
                int lo2 = 0, hi2 = pos.size() - 1, idx = -1;
                while (lo2 <= hi2) {
                    int mid2 = (lo2 + hi2) / 2;
                    if (pos[mid2].first <= mid_val) {
                        idx = mid2;
                        lo2 = mid2 + 1;
                    } else {
                        hi2 = mid2 - 1;
                    }
                }
                if (idx >= l_idx) {
                    int length = min(idx, r_idx) - l_idx + 1;
                    num_del = length;
                }
                num_avail -= num_del;

                if (num_avail >= k) {
                    x = mid_val;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            ans.push_back(x);
        }
        return ans;
    }
};
