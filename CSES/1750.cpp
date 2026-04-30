#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<int> parent;
vector<vector<int>> adj, ancestor;
constexpr int LOGMAXK = 30;

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
    int n, q;
    cin >> n >> q;
    parent = vector<int>(n);
    cin >> parent;
    for (int i = 0; i < n; ++i) --parent[i];

    ancestor = vector<vector<int>>(LOGMAXK + 1, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) ancestor[0][i] = parent[i];
    for (int b = 1; b <= LOGMAXK; ++b) {
        for (int i = 0; i < n; ++i) {
            int halfway = ancestor[b - 1][i];
            ancestor[b][i] = ancestor[b - 1][halfway];
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        --x;
        for (int i = 0; i <= LOGMAXK; ++i) {
            if ((k >> i) & 1) x = ancestor[i][x];
        }
        ++x;
        cout << x << endl;
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
