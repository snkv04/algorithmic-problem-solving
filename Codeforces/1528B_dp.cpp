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

ll modpow(ll b, ll e) {
    if (e == 0) return 1;

    if (e % 2) {
        ll res = modpow(b, e - 1);
        return (res * b) % MOD;
    } else {
        ll res = modpow(b, e / 2);
        return (res * res) % MOD;
    }
}

void solve() {
    /*
    - problem:
        - given the points {1, 2, ..., 2n}, find the number of ways to pair up the points so that for any
        two pairs (s_1, e_1), (s_2, e_2), at least one of the following two conditions is satisfied:
            - e_1 - s_1 == e_2 - s_2
            - s_i <= s_j and e_j <= e_i for some bijective assigment of (i, j) to {1, 2}
    - solution:
        - like in the other solution, we can break up the points in [n+1, 2n] into "layers",
        which symmetrically breaks up [1, n], such that each layer only includes points of a certain pair length
        - then, we define our DP state dp[i] to be the number of ways to pair exactly 2i consecutive points, and then
        we compute dp[i] by looking over all possible sizes of the size of the layer containing points 1 and i
        (and possibly more points), including the case where that's the only layer
    - details:
        - in general, if we have a "layered" structure like this, then DP can be a good choice, because our
        transition to compute dp[i] can be to add the last layer by EITHER assuming there are previous layers
        OR creating the first layer
        - i already knew this, but each "size" of the problem can be its own subproblem, where a subproblem is
        a specific element of the DP table
        - there are some problems where dp[i] represents the answer to the subproblem for all states s < i,
        and some problems where dp[i] represents the answer to the subproblem at i; in this problem, dp[i]
        represents the subproblem at exactly i, but we also maintain a prefix sum over DP states to compute dp[i]
    */

    int n;
    cin >> n;

    vector<ll> d(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            d[j] += 1;
        }
    }

    vector<ll> mem(n+1, 0);
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        // case 1: we look over all ending points for the previous layer, but we do it efficiently with
        // a prefix sum over DP values
        mem[i] = sum;

        // case 2: this is the first layer
        mem[i] = (mem[i] + d[i]) % MOD;

        // update prefix sum over DP states
        sum = (sum + mem[i]) % MOD;
    }
    cout << mem[n] << '\n';
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
