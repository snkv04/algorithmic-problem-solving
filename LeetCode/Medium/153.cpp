class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if (nums[n-1] >= nums[0]) return nums[0];

        int l = 0, r = n-1, ans = -1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] < nums[0]) {
                ans = nums[m];
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }
};
