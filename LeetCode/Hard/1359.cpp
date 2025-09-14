using ll = long long;

const ll MOD = 1e9 + 7;

ll pow(ll base, ll exp) {
    if (exp == 0) return 1;

    ll result = pow(base, exp / 2);
    result = (result * result) % MOD;
    if (exp % 2) result = (result * base) % MOD;
    return result;
}

ll modInv(ll num) {
    return pow(num, MOD - 2);
}

ll divide(ll num, ll denom) {
    return (num * modInv(denom)) % MOD;
}

class Solution {
public:
    int countOrders(int n) {
        ll numerator = 1;
        for (int i = 2; i <= 2 * n; ++i) {
            numerator = (numerator * i) % MOD;
        }

        ll denominator = 1;
        for (int i = 1; i <= n; ++i) {
            denominator = (2 * denominator) % MOD;
        }

        return (int) divide(numerator, denominator);
    }
};
