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
    int a, b;
    cin >> a >> b;

    // mem[i][j] = min cuts to get a block of size ixj to be composed of squares
    vector<vector<int>> mem(a + 1, vector<int>(b + 1, 1e9));
    for (int i = 0; i <= a; ++i) mem[i][0] = 0;
    for (int j = 0; j <= b; ++j) mem[0][j] = 0;
    for (int i = 1; i <= a; ++i) mem[i][1] = i - 1;
    for (int j = 1; j <= b; ++j) mem[1][j] = j - 1;
    for (int i = 1; i <= min(a, b); ++i) mem[i][i] = 0;

    for (int i = 2; i <= a; ++i) {
        for (int j = 2; j <= b; ++j) {
            for (int k = 1; k <= min(i, j); ++k) {
                int cuts = k == min(i, j) ? (i == j ? 0 : 1) : 2;
                mem[i][j] = min({
                    mem[i][j],
                    cuts + mem[i-k][k] + mem[k][j-k] + mem[i-k][j-k],
                    cuts + mem[i-k][k] + mem[i][j-k],
                    cuts + mem[k][j-k] + mem[i-k][j],
                });
            }
        }
    }
    cout << mem[a][b] << endl;
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
