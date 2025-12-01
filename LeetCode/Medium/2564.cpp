class Solution {
    int to_decimal(string s) {
        int result = 0, multiplier = 1;
        for (int i = s.size() - 1; i >= 0; --i) {
            result += multiplier * (s[i] - '0');
            multiplier *= 2;
        }
        return result;
    }

public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();
        unordered_map<int, pair<int, int>> leftmost;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= 30 && i+j<=n; ++j) {
                int num = to_decimal(s.substr(i, j));
                if (
                    leftmost.find(num) == leftmost.end() ||
                    leftmost[num].second - leftmost[num].first + 1 > j
                ) {
                    leftmost[num] = make_pair(i, i + j - 1);
                }
            }
        }

        vector<vector<int>> ans;
        for (auto q : queries) {
            int need = q[0] ^ q[1];
            if (leftmost.find(need) == leftmost.end()) {
                ans.push_back(vector<int>({-1, -1}));
            } else {
                ans.push_back(vector<int>({leftmost[need].first, leftmost[need].second}));
            }
        }
        return ans;
    }
};
