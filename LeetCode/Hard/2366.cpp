class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        long long ans = 0, n = nums.size(), bound = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] > bound) {
                int ops = (nums[i] + bound - 1) / bound - 1;
                ans += ops;
                int spots = ops + 1;
                bound = nums[i] / spots;  // floor division
            } else {
                bound = nums[i];
            }
        }
        return ans;
    }
};
