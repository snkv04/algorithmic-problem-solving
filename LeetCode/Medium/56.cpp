#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(
            intervals.begin(),
            intervals.end(),
            [](const vector<int> &a, const vector<int> &b) {
                return a[0] < b[0];
            }
        );

        vector<vector<int>> result = {intervals[0]};
        for (int i = 1; i < intervals.size(); ++i) {
            int l = intervals[i][0], r = intervals[i][1];
            if (l > result.back()[1]) {
                result.push_back({l, r});
            } else {
                result.back()[1] = max(result.back()[1], r);
            }
        }
        return result;
    }
};
