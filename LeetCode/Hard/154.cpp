class Solution {
public:
    int findMin(vector<int>& nums) {
        /*
        basically: first remove the edge elements if they are equal (because
        that messes up the binary search), and then the inner part will be
        a rotated sorted array (with possibly duplicates) except the right
        and left elements are NOT equal. now, a simple binary search (or simple
        access of left element, if inner part is already sorted) will suffice
        */

        int n = nums.size();
        int left = 0, right = n-1; // bounds of array after removing edge elems
        int edge_elem = nums[0];
        if (nums[0] == nums[n-1]) {
            while (left < n && nums[left] == edge_elem) {
                ++left;
            }

            if (left == n) { // all elements are equal
                return edge_elem;
            }

            while (nums[right] == edge_elem) {
                --right;
            }
        }

        // if inner portion is sorted, just take min of edge elem and lowest
        // from sorted portion
        if (nums[left] <= nums[right]) {
            return min(edge_elem, nums[left]);
        }

        // otherwise, do binary search to find lowest from sorted portion
        int l = left, r = right, idx = -1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[m] < nums[left]) {
                idx = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return min(edge_elem, nums[idx]);
    }
};
