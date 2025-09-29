class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> prev(k + 1, vector<int>(2, 0));
        for (int i = 1; i <= n; ++i) {
            int price = prices[i-1];
            vector<vector<int>> curr(k+1, vector<int>(2, 0));
            for (int j = 1; j <= k; ++j) {
                if (i >= 2 * j - 1) {
                    // compute DP for buying
                    if (i == 2 * j - 1) {
                        curr[j][0] = prev[j-1][1] - price;
                    } else {
                        curr[j][0] = max(
                            prev[j][0],
                            prev[j-1][1] - price
                        );
                    }
                }

                if (i >= 2 * j) {
                    // compute DP for selling
                    if (i == 2 * j) {
                        curr[j][1] = prev[j][0] + price;
                    } else {
                        curr[j][1] = max(
                            prev[j][1],
                            prev[j][0] + price
                        );
                    }
                }
            }
            prev = std::move(curr);
        }

        int ans = -1e9;
        for (int i = 0; i <= k; ++i) {  // all numbers of transactions
            ans = max(ans, prev[i][1]);
        }
        return ans;
    }
};
