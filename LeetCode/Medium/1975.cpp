class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long sum = 0;
        int n = matrix.size();
        int smallestabs = 1e9;
        int negativecount = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int val = matrix[i][j];
                sum += abs(val);
                if (val < 0) negativecount += 1;
                smallestabs = min(smallestabs, abs(val));
            }
        }

        if (negativecount % 2) sum -= 2 * smallestabs;
        return sum;
    }
};
