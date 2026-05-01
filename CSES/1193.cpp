#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int r, c;
vector<string> grid;
pair<int, int> a, b;
vector<vector<bool>> visited;
vector<string> from;
string dirs = "RLDU";

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

void bfs(pair<int, int> node) {
    queue<pair<int, int>> q;
    q.push(node);
    while (q.size()) {
        auto [i, j] = q.front();
        q.pop();
        if (visited[i][j]) continue;
        visited[i][j] = true;

        for (int k = 0; k < 4; ++k) {
            int newi = i + di[k], newj = j + dj[k];
            if (
                newi >= 0 &&
                newi < r &&
                newj >= 0 &&
                newj < c &&
                (grid[newi][newj] == '.' || grid[newi][newj] == 'B') &&
                !visited[newi][newj]
            ) {
                from[newi][newj] = dirs[k];
                q.push({newi, newj});
            }
        }
    }
}

void solve() {
    cin >> r >> c;
    grid = vector<string>(r);
    cin >> grid;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (grid[i][j] == 'A') {
                a = {i, j};
            } else if (grid[i][j] == 'B') {
                b = {i, j};
            }
        }
    }

    visited = vector<vector<bool>>(r, vector<bool>(c, false));
    from = vector<string>(r, string(c, ' '));
    bfs(a);

    if (!visited[b.first][b.second]) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        stack<char> path;
        while (b != a) {
            char direction = from[b.first][b.second];
            path.push(direction);
            if (direction == 'L') {
                b.second += 1;
            } else if (direction == 'R') {
                b.second -= 1;
            } else if (direction == 'D') {
                b.first -= 1;
            } else {
                b.first += 1;
            }
        }

        cout << path.size() << "\n";
        while (path.size()) {
            char top = path.top();
            path.pop();
            cout << top;
        }
        cout << "\n";
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
