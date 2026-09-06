#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        if (s.size() < t.size()) return 0;

        constexpr long long MOD = 1LL << 31;
        vector<long long> mem(s.size() + 1, 1);
        for (int i = 0; i < t.size(); ++i) {
            vector<long long> new_mem(s.size() + 1, 0);
            for (int j = i + 1; j <= s.size(); ++j) {
                new_mem[j] = new_mem[j - 1];
                if (s[j - 1] == t[i]) {
                    new_mem[j] += mem[j - 1];
                    new_mem[j] %= MOD;
                }
            }
            mem = std::move(new_mem);
        }
        return mem[s.size()];
    }
};
