class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int ans = 0;
        for (int i = 0; i < min(nums1.size(), nums2.size()); ++i) {
            int l = i, r = nums2.size() - 1, j = i;
            while (l <= r) {
                int m = (l + r) / 2;
                if (nums2[m] >= nums1[i]) {
                    j = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            ans = max(ans, j - i);
        }
        return ans;
    }
};
