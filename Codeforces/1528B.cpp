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
        - break up the points in [n+1, 2n] into "layers", which symmetrically breaks up [1, n], such that
        each layer only includes points of a certain pair length
        - then, note that all layers except the first have a deterministic, fixed pair length, while the first
        layer has a few different pair lengths (which is equal to d(x_1)), so then we can iterate over the size
        of the first layer and add a term to the answer for each value
    - details:
        - first, observe that the two conditions cannot both hold at once; so, either two segments are the same
        length or one is contained in the other
        - then, we can see that we can break up the points in [n+1, 2n] into layers, which are mathematically
        defined using the variables 1 <= x_1, x_2, ..., x_k <= n, where the points p_1 in [n + 1 - x_1, n + x_1]
        are paired with each other, the points in [n + 1 - x_2, n - x_1] are paired with [n + x_1 + 1, n + x_2],
        etc. the point of these layers is that the points in each layer are paired into pairs that all have the
        same length
        - interestingly, for all layers >= 2, that layer's points has EXACTLY one way to pair the points, and for
        layer 1, we have 2*x_1 points total, which must be divisble by blocks of length 2L if we want the pairs to
        have length L, so x_1 % L must equal 0
        - finally, we can iterate over x_1; for each, the number of ways for the first layer is d(x_1), and the number
        of ways for the other layers is just the number of ways to pick the variables x_2, x_3, ..., x_k, where x_k == n,
        because for each selection there's only one way to pair the elements given that set of variables, so we
        just multiply these 2 variables together for each choice of x_1
            - the number of ways to pick x_2, x_3, ..., x_{k-1} is just the size of the power set of the integers
            strictly greater than x_1 and strictly less than n
        - always try to have some mathematical notation for whatever i'm doing, so that things are easier to refer to
    */

    int n;
    cin >> n;

    vector<ll> d(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            d[j] += 1;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (i < n) {
            ans = (ans + (d[i] * modpow(2, n - 1 - i) % MOD)) % MOD;
        } else {
            ans = (ans + d[i]) % MOD;
        }
    }
    cout << ans << '\n';
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
