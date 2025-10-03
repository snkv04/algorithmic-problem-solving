class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int r = matrix.size(), c = matrix[0].size();
        vector<vector<int>> to_left(r+1, vector<int>(c+1, 0)),
                            to_up(r+1, vector<int>(c+1, 0));
        for (int i = 1; i <= r; ++i) {
            for (int j = 1; j <= c; ++j) {
                if (matrix[i-1][j-1] == '1') {
                    to_left[i][j] = to_left[i][j-1] + 1;
                    to_up[i][j] = to_up[i-1][j] + 1;
                }
            }
        }

        int ans = 0;
        vector<vector<int>> mem(r+1, vector<int>(c+1, 0));
        for (int i = 1; i <= r; ++i) {
            for (int j = 1; j <= c; ++j) {
                if (matrix[i-1][j-1] == '1') {
                    mem[i][j] = min(
                        mem[i-1][j-1] + 1,
                        min(
                            to_left[i][j],
                            to_up[i][j]
                        )
                    );
                    ans = max(ans, mem[i][j] * mem[i][j]);
                }
            }
        }
        return ans;
    }
};
