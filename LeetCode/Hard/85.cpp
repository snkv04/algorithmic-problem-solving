class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int r = matrix.size(), c = matrix[0].size();
        vector<vector<int>> above(r, vector<int>(c, 0));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (matrix[i][j] == '1') {
                    if (i == 0) above[i][j] = 1;
                    else above[i][j] = above[i-1][j] + 1;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < r; ++i) {
            stack<pair<int, int>> stk;
            for (int j = 0; j <= c; ++j) {
                int height = j == c ? -1 : above[i][j];
                int index = j;
                while (stk.size() && stk.top().second >= height) {
                    index = stk.top().first;
                    ans = max(ans, stk.top().second * (j - stk.top().first));
                    stk.pop();
                }
                stk.push(make_pair(index, height));
            }
        }
        return ans;
    }
};
