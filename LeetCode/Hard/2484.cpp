class Solution {
public:
    int countPalindromes(string s) {
        int n = s.size();
        if (n <= 4) return 0;

        vector<vector<int>> pref(n, vector<int>(10)), suf(n, vector<int>(10));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= 9; ++j) {
                pref[i][j] = static_cast<int>(s[i] - '0') == j;
                if (i) pref[i][j] += pref[i-1][j];
            }
        }
        for (int i = n-1; i >= 0; --i) {
            for (int j = 0; j <= 9; ++j) {
                suf[i][j] = static_cast<int>(s[i] - '0') == j;
                if (i < n-1) suf[i][j] += suf[i+1][j];
            }
        }

        vector<vector<int>> mempref(n, vector<int>(100)),
            memsuf(n, vector<int>(100));
        constexpr int MOD = 1e9 + 7;
        for (int j = 0; j <= 99; ++j) {
            int tens = j / 10, ones = j % 10;
            for (int i = 1; i < n; ++i) {
                mempref[i][j] = mempref[i-1][j];
                if (static_cast<int>(s[i] - '0') == ones) {
                    mempref[i][j] += pref[i-1][tens];
                }
                mempref[i][j] %= MOD;
            }
            for (int i = n-2; i >= 0; --i) {
                memsuf[i][j] = memsuf[i+1][j];
                if (static_cast<int>(s[i] - '0') == ones) {
                    memsuf[i][j] += suf[i+1][tens];
                }
                memsuf[i][j] %= MOD;
            }
        }

        long long ans = 0;
        for (int i = 2; i <= n-3; ++i) {
            for (int j = 0; j <= 99; ++j) {
                long long ways = static_cast<long long>(mempref[i-1][j]) *
                    memsuf[i+1][j];
                ans += ways;
                ans %= MOD;
            }
        }
        return ans;
    }
};
