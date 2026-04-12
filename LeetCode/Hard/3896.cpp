class Solution {
public:
    int minOperations(vector<int>& nums) {
        int max_prime = 1e5 + 3;
        vector<bool> is_prime(max_prime + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= max_prime; ++i) {
            for (int j = 2 * i; j <= max_prime; j += i) {
                is_prime[j] = false;
            }
        }

        vector<int> next_prime(max_prime + 1, 0);
        int next = max_prime;
        for (int i = max_prime; i >= 1; --i) {
            if (is_prime[i]) next = i;
            next_prime[i] = next - i;
        }

        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i % 2 == 0) {
                ans += next_prime[nums[i]];
            } else if (is_prime[nums[i]]) {
                if (nums[i] == 2) {
                    ans += 2;
                } else {
                    ans += 1;
                }
            }
        }
        return ans;
    }
};
