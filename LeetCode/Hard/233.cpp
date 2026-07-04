#include <bits/stdc++.h>
using namespace std;

class Solution {
    int mem[11][2][10];
    vector<int> digits;

    int dfs(int idx, bool tight, int num_ones) {
        if (idx == 0) return num_ones;
        int &result = mem[idx][tight][num_ones];
        if (result != -1) return result;

        result = 0;
        for (int i = 0; i <= (tight ? digits[idx - 1] : 9); ++i) {
            result += dfs(
                idx - 1,
                tight && i == digits[idx - 1],
                num_ones + (i == 1)
            );
        }
        return result;
    }

public:
    int countDigitOne(int n) {
        for (int i = 0; i < 10; ++i) {
            digits.push_back(n % 10);
            n /= 10;
        }

        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < 2; ++j) {
                fill(mem[i][j], mem[i][j] + 10, -1);
            }
        }

        return dfs(10, true, 0);
    }
};
