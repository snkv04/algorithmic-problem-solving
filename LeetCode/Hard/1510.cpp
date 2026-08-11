#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<int> nimber(n + 1, 0);
        vector<bool> reachable(n + 1, false);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                reachable[nimber[i - j * j]] = true;
            }

            int mex = 0;
            while (reachable[mex]) ++mex;
            nimber[i] = mex;

            for (int j = 1; j * j <= i; ++j) {
                reachable[nimber[i - j * j]] = false;
            }
        }
        return nimber[n];
    }
};
