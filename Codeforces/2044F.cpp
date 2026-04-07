#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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

void solve() {
    /*
    - problem:
        - we are given an array a of length n and an array b of length m, and together, they define
        an nxm grid such that grid[i][j] = a[i] * b[j]
        - then, for each query, we are given a value x and want to see if (sum(grid) - sum(cross) = x)
        for some cross defined by (i, j)
    - the solution is pretty much this:
        - do some math to show that for a fixed a_i and value x, the value of b_j that we need is fixed
            - namely, we want to just find some (i, j) such that x = (sum(a) - a_i) * (sum(b) - b_j)
        - precompute the contribution of each a_i and each b_j
        - then, for a given x, iterate through all the divisors of x (and all 4 combinations of which
        divisor comes from which array and if they're negated) to see if there's some (i, j) that satisfies
        the desired equation
    */

    // reads in input
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n), b(m);
    cin >> a >> b;

    // precomputes possible factors
    ll sum_a = 0, sum_b = 0;
    for (int a_i : a) sum_a += a_i;
    for (int b_j : b) sum_b += b_j;
    unordered_set<ll> factors_a, factors_b;
    for (int a_i : a) factors_a.insert(sum_a - a_i);
    for (int b_j : b) factors_b.insert(sum_b - b_j);

    // iterates through O(sqrt(abs(x))) possible factors for each query x
    while (q--) {
        ll x;
        cin >> x;
        ll rt = sqrt(abs(x));
        bool found = false;
        for (int i = 1; i <= rt; ++i) {
            if (abs(x) % i == 0) {
                ll other = x / i;
                if (
                    (factors_a.count(i) && factors_b.count(other)) ||
                    (factors_a.count(-i) && factors_b.count(-other)) ||
                    (factors_a.count(other) && factors_b.count(i)) ||
                    (factors_a.count(-other) && factors_b.count(-i))
                ) {
                    found = true;
                    break;
                }
            }
        }
        cout << (found ? "yes" : "no") << '\n';
    }
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
