#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> pref(n, 0);
        for (int i = 0; i < n; ++i) {
            pref[i] = stoneValue[i] + (i ? pref[i - 1] : 0);
        }

        vector<vector<long long>> mem(n, vector<long long>(n, 0));
        auto range_sum = [&](int l, int r) { return pref[r] - (l ? pref[l - 1] : 0); };
        for (int len = 2; len <= n; ++len) {
            for (int l = 0; l + len <= n; ++l) {
                int r = l + len - 1;
                long long total = range_sum(l, r);
                for (int m = l; m < r; ++m) {
                    long long left = range_sum(l, m);
                    long long right = total - left;
                    long long val = left == right
                        ? (left + max(mem[l][m], mem[m + 1][r]))
                        : (
                            left < right
                            ? (left + mem[l][m])
                            : (right + mem[m + 1][r])
                        );
                    mem[l][r] = max(mem[l][r], val);
                }
            }
        }
        return mem[0][n - 1];
    }
};
