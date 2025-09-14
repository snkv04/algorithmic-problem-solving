class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        /*
        - map all positions into left-right pairs
        - coordinate compression
        - go through each operation, and brute-force it
        */
        set<int> distinct;
        for (vector<int> &position : positions) {
            position[1] = position[0] + position[1] - 1;
            distinct.insert(position[0]);
            distinct.insert(position[1]);
        }

        map<int, int> to_compressed;
        int idx = 0;
        for (int distinct_val : distinct) {
            to_compressed[distinct_val] = idx++;
        }

        int len = distinct.size();
        vector<int> height(len, 0);
        vector<int> ans;
        for (vector<int> &operation : positions) {
            int l = to_compressed[operation[0]], r = to_compressed[operation[1]];
            int h = operation[1] - operation[0] + 1;

            int mx = 0;
            for (int i = l; i <= r; ++i) mx = max(height[i], mx);

            mx += h;
            ans.push_back(max(mx, ans.size() ? ans[ans.size()-1] : (int) -1e9));
            for (int i = l; i <= r; ++i) height[i] = mx;
        }
        return ans;
    }
};
