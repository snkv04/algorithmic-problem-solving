constexpr int MOD = 1e9 + 7;

class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        unordered_map<int, vector<int>> indices;
        for (int i = 0; i < nums.size(); ++i) {
            indices[nums[i]].push_back(i);
        }

        long long ans = 0, zero_count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                ++zero_count;
                continue;
            }

            int double_num = 2 * nums[i];
            if (indices.find(double_num) != indices.end()) {
                int l = 0, r = indices[double_num].size() - 1, idx = -1;
                while (l <= r) {
                    int m = (l + r) / 2;
                    if (indices[double_num][m] >= i) {
                        idx = m;
                        r = m - 1;
                    } else {
                        l = m + 1;
                    }
                }

                if (idx != 0 && idx != -1) {
                    long long left = idx, right = indices[double_num].size() - idx;
                    ans += left * right;
                    ans %= MOD;
                }
            }
        }
        ans = (ans + (zero_count * (zero_count - 1) * (zero_count - 2) / 6)) % MOD;
        return static_cast<int>(ans);
    }
};
