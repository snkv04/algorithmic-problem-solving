/*
observations:
- keep in mind that the dp table isn’t exactly indexed based on the grid of spaces. it is more accurate to say that it is indexed by the position of the entity that we’re tracking. namely, in many problems, dp[i][j] represents the max value we can get if the character in the problem has reached (i, j), not just “the max value reachable over the rows up to i and the cols up to j”. it’s just that generally, we’re getting the max value reachable if the entity has reached (i, j) through such rows and columns. so, if we take this concept and extend it, then we can keep track of the max value if robot1 is at (a, b) and robot2 is at (c, d). simply put: the indices of the dp table has a very specific meaning, and i should recognize what it is so that it can be easily modified (it’s the max value if the robot is at (i, j), so it can just be extended to be the max value if the robots are at two separate coordinate-pairs)
- if we have multiple robots like this, we can form an equation out of the coordinates and remove a dimension. how is this generalizable? when we have several terms, form an equation and see if any of them can be fully dependent on each ither. however, it must be noted that we need to perform a check on the inferred variable to make sure that the state that we're looking at is valid (e.g., if i1==n-1 and j1==m-1 and i2==0, then j2 would have to be too large if it had to compensate for the low value of i2, so this state is not valid)
    - keep in mind, though, that we can only do this because the robots have made the same number of steps.
    - the question now is, why are we keeping the robots at the same time step?well, consider what happens if we don't keep them at the same time step. then, if we want to ensure that each cherry is only taken once, then it might be the case that robot 1 took the cherry a few timesteps ago and robot 2 must not take it again, or maybe this order is swapped. to keep things simple, just assume that the robots are always at the same timestep, and then we can easily ensure that each cherry is only taken once by actually deliberately enforcing that if two robots are in the same square and there's a cherry, then it's only taken once.
    - the fact that we are allowed to do this is also a result of making sure that the two robots start from the same place and not opposite corners. if they start from the same place, then the only time that two robots could ever eat the same cherry is when they see it at the same time. this isn't true if they started at opposite locations. this is true in Cherry Pickup II as well, by the way, since the two robots are ALWAYS at the same horizontal level if we ensure that they're always at the same timestep. by the way, what does it mean to say that they're at the same timestep? the number of movement operations they've done is equivalent.

solution:
- first off, instead of treating it like we go down-right then come back up
by going up-left, just suppose that we go down-right twice, and after the
first time, then the path that we go is cleared of cherries.
- we can also enforce it to be the case that the two robots (which are what we
are naming the separate entities that are taking the two paths) are always
at the same timestep, so we can entirely disregard states where they haven't
taken the same number of steps away from the starting point.
- also, we want to determine if all cells are even reachable or if there's no
way to get to them (like if a down-right diagonal line blocks us from getting
to the bottom right corner but there are a bunch of cherries in that bottom
right corner, then those cherries shouldn't actually matter). so, we can
replace all unreachable cells in the grid with thorns at the beginning. note
that if we were to do a recursive solution, then we would never be able to
cross such a barrier, but we do cross it since we are doing this DP
iteratively. that's why we enforce this restriction.
- now, we just do the traditional DP solution for a single robot and single
path, except that if the two robots are in the same cell and they're both on
a cherry, then it's only taken once.
*/

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<int>>> dp(
            n,
            vector<vector<int>>(
                m,
                vector<int>(n, 0)
            )
        );

        // determine all reachable squares
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 && j == 0) continue;

                bool reachable_from_left = j != 0 && grid[i][j-1] != -1;
                bool reachable_from_up = i != 0 && grid[i-1][j] != -1;
                if (!(reachable_from_left || reachable_from_up)) {
                    grid[i][j] = -1;
                }
            }
        }

        for (int i1 = 0; i1 < n; ++i1) {
            for (int j1 = 0; j1 < m; ++j1) {
                for (int i2 = 0; i2 < n; ++i2) {
                    int j2 = i1 + j1 - i2; // inferred from the other values
                    if (j2 < 0 || j2 >= m) continue;
                    if (grid[i1][j1] == -1) continue;
                    if (grid[i2][j2] == -1) continue;

                    int gaining = 0;
                    if (i1 == i2) { // automatically, j1 == j2
                        gaining = grid[i1][j1];
                    } else {
                        gaining = grid[i1][j1] + grid[i2][j2];
                    }

                    if (i1 > 0 && i2 > 0) {
                        // coming from above on both robots
                        dp[i1][j1][i2] = max(
                            dp[i1][j1][i2],
                            dp[i1-1][j1][i2-1]
                        );
                    }
                    if (i1 > 0 && j2 > 0) {
                        // from above on first robot, from left on second
                        dp[i1][j1][i2] = max(
                            dp[i1][j1][i2],
                            dp[i1-1][j1][i2]
                        );
                    }
                    if (j1 > 0 && i2 > 0) {
                        // from left on first, from above on second
                        dp[i1][j1][i2] = max(
                            dp[i1][j1][i2],
                            dp[i1][j1-1][i2-1]
                        );
                    }
                    if (j1 > 0 && j2 > 0) {
                        // from left on both
                        dp[i1][j1][i2] = max(
                            dp[i1][j1][i2],
                            dp[i1][j1-1][i2]
                        );
                    }
                    dp[i1][j1][i2] += gaining;
                }
            }
        }
        return dp[n-1][m-1][n-1];
    }
};
