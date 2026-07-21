#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> is_palindrome(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            is_palindrome[i][i] = true;
            for (
                int j = 1;
                i - j >= 0 && i + j < n && s[i - j] == s[i + j];
                ++j
            ) {
                is_palindrome[i - j][i + j] = true;
            }

            if (i < n - 1) {
                for (
                    int j = 1;
                    i + 1 - j >= 0 && i + j < n && s[i + 1 - j] == s[i + j];
                    ++j
                ) {
                    is_palindrome[i + 1 - j][i + j] = true;
                }
            }
        }

        vector<int> mem(n + 1, 1e9);
        mem[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j >= 1; --j) {
                if (is_palindrome[j - 1][i - 1]) {
                    mem[i] = min(mem[i], 1 + mem[j - 1]);
                }
            }
        }
        return mem[n] - 1;
    }
};
