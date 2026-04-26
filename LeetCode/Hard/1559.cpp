vector<pair<int, int>> delta = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

class Solution {
    bool dfs(
        int i, int j,
        int previ, int prevj,
        vector<vector<char>> &grid,
        vector<vector<bool>> &visited
    ) {
        auto p = make_pair(i, j);
        visited[i][j] = true;

        for (auto [di, dj] : delta) {
            int nexti = i + di, nextj = j + dj;
            if (
                nexti < 0 ||
                nexti >= grid.size() ||
                nextj < 0 ||
                nextj >= grid[0].size()
            ) {
                continue;
            }
            if (grid[nexti][nextj] != grid[i][j]) continue;
            if (nexti == previ && nextj == prevj) continue;

            if (
                visited[nexti][nextj] ||
                dfs(nexti, nextj, i, j, grid, visited)
            ) {
                return true;
            }
        }
        return false;
    }

public:
    bool containsCycle(vector<vector<char>>& grid) {
        int r = grid.size(), c = grid[0].size();
        vector<vector<bool>> visited(r, vector<bool>(c, false));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (visited[i][j]) continue;

                // if we wanted to keep track of the whole cycle, a stack
                // would be helpful, but to just recognize if a cycle is
                // there or not, we only need to make sure we don't step
                // backward on the path we just came from
                if (dfs(i, j, -1, -1, grid, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
};
