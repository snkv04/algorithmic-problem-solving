class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> mem(
            n,
            vector<vector<int>>(
                k,
                vector<int>(2, 0)
            )
        );

        /*
                        1        2
        [3, 2, 6, 5, 1, 8, 7, 2, 0, 3]
        */

        // let mem[i][j][k] represent the maximum accumulated delta (from 0
        // dollars initially) that we can get from only considering the first
        // i+1 prices, having completed j-1 transactions + a buy (if k = 0)
        // and having completed j transactions (if k = 1).
        // in order to save ourselves from looking at all possible choices of
        // the end of the last transaction, and for each, getting the min across
        // the current segment (for the buy point), we break it up into two
        // tables (or 1 table with the last dimension having length 2). each one
        // looks at if the state involves currently selling (as well as
        // possibly selling on a previous index) or currently buying (as well
        // as possibly buying on a previous index).
        for (int i = 0; i < n; ++i) {
            if (i == 0) mem[i][0][0] = -1 * prices[0];
            else mem[i][0][0] = max(mem[i-1][0][0], -1 * prices[i]);
        }
        for (int i = 1; i < n; ++i) {
            if (i == 1) mem[i][0][1] = mem[i-1][0][0] + prices[i];
            else mem[i][0][1] = max(mem[i-1][0][1], mem[i-1][0][0] + prices[i]);
        }

        for (int j = 1; j < k; ++j) {
            for (int i = 2*j; i < n; ++i) {
                if (i == 2*j) {
                    mem[i][j][0] = mem[i-1][j-1][1] - prices[i];
                } else {
                    mem[i][j][0] = max(mem[i-1][j][0], mem[i-1][j-1][1] - prices[i]);
                }
            }

            for (int i = 2*j+1; i < n; ++i) {
                if (i == 2*j+1) {
                    mem[i][j][1] = mem[i-1][j][0] + prices[i];
                } else {
                    mem[i][j][1] = max(
                        mem[i-1][j][1],
                        mem[i-1][j][0] + prices[i]
                    );
                }
            }
        }
        
        int ans = 0;
        while (k--) {
            ans = max(ans, mem[n-1][k][1]);
        }
        return ans;
    }
};
