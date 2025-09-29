class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> mem(
            // the 0 is there to allow looking at the "previous price"
            // without causing indexing errors
            n + 1,
            vector<vector<int>>(
                // the 0 is there to allow looking at the "previous transaction"
                // without causing indexing errors
                k + 1,
                vector<int>(2, 0)
            )
        );

        for (int i = 1; i <= n; ++i) {
            int price = prices[i-1];
            for (int j = 1; j <= k; ++j) {
                if (i >= 2 * j - 1) {
                    // compute DP for buying
                    if (i == 2 * j - 1) {
                        mem[i][j][0] = mem[i-1][j-1][1] - price;
                    } else {
                        mem[i][j][0] = max(
                            mem[i-1][j][0],
                            mem[i-1][j-1][1] - price
                        );
                    }
                }

                if (i >= 2 * j) {
                    // compute DP for selling
                    if (i == 2 * j) {
                        mem[i][j][1] = mem[i-1][j][0] + price;
                    } else {
                        mem[i][j][1] = max(
                            mem[i-1][j][1],
                            mem[i-1][j][0] + price
                        );
                    }
                }
            }
        }

        int ans = -1e9;
        for (int i = 0; i <= k; ++i) {  // all numbers of transactions
            ans = max(ans, mem[n][i][1]);
        }
        return ans;
    }
};
