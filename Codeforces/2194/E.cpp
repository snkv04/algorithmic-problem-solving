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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

pair<vector<vector<ll>>, vector<vector<int>>> solve_dr(vector<vector<ll>> &grid) {
    int r = grid.size(), c = grid[0].size();
    vector<vector<ll>> best(r, vector<ll>(c, -1e16));
    vector<vector<int>> from(r, vector<int>(c, -1));  // 0 for down, 1 for right
    best[0][0] = grid[0][0];
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (i == 0 && j == 0) continue;

            if (i) {
                best[i][j] = grid[i][j] + best[i - 1][j];
                from[i][j] = 0;
            }
            if (j && grid[i][j] + best[i][j - 1] > best[i][j]) {
                best[i][j] = grid[i][j] + best[i][j - 1];
                from[i][j] = 1;
            }
        }
    }
    return make_pair(best, from);
}

vector<vector<ll>> solve_ul(vector<vector<ll>> &grid) {
    int r = grid.size(), c = grid[0].size();
    vector<vector<ll>> best(r, vector<ll>(c, -1e16));
    best[r - 1][c - 1] = grid[r - 1][c - 1];
    for (int i = r - 1; i >= 0; --i) {
        for (int j = c - 1; j >= 0; --j) {
            if (i == r - 1 && j == c - 1) continue;

            if (i < r - 1) best[i][j] = grid[i][j] + best[i + 1][j];
            if (j < c - 1) best[i][j] = max(best[i][j], grid[i][j] + best[i][j + 1]);
        }
    }
    return best;
}

void solve() {
    /*
    key ideas:
    - (this is obvious, but just writing this for completeness) based on the fact that at least one
    cell exists that's nonnegative, it can be proven that the minimum possible max-sum path after
    flipping a cell is <= the max-sum path before flipping any cell.
    - this is a minimax problem that, surprisingly, does not use binary search. instead, we brute-force.
    - suppose we flip a cell (i, j) on the best path. then, in the new grid, either the optimal path goes
    through that cell (so it's affected by the flip) or it doesn't go through the cell (so it's not affected
    by the flip). it's true that, a priori (before fully processing the new grid), we don't know for sure if
    the optimal path in the new grid goes through the cell or not. however, we are looking for the OPTIMAL
    path; so, critically, we don't care about which case is true, and we just take the max of the two cases.
    - it's easier to reason about "best path that goes through a cell" and harder to reason about "best path
    that doesn't go through a cell". however, suppose that for a cell x there exists some set of cells Y
    such that if a path doesn't go through x then it's guaranteed to go through some y in Y and if a path
    goes through some y in Y then it's guaranteed to not go through x. basically, there's some set of cells
    for which going through them is perfectly equivalent to not going through x. (this is true in this problem.)
    then, to get "best path not going through x", we just get "best path among all paths that do go through
    any y in Y".
    */

    // read inputs
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> grid(n, vector<ll>(m));
    cin >> grid;

    // solve the DP problem and get the path
    auto [dr, from] = solve_dr(grid);
    auto ul = solve_ul(grid);
    pair<int, int> zero = {0, 0}, curr = {n - 1, m - 1};
    stack<pair<int, int>> path;
    while (curr != zero) {
        path.push(curr);
        if (from[curr.first][curr.second] == 0) {
            --curr.first;
        } else {
            --curr.second;
        }
    }
    path.push(curr);

    // get the best two-directional path (path from end to end covering each cell)
    vector<vector<ll>> best_path(n, vector<ll>(m, -1e16));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            best_path[i][j] = dr[i][j] + ul[i][j] - grid[i][j];
        }
    }

    // get the horizontal and vertical prefix maximums
    vector<vector<ll>> pref_best_right(n, vector<ll>(m, -1e16)), pref_best_down(n, vector<ll>(m, -1e16));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            pref_best_right[i][j] = best_path[i][j];
            if (j) pref_best_right[i][j] = max(pref_best_right[i][j], pref_best_right[i][j - 1]);
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            pref_best_down[i][j] = best_path[i][j];
            if (i) pref_best_down[i][j] = max(pref_best_down[i][j], pref_best_down[i - 1][j]);
        }
    }

    // gets the best path NOT covering a cell (doesn't need to really be precomputed, and this is actually
    // overkill since we compute it for more cells than necessary, but precomputing it makes it quite clear
    // to see what the code is doing)
    vector<vector<ll>> best_not_covering(n, vector<ll>(m, -1e16));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0 && i < n - 1)
                best_not_covering[i][j] = pref_best_right[i + 1][j - 1];
            if (i > 0 && j < m - 1)
                best_not_covering[i][j] = max(best_not_covering[i][j], pref_best_down[i - 1][j + 1]);
        }
    }

    // brute-forces all cells on the optimal path
    // why does ans have to be initialized to default_best? because if the path only consists of
    // negative values, then we can invert a nonnegative cell elsewhere and keep the path as-is
    // without improving it.
    ll default_best = dr[n - 1][m - 1], ans = default_best;
    while (path.size()) {
        auto [i, j] = path.top();
        path.pop();
        ans = min(ans, max(default_best - 2 * grid[i][j], best_not_covering[i][j]));
    }
    cout << ans << "\n";
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
