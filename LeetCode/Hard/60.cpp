#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> remaining;
        for (int i = 1; i <= n; ++i) {
            remaining.push_back(i);
        }

        vector<int> fac(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            fac[i] = fac[i - 1] * i;
        }

        stringstream ss;
        while (n) {
            for (int j = 1; j <= n; ++j) {
                if (fac[n - 1] * j >= k) {
                    ss << remaining[j - 1];
                    remaining.erase(remaining.begin() + j - 1);
                    k -= fac[n - 1] * (j - 1);
                    break;
                }
            }
            --n;
        }
        return ss.str();
    }
};
