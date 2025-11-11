class Solution {
    void dfs(
        int i,
        int j,
        int r,
        int c,
        int maxval,
        vector<vector<int>> &grid,
        vector<vector<bool>> &visited
    ) {
        if (i < 0 || i >= r || j < 0 || j >= c) return;
        if (visited[i][j]) return;
        if (grid[i][j] > maxval) return;

        visited[i][j] = true;
        dfs(i, j+1, r, c, maxval, grid, visited);
        dfs(i, j-1, r, c, maxval, grid, visited);
        dfs(i+1, j, r, c, maxval, grid, visited);
        dfs(i-1, j, r, c, maxval, grid, visited);
    }

    bool check(int maxval, vector<vector<int>> &grid) {
        int r = grid.size(), c = grid[0].size();
        vector<vector<bool>> visited(r, vector<bool>(c, false));
        dfs(0, 0, r, c, maxval, grid, visited);
        return visited[r-1][c-1];
    }

public:
    int swimInWater(vector<vector<int>>& grid) {
        int l = 0, r = 2500, ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (check(m, grid)) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    }
};
