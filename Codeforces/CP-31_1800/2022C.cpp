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
    /*
    - problem:
        - we have a 2xn grid, and tiles of the shape:
            - o o o
            - o
              o o
        - we need to partition the grid into tiles such that the tiling receives a maximum score, where
        the score of a tiling is based on the grid's cells that each tile lands on
    - solution:
        - for each column i, we can let:
            - mem[i][0] be the max score after filling in the first i columns completely
            - mem[i][1] be the max score after filling in the first i columns for the first row and the
            first i-1 columns for the second row
            - mem[i][2] be the max score after filling in the first i-1 columns for the first row and
            the first i columns for the second row
        - now that we've defined these DP states, they're all we need to compute the max score for all
        possible tiling configurations using dynamic programming
    - details:
        - the fact that we need to group houses such that "any 3 houses are connected" basically means that
        the groups must take on one of those 2 shapes
        - flat states depend on jagged states, and jagged states depend on flat states; that's why they're
        both needed
    */

    // reads in the input and makes the strings 1-indexed
    int n;
    cin >> n;
    vector<string> grid(2);
    cin >> grid[0] >> grid[1];
    grid[0].insert(grid[0].begin(), ' ');
    grid[1].insert(grid[1].begin(), ' ');

    // defines the scores for the tiles
    auto tr = [&](int col) {
        int cnt = 0;
        cnt += grid[0][col] == 'A';
        cnt += grid[1][col] == 'A';
        cnt += grid[0][col-1] == 'A';
        return cnt >= 2;
    };
    auto tl = [&](int col) {
        return (
            (grid[0][col] == 'A') +
            (grid[0][col-1] == 'A') +
            (grid[1][col-1] == 'A')
        ) >= 2;
    };
    auto br = [&](int col) {
        return (
            (grid[0][col] == 'A') +
            (grid[1][col] == 'A') +
            (grid[1][col-1] == 'A')
        ) >= 2;
    };
    auto bl = [&](int col) {
        return (
            (grid[1][col] == 'A') +
            (grid[0][col-1] == 'A') +
            (grid[1][col-1] == 'A')
        ) >= 2;
    };
    auto straight = [&](int r, int c) {
        return (
            (grid[r][c] == 'A') + (grid[r][c-1] == 'A') + (grid[r][c-2] == 'A')
        ) >= 2;
    };

    // runs DP
    constexpr int INF = 1e9;
    vector<vector<int>> mem(n + 1, vector<int>(3, -INF));
    mem[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        // flat face
        if (i >= 2) mem[i][0] = max({
            mem[i][0],
            mem[i-1][2] + tr(i),
            mem[i-1][1] + br(i)
        });
        if (i >= 3) mem[i][0] = max(
            mem[i][0],
            mem[i-3][0] + straight(0, i) + straight(1, i)
        );

        // protruding on top
        if (i >= 2) mem[i][1] = max(
            mem[i][1],
            mem[i-2][0] + tl(i)
        );
        if (i >= 4) mem[i][1] = max(
            mem[i][1],
            mem[i-3][1] + straight(0, i) + straight(1, i-1)
        );

        // protruding on bottom
        if (i >= 2) mem[i][2] = max(
            mem[i][2],
            mem[i-2][0] + bl(i)
        );
        if (i >= 4) mem[i][2] = max(
            mem[i][2],
            mem[i-3][2] + straight(1, i) + straight(0, i-1)
        );
    }
    cout << mem[n][0] << '\n';
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
