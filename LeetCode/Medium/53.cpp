#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, mn = 0, ans = -1e9;
        for (int num : nums) {
            pre += num;
            ans = max(ans, pre - mn);
            mn = min(mn, pre);
        }
        return ans;
    }
};
