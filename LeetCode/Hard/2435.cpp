constexpr int MOD = 1e9 + 7;

class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int r = grid.size(), c = grid[0].size();
        vector<vector<vector<long long>>> mem(
            r, vector<vector<long long>>(
                c, vector<long long>(k, 0)
            )
        );

        mem[0][0][grid[0][0] % k] = 1;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int val = grid[i][j] % k;
                if (i) {
                    for (int m = 0; m < k; ++m) {
                        mem[i][j][m] = (mem[i][j][m] + mem[i-1][j][(m+k-val)%k]) % MOD;
                    }
                }
                if (j) {
                    for (int m = 0; m < k; ++m) {
                        mem[i][j][m] = (mem[i][j][m] + mem[i][j-1][(m+k-val)%k]) % MOD;
                    }
                }
            }
        }
        return mem[r-1][c-1][0];
    }
};
