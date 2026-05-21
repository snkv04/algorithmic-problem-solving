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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), cold(k), hot(k);
    cin >> a >> cold >> hot;
    a.push_back(0);
    cold.insert(cold.begin(), 0);
    hot.insert(hot.begin(), 0);

    /*
    - mem[i][j] = minimum cost on suffix starting at index i, where we assume program i is on the black CPU,
    we assume i is having a cold start (nothing before it), and j is the color of the very first program
    on the white CPU
    - for a given index, if we look at the color of the next program on the same CPU, we can decide whether
    we'll keep that next program as cold or switch it to hot
        - this is feasible, since we can just always assume something is cold at the start of a suffix,
        and move it to hot by taking the difference between costs
        - then, we'll add the cost of the current program by again assuming that it's cold
        - in implementation, it doesn't actually matter if we "update next to be hot" or "set current to be
        hot", because it's the same logic: each adjacent pair of same color will just be (2 * cold - (cold - hot))
    */
    vector<vector<ll>> mem(n + 1, vector<ll>(k + 1, 1e15));
    mem[n][0] = 0;
    for (int i = n - 1; i >= 0; --i) {
        // same CPU
        for (int j = 0; j <= k; ++j) {
            mem[i][j] = mem[i + 1][j] + (a[i] == a[i + 1] ? hot[a[i]] : cold[a[i]]);
        }

        // diff CPU
        for (int j = 0; j <= k; ++j) {
            mem[i][a[i + 1]] = min(
                mem[i][a[i + 1]],
                mem[i + 1][j] + (a[i] == j ? hot[a[i]] : cold[a[i]])
            );
        }
    }

    ll ans = 1e15;
    for (int j = 0; j <= k; ++j) ans = min(ans, mem[0][j]);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
