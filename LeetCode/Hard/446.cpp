#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int len = nums.size();
        vector<array<map<long long, int>, 2>> mem(len);
        int ans = 0;
        for (int i = 1; i < len; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                long long diff = (long long) nums[i] - nums[j];
                mem[i][0][diff] += 1;
                if (mem[j][0].count(diff)) {
                    mem[i][1][diff] += mem[j][0][diff];
                }
                if (mem[j][1].count(diff)) {
                    mem[i][1][diff] += mem[j][1][diff];
                }
            }

            for (auto [k, v] : mem[i][1]) {
                ans += v;
            }
        }
        return ans;
    }
};
