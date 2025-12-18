class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> premin(n), sufmax(n);
        for (int i = 0; i < n; ++i) {
            if (i == 0) premin[i] = prices[i];
            else premin[i] = min(premin[i-1], prices[i]);
        }
        for (int i = n-1; i >= 0; --i) {
            if (i == n-1) sufmax[i] = prices[i];
            else sufmax[i] = max(sufmax[i+1], prices[i]);
        }

        vector<int> prebest(n, 0), sufbest(n, 0);
        for (int i = 1; i < n; ++i) {
            prebest[i] = max(prebest[i-1], prices[i] - premin[i-1]);
        }
        for (int i = n-2; i >= 0; --i) {
            sufbest[i] = max(sufbest[i+1], sufmax[i+1] - prices[i]);
        }

        int ans = 0;
        for (int i = -1; i < n; ++i) {
            int prefix = i == -1 ? 0 : prebest[i];
            int suffix = i == n-1 ? 0 : sufbest[i+1];
            ans = max(ans, prefix + suffix);
        }
        return ans;
    }
};
