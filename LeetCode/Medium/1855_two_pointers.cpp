class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int ans = 0, j = 0;
        for (int i = 0; i < min(nums1.size(), nums2.size()); ++i) {
            j = max(i, j);
            while (j + 1 < nums2.size() && nums2[j + 1] >= nums1[i]) {
                ++j;
            }
            ans = max(ans, j - i);
        }
        return ans;
    }
};
