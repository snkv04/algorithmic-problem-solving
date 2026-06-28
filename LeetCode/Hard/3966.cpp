#include <bits/stdc++.h>
using namespace std;

long long mem[17][2][10][2];

class Solution {
    vector<int> digits;
    int k;

    long long dfs(
        int idx,
        bool started,
        int dig,
        bool tight
    ) {
        if (idx == 0) return 1;
        if (mem[idx][started][dig][tight] != -1) return mem[idx][started][dig][tight];

        long long result = 0;
        int mn = -1, mx = -1;
        if (started) {
            mn = max(0, dig - k);
            if (tight) {
                mx = min(dig + k, digits[idx - 1]);
            } else {
                mx = min(dig + k, 9);
            }
        } else {
            mn = 0;
            if (tight) {
                mx = digits[idx - 1];
            } else {
                mx = 9;
            }
        }

        for (int d = mn; d <= mx; ++d) {
            result += dfs(
                idx - 1,
                started || d,
                d,
                tight && d == digits[idx - 1]
            );
        }

        return mem[idx][started][dig][tight] = result;
    }

    long long solve(long long num) {
        for (int i = 0; i <= 16; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 10; ++k) {
                    fill(mem[i][j][k], mem[i][j][k] + 2, -1);
                }
            }
        }

        digits.clear();
        long long copy = num;
        for (int i = 0; i < 16; ++i) {
            digits.push_back(copy % 10);
            copy /= 10;
        }

        long long ans = dfs(16, 0, 0, 1);
        return ans;
    }

public:
    long long goodIntegers(long long l, long long r, int k) {
        this->k = k;
        return solve(r) - (l == 0 ? 0 : solve(l - 1));
    }
};
