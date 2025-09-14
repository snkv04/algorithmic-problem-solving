class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        vector<vector<vector<int>>> dp(
            r,
            vector<vector<int>>(
                c,
                vector<int>(c, 0)
            )
        );
        
        dp[0][0][c-1] = grid[0][0] + grid[0][c-1];
        for (int i = 1; i < r; ++i) {
            for (int j1 = 0; j1 < c; ++j1) {
                for (int j2 = 0; j2 < c; ++j2) {
                    // determine if it's possible to go this far horizontally
                    if (j1 > i || (c-1-j2) > i) continue;

                    int gaining = (j1 == j2)
                        ? grid[i][j1]
                        : (grid[i][j1] + grid[i][j2]);
                    
                    // iterate through ways to get to this state
                    for (int dj1 = -1; dj1 <= 1; ++dj1) {
                        for (int dj2 = -1; dj2 <= 1; ++dj2) {
                            int oldj1 = j1 + dj1, oldj2 = j2 + dj2;
                            if (
                                oldj1 < 0 ||
                                oldj1 >= c ||
                                oldj2 < 0 ||
                                oldj2 >= c
                            ) {
                                continue;
                            }

                            dp[i][j1][j2] = max(
                                dp[i][j1][j2],
                                dp[i-1][oldj1][oldj2] + gaining
                            );
                        }
                    }
                }
            }
        }
        
        int best = 0;
        for (int j1 = 0; j1 < c; ++j1) {
            for (int j2 = 0; j2 < c; ++j2) {
                best = max(best, dp[r-1][j1][j2]);
            }
        }
        return best;
    }
};
