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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    cin >> grid;

    int cnt = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cnt += grid[i][j];

    vector<int> wall(n, m);
    int curr = 0;
    for (int i = 0; i < n && curr < cnt / 2; ++i) {
        for (int j = m - 1; j >= 0 && curr < cnt / 2; --j) {
            if (grid[i][j]) {
                ++curr;
                wall[i] = j;
            }
        }
    }
    for (int i = n - 2; i >= 0; --i) wall[i] = min(wall[i], wall[i + 1]);

    cout << 1LL * curr * (cnt - curr) << endl;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < wall[i]) {
            cout << 'R';
            ++j;
        }
        cout << 'D';
    }
    while (j < m) {
        cout << 'R';
        ++j;
    }
    cout << endl;
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
