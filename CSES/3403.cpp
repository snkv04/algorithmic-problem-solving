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
    vector<int> a(n), b(m);
    cin >> a >> b;

    vector<vector<int>> mem(n + 1, vector<int>(m + 1, 0));
    vector<vector<pair<int, int>>> prev(n + 1, vector<pair<int, int>>(m + 1, {-1, -1}));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (mem[i][j - 1] > mem[i][j]) {
                mem[i][j] = mem[i][j - 1];
                prev[i][j] = make_pair(i, j - 1);
            }

            if (mem[i - 1][j] > mem[i][j]) {
                mem[i][j] = mem[i - 1][j];
                prev[i][j] = make_pair(i - 1, j);
            }

            if (a[i - 1] == b[j - 1] && mem[i - 1][j - 1] + 1 > mem[i][j]) {
                mem[i][j] = mem[i - 1][j - 1] + 1;
                prev[i][j] = make_pair(i - 1, j - 1);
            }
        }
    }
    // for (int i = 0; i <= n; ++i) {
    //     for (int j = 0; j <= m; ++j) {
    //         cout << prev[i][j] << '\t';
    //     }
    //     cout << '\n';
    // }

    cout << mem[n][m] << endl;
    vector<int> subsequence;
    int i = n, j = m;
    while (i != 0 && j != 0 && i != -1 && j != -1) {
        auto [prev_i, prev_j] = prev[i][j];
        if (i == prev_i + 1 && j == prev_j + 1) {
            subsequence.push_back(a[i - 1]);
        }
        i = prev_i;
        j = prev_j;
    }
    reverse(subsequence.begin(), subsequence.end());
    for (int num : subsequence) cout << num << ' ';
    cout << endl;
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
