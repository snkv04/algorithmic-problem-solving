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

void dfs(int i, int j, vector<string> &grid, vector<vector<bool>> &visited) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) return;
    if (grid[i][j] == '#') return;
    if (visited[i][j]) return;

    visited[i][j] = true;
    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k];
        int nj = j + dj[k];
        dfs(ni, nj, grid, visited);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    cin >> grid;

    int g = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'G') ++g;
            else if (grid[i][j] == 'B') ++b;
        }
    }

    if (g == 0) {
        cout << "Yes\n";
        return;
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    dfs(n - 1, m - 1, grid, visited);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'G' && !visited[i][j]) {
                cout << "No\n";
                return;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'B') {
                for (int k = 0; k < 4; ++k) {
                    int ni = i + di[k], nj = j + dj[k];
                    if (ni < 0 || ni >= n || nj < 0 || nj >= m) {
                        continue;
                    }
                    if (grid[ni][nj] == 'G') {
                        cout << "No\n";
                        return;
                    } else if (grid[ni][nj] == '.') {
                        grid[ni][nj] = '#';
                    }
                }
            }
        }
    }

    visited = vector<vector<bool>>(n, vector<bool>(m, false));
    dfs(n - 1, m - 1, grid, visited);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((grid[i][j] == 'G' && !visited[i][j]) || (grid[i][j] == 'B' && visited[i][j])) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
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
