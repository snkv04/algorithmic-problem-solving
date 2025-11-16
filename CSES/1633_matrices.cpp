#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int DIM = 7;
constexpr int MOD = 1e9 + 7;
const vector<vector<ll>> shift_down = {
    {0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0},
};
const vector<vector<ll>> next_state = {
    {0, 1, 1, 1, 1, 1, 1},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 1},
};
const vector<vector<ll>> identity = {
    {1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 1},
};

vector<vector<ll>> matmul(const vector<vector<ll>> &a, const vector<vector<ll>> &b) {
    vector<vector<ll>> c(DIM, vector<ll>(DIM, 0));
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            for (int k = 0; k < DIM; ++k) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

vector<vector<ll>> matsquare(const vector<vector<ll>> &a) {
    return matmul(a, a);
}

vector<vector<ll>> fastexp(const vector<vector<ll>> &m, int exp) {
    if (exp == 0) return identity;

    if (exp % 2) {
        return matmul(m, fastexp(m, exp - 1));
    } else {
        vector<vector<ll>> res = fastexp(m, exp / 2);
        return matsquare(res);
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<ll>> dp(7, vector<ll>(1, 0));
    dp[0][0] = 1;
    auto transition = matmul(next_state, shift_down);
    auto full_transition = fastexp(transition, n);
    dp = matmul(full_transition, dp);
    cout << dp[0][0] << '\n';

    return 0;
}
