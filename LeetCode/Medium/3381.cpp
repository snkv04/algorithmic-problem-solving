class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        vector<long long> mn(k, 1e15);
        long long pref = 0, ans = -1e15;
        mn[0] = 0;
        for (int i = 1; i <= nums.size(); ++i) {
            pref += nums[i-1];
            ans = max(ans, pref - mn[i%k]);
            mn[i%k] = min(mn[i%k], pref);
        }
        return ans;
    }
};
