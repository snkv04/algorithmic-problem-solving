#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        stoneValue.push_back(0);

        vector<int> suf_sum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suf_sum[i] = suf_sum[i + 1] + stoneValue[i];
        }

        vector<vector<int>> mem(n + 1, vector<int>(2, -1e9));
        mem[n][0] = mem[n][1] = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 1; j <= min(3, n - i); ++j) {
                mem[i][0] = max(mem[i][0], suf_sum[i] - suf_sum[i + j] + mem[i + j][1]);
            }

            int bob_best = -1e9;
            for (int j = 1; j <= min(3, n - i); ++j) {
                bob_best = max(bob_best, suf_sum[i] - mem[i + j][0]);
            }
            mem[i][1] = suf_sum[i] - bob_best;
        }

        int alice = mem[0][0], bob = suf_sum[0] - alice;
        if (alice > bob) {
            return "Alice";
        } else if (alice < bob) {
            return "Bob";
        } else {
            return "Tie";
        }
    }
};
