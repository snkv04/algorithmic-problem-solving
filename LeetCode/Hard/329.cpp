class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int r = matrix.size(), c = matrix[0].size();
        vector<pair<int, int>> cells;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cells.push_back(make_pair(i, j));
            }
        }
        sort(
            cells.begin(),
            cells.end(),
            [&](const pair<int, int> &a, const pair<int, int> &b) {
                return matrix[a.first][a.second] < matrix[b.first][b.second];
            }
        );

        int ans = 0;
        vector<vector<int>> mem(r, vector<int>(c, 1));
        vector<pair<int, int>> dirs = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
        };
        for (auto [i, j] : cells) {
            for (auto [di, dj] : dirs) {
                int newi = i + di, newj = j + dj;
                if (
                    newi >= 0 &&
                    newi < r &&
                    newj >= 0 &&
                    newj < c &&
                    matrix[i][j] > matrix[newi][newj]
                ) {
                    mem[i][j] = max(
                        mem[i][j],
                        1 + mem[newi][newj]
                    );
                }
            }
            ans = max(ans, mem[i][j]);
        }
        return ans;
    }
};
