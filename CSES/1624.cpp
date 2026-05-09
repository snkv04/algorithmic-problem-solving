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

bool is_attacked(int r1, int c1, int r2, int c2) {
    return (
        r1 == r2 ||
        c1 == c2 ||
        r1 + c1 == r2 + c2 ||
        r1 - c1 == r2 - c2
    );
}

bool check(int row, int col, vector<int> &placed_col) {
    for (int prev_row = 0; prev_row < row; ++prev_row) {
        if (is_attacked(prev_row, placed_col[prev_row], row, col)) {
            return false;
        }
    }
    return true;
}

void dfs(int row, const vector<string> &grid, int &ans, vector<int> &placed_col) {
    if (row == 8) {
        ++ans;
        return;
    }

    for (int col = 0; col < 8; ++col) {
        if (check(row, col, placed_col) && grid[row][col] == '.') {
            placed_col[row] = col;
            dfs(row + 1, grid, ans, placed_col);
            placed_col[row] = -1;
        }
    }
}

void solve() {
    vector<string> grid(8);
    cin >> grid;
    int ans = 0;
    vector<int> placed_col(8, -1);
    dfs(0, grid, ans, placed_col);
    cout << ans << "\n";
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
