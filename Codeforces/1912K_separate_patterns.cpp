#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

void solve() {
    /*
    - problem:
        - given an array, find the number of subsequences such that in the subsequence, every 3 consecutive
        numbers adds up to an even number
    - solution:
        - separately count the subsequences with shape [even, even, even] and [odd, even, odd]
        - for the second case, use DP, where we look at the 3 possible patterns separately, and all subsequences
        with length >= 3 are collapsed into 3 cases which loop cyclically
    - details:
        - full solution idea:
            - we can break up the "every 3 consecutive numbers" condition into 2 cases: all numbers are already
            even, or the numbers follow the infinite pattern [0, 1, 1, 0, 1, 1, 0, 1, 1, etc.] mod 2
            - for the first case, we can find all even numbers, find all possible subsets, and subtract the
            subsets of size 0, 1, and 2
            - everything below is focused on the second case:
                - we can break the subsequences into 3 exhaustive cases, based on the way they start
                - we can break each starting pattern's length into 2 cases: less than 3, and at least 3 (so the
                "at least 3" lengths will loop cyclically mod 3)
                    - the reason for doing this is to avoid having all possible lengths as part of the state,
                    which would be O(n^2)
                - after implementing that cyclic logic, the rest of the logic is pretty straightforward: for a
                given starting pattern j and end index in that pattern k, if the current element a[i] has the
                same parity as patterns[j][k], then we can assume the last number in the subsequence is that
                number a[i], and update the DP values accordingly.
    */

    // reads in input
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // counts fully even subsequences with combinatorics
    ll even = 0, ans = 0;
    for (int i = 0; i < n; ++i) even += a[i] % 2 == 0;
    if (even >= 3) {
        ans += mod_pow(2, even);
        ans -= (1 + even + even * (even - 1) / 2) % MOD;
        if (ans < 0) ans += MOD;
    }

    // counts odd, even, odd subsequences with DP
    vector<vector<int>> patterns = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
    };
    vector<vector<ll>> dp(3, vector<ll>(5, 0));
    for (int i = 0; i < n; ++i) {
        vector<vector<ll>> new_dp = dp;  // uses copy constructor
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 5; ++k) {
                if (a[i] % 2 == patterns[j][k] % 2) {
                    if (k == 0) {
                        new_dp[j][k] = (new_dp[j][k] + 1) % MOD;
                    } else if (k == 2) {
                        new_dp[j][k] = (new_dp[j][k] + dp[j][1] + dp[j][4]) % MOD;
                    } else {
                        new_dp[j][k] = (new_dp[j][k] + dp[j][k-1]) % MOD;
                    }
                }
            }
        }
        dp = std::move(new_dp);
    }
    for (int j = 0; j < 3; ++j) {
        for (int k = 2; k < 5; ++k) {
            ans = (ans + dp[j][k]) % MOD;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
