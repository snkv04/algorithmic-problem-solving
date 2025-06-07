class Solution {
    public int maxSubArray(int[] nums) {
        int[] maxEndingHere = new int[nums.length];
        maxEndingHere[0] = nums[0];
        int max = nums[0];
        for (int i = 1; i <= nums.length-1; i++) {
            maxEndingHere[i] = Math.max(nums[i] + maxEndingHere[i-1], nums[i]);
            max = Math.max(max, maxEndingHere[i]);
        }
        return max;
    }
}