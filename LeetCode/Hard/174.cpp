class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        /*
        generalizable ideas for the future:
        - the reason why the dp[i][j] values are filled in backward is this: the way
        we use dp[i][j] is for it to represent the minimum health AT THE CELL (i, j)
        to get from (i, j) to (r-1, c-1). if we did it as a standard DP from top left
        to bottom right, then we would be saying that dp[i][j] is the minimum health
        needed AT THE CELL (0, 0) for the path's sum to never become negative across
        all paths from (0, 0) to (i, j). the former is used here, and is more intuitive,
        because dp[i][j] talks about the health needed AT THE CURRENT CELL. the core idea
        is that if the 2 possible next cells (for a given cell (i, j)) require k amount
        of health at those cells to survive to the end, then we can calculate the minimum
        amount of health needed at cell (i, j) by noting that the dungeon[i][j] value would
        contribute to the health values found at those next cells (so then we would subtract
        it, because we're going back in time, and take the max of that and 1 because the
        health should never be non-positive, whether before or after a cell).
        - although i did it in a different way for the CTC OA problem ("bank_transfers"),
        where i went from left to right over the array, this approach of going backward
        (because we can represent dp[i] as the minimum initial amount needed at index i
        to get from i to n-1) would also work on that problem as well.
        */

        int r = dungeon.size(), c = dungeon[0].size();
        vector<vector<int>> dp(r, vector<int>(c, 1e9));
        dp[r-1][c-1] = max(1, 1 - dungeon[r-1][c-1]);
        for (int i = r - 1; i >= 0; --i) {
            for (int j = c - 1; j >= 0; --j) {
                if (i < r - 1) {
                    dp[i][j] = min(dp[i][j], max(1, dp[i+1][j] - dungeon[i][j]));
                }
                if (j < c - 1) {
                    dp[i][j] = min(dp[i][j], max(1, dp[i][j+1] - dungeon[i][j]));
                }
            }
        }
        return dp[0][0];
    }
};
