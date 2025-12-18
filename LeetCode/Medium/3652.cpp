class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        long long ans = 0;
        int n = prices.size();
        for (int i = 0; i < n; ++i) {
            ans += strategy[i] * prices[i];
        }

        long long curr = ans;
        for (int i = 0; i < k; ++i) {
            curr -= strategy[i] * prices[i];
            if (i >= k/2) {
                curr += prices[i];
            }
        }
        ans = max(ans, curr);

        for (int i = k; i < n; ++i) {
            curr -= strategy[i] * prices[i];
            curr += prices[i];
            curr -= prices[i-k/2];
            curr += strategy[i-k] * prices[i-k];
            ans = max(ans, curr);
        }
        return ans;
    }
};
