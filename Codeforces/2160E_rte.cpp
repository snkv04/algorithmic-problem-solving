#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
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

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
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

vector<vector<int>> transpose(vector<vector<int>> &grid) {
    int r = grid.size(), c = grid[0].size();
    vector<vector<int>> result(c, vector<int>(r));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            result[j][i] = grid[i][j];
        }
    }
    return result;
}

void solve() {
    // reads in grid
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = s[j] == '1';
        }
    }

    // transposes matrix if needed
    bool flipping = false;
    if (n > m) {
        flipping = true;
        grid = transpose(grid);
        swap(n, m);
    }

    // brute-forces across rectangles by: iterating through each (u, d), and for each,
    // walking through columns and finding rectangles based on both (u, col) and (d, col) being activated
    int best[n][n][m];
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) fill(best[i][j], best[i][j] + m, 1e9);
    vector<int> cols;
    for (int u = 0; u < n; ++u) {
        for (int d = u + 1; d < n; ++d) {
            if (cols.size())
                cols.clear();
            for (int j = 0; j < m; ++j) {
                if (grid[u][j] && grid[d][j]) {
                    cols.push_back(j);
                }
            }
            // cout << "cols = " << cols << "\n";

            for (int idx = 0; idx < (int) cols.size() - 1; ++idx) {
                int l = cols[idx], r = cols[idx + 1];
                int area = (d - u + 1) * (r - l + 1);
                for (int c = l; c <= r; ++c) {
                    best[u][d][c] = min(best[u][d][c], area);
                }
            }
        }
    }

    // for each column, walks through rows to get final answer for each (row, col) cell
    vector<vector<int>> ans(n, vector<int>(m, 1e9));
    multiset<int> curr;
    for (int j = 0; j < m; ++j) {
        curr.clear();
        for (int i = 0; i < n; ++i) {
            for (int d = i + 1; d < n; ++d) {
                curr.insert(best[i][d][j]);
            }

            int val = *curr.begin();
            ans[i][j] = val == 1e9 ? 0 : val;

            for (int u = 0; u < i; ++u) {
                curr.erase(curr.find(best[u][i][j]));
            }
        }
    }

    // un-transposes matrix
    if (flipping) {
        ans = transpose(ans);
        swap(n, m);
    }

    // outputs answers
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
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
