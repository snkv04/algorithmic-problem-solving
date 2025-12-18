using ll = long long;

class Solution {
public:
    ll maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        ll mem[k+1][3][n+1];
        for (int i = 0; i <= k; ++i) for (int j = 0; j < 3; ++j) {
            fill(mem[i][j], mem[i][j]+n+1, -1e15);
        }
        for (int i = 0; i <= n; ++i) {
            mem[0][2][i] = 0;
        }

        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= n; ++j) {
                mem[i][0][j] = max(
                    mem[i][0][j-1],
                    mem[i-1][2][j-1] - prices[j-1]
                );
                mem[i][1][j] = max(
                    mem[i][1][j-1],
                    mem[i-1][2][j-1] + prices[j-1]
                );
                mem[i][2][j] = max({
                    mem[i][2][j-1],
                    mem[i][0][j-1] + prices[j-1],
                    mem[i][1][j-1] - prices[j-1]
                });
            }
        }
        // for (int i = 0; i <= k; ++i) {
        //     cout << "for " << i << " ops:\n";
        //     for (int j = 0; j <= n; ++j) {
        //         cout << "\tfor day " << j << ": ";
        //         cout << mem[i][0][j] << " " << mem[i][1][j] << " " << mem[i][2][j] << endl;
        //     }
        // }

        ll ans = 0;
        for (int i = 1; i <= k; ++i) {
            ans = max(ans, mem[i][2][n]);
            // for (int j = 1; j <= n; ++j) {
            //     ans = max(ans, mem[i][2][j]);
            // }
        }
        return ans;
    }
};
