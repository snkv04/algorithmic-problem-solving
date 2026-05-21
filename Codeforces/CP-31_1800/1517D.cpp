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

struct EntryComparator {
    bool operator()(const array<ll, 4> &a, const array<ll, 4> &b) const {
        if (a[2] != b[2]) {
            return a[2] > b[2];
        } else {
            return a[3] > b[3];
        }
    }
};

void solve() {
    /*
    - problem:
        - we are given a grid, and each adjacent pair of cells has an associated weight between them.
        - for each cell, we want to find the minimum weight of a path going out from that cell and
        returning to it after exactly k steps.
    - solution:
        - the second half of the path can start from anywhere, and if it's optimal, then the first half
        of the path will just retrace its steps.
        - so, for each cell, find the minimum length of a path that ends there after k steps and starts
        from anywhere using DP, then just double that
    - details:
        - the intuitive solution:
            - for each cell (i, j), we can compute mem[r][c][s], which is the minimum distance (across all
            paths) from (i, j) after taking exactly s steps and ending up at (r, c).
            - we don't need to find the min dist from (i, j) across all cells. we only need to find it for
            the cells whose Manhattan distance from (i, j) is <= k/2.
            - by reusing the DP table (and not creating a new table of size nxm for each of the nxm cells),
            this solution is O(n * m * k^3).
            - this solution can also be optimized by just assuming we go half the path length and then
            retrace the same path backward for the second half, which does cut down the runtime by about a
            factor of 8, but asymptotically it's the same.
            - specifically, if we assume we are starting from (i, j) and then travel outward:
                - then mem[r][c][s] is the minimum distance from (i, j) to (r, c) after s steps
                - and the answer for cell (i, j) is double of the minimum of mem[r][c][k] across all (r, c).
        - the important observations:
            - we don't need the full path. we can just go half the shortest path of k/2 steps and retrace
            our steps to go the way back.
            - critically, if we look at the first half of the path, then we start at (i, j) and our DP state
            relies on our starting point, but if we look at the second half of the path, then we can start
            from ANYWHERE and end at (i, j). the REASON why this is important is that the DP state won't rely
            on the starting location.
        - the faster solution:
            - we assume we are starting anywhere and then traveling inward to (i, j), so then:
                - mem[i][j][s] is the minimum distance to get to (i, j) after exactly s steps
                - and the answer for cell (i, j) is just (2 * mem[i][j][k/2])
            - the way we do this is initialize mem[i][j][0] == 0 for all (i, j), initialize mem[i][j][s]
            to inf for all (i, j) and s != 0, then run a standard DP by iterating upward on s
    */

    // reads in input grid
    int n, m, k;
    cin >> n >> m >> k;
    if (k % 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << "-1 ";
            }
            cout << "\n";
        }
        return;
    }
    vector<vector<int>> right(n, vector<int>(m-1)), down(n-1, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        cin >> right[i];
    }
    for (int i = 0; i < n-1; ++i) {
        cin >> down[i];
    }

    // finds half-path to each node with minimum weight
    k /= 2;
    ll mem[n][m][k + 1];
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        fill(mem[i][j] + 1, mem[i][j] + k + 1, 1e15);
        mem[i][j][0] = 0;
    }
    for (int steps = 1; steps <= k; ++steps) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int dir = 0; dir < 4; ++dir) {
                    int previ = i + di[dir], prevj = j + dj[dir];
                    if (previ < 0 || previ >= n || prevj < 0 || prevj >= m) continue;

                    ll weight;
                    if (dir == 0) weight = right[i][j];
                    else if (dir == 1) weight = right[i][j-1];
                    else if (dir == 2) weight = down[i][j];
                    else weight = down[i-1][j];

                    mem[i][j][steps] = min(mem[i][j][steps], mem[previ][prevj][steps-1] + weight);
                }
            }
        }
    }
    
    // outputs double of final distances to each cell
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << 2 * mem[i][j][k] << " ";
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
