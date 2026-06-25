#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> pre(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + (nums[i - 1] == target ? 1 : -1);
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                if (pre[j] - pre[i - 1] > 0) {
                    ans += 1;
                }
            }
        }
        return ans;
    }
};
