#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfArrays(string s, int k) {
        int n = s.size();
        int copy = k, digits = 0;
        while (copy) {
            copy /= 10;
            digits += 1;
        }

        vector<long long> mem(n + 1, 0);
        mem[n] = 1;
        constexpr int MOD = 1e9 + 7;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == '0') continue;

            for (int j = 1; j <= digits && i + j <= n; ++j) {
                string substr = s.substr(i, j);
                long long num = stoll(substr);
                if (num >= 1 && num <= k) {
                    mem[i] += mem[i + j];
                    mem[i] %= MOD;
                }
            }
        }
        return mem[0];
    }
};
