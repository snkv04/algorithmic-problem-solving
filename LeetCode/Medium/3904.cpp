#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre(n), suf(n);
        for (int i = 0; i < n; ++i) {
            pre[i] = max(i ? pre[i - 1] : static_cast<int>(-1e9), nums[i]);
        }
        for (int i = n - 1; i >= 0; --i) {
            suf[i] = min(i < n - 1 ? suf[i + 1] : static_cast<int>(1e9), nums[i]);
        }

        for (int i = 0; i < n; ++i) {
            int instability = pre[i] - suf[i];
            if (instability <= k) {
                return i;
            }
        }
        return -1;
    }
};
