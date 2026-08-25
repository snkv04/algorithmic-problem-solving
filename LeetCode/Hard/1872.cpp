#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<int> pre(n, 0);
        for (int i = 0; i < n; ++i) {
            pre[i] = stones[i] + (i == 0 ? 0 : pre[i - 1]);
        }

        vector<int> alice_best(n, 0), bob_best(n, 0);
        alice_best[n - 1] = pre[n - 1];
        bob_best[n - 1] = -pre[n - 1];
        for (int i = n - 2; i >= 1; --i) {
            alice_best[i] = max(
                alice_best[i + 1],
                pre[i] + bob_best[i + 1]
            );
            bob_best[i] = min(
                bob_best[i + 1],
                -pre[i] + alice_best[i + 1]
            );
        }
        return alice_best[1];
    }
};
