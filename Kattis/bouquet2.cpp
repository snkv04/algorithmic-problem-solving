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

ld dist(ld x1, ld y1, ld x2, ld y2) {
    ld dx = x2 - x1;
    ld dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    map<char, int> rgb = {
        {'R', 0},
        {'G', 1},
        {'B', 2},        
    };
    int n;
    cin >> n;
    vector<int> x(n), y(n), color(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        char c;
        cin >> c;
        color[i] = rgb[c];
    }

    // - min_dist[i][j] = minimum distance to reach flower i after taking a path like
    // (start -> any flower of color j -> flower i) across all flowers of color j
    // - we basically iterate over all possible middle flowers on our path of 3 flowers
    // and look at all ways to get to that flower through one of the other 2 colors and
    // through the other of the other 2 colors
    vector<vector<ld>> min_dist(n, vector<ld>(3, 1e15));
    for (int i = 0; i < n; ++i) min_dist[i][color[i]] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (color[i] == color[j]) continue;

            min_dist[i][color[j]] = min(
                min_dist[i][color[j]],
                dist(0, 0, x[j], y[j]) + dist(x[j], y[j], x[i], y[i])
            );
        }
    }

    ld ans = 1e15;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, min_dist[i][0] + min_dist[i][1] + min_dist[i][2]);
    }
    cout << fixed << setprecision(12) << ans << endl;
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
