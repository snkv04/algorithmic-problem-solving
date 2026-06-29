#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 1) return 0;

        vector<bool> is_prime(n, true);
        is_prime[0] = is_prime[1] = false;
        for (int d = 2; d < n; ++d) {
            if (!is_prime[d]) continue;

            for (int m = 2 * d; m < n; m += d) {
                is_prime[m] = false;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) ans += is_prime[i];
        return ans;
    }
};
