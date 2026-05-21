#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

void solve() {
    /*
    main ideas:
    - evidently, we need the dimensions to be of opposite parity.
    - it's clear that a brute-force way is to keep track of every possible value that is achievable
    by ending the path at each cell in the grid. maybe this could involve some intersections of achievable
    intervals. however, this is clearly too slow. the only difficult part of this problem is recognizing
    that only holding the min and max achievable for each cell is, indeed, sufficient. first, note that
    for a given cell, the parities of all path sums for paths that end at that cell are equivalent. now,
    we just want to know how we can get from the min path to the max path while making sure to hit every
    path sum of the same parity on the way. this involves switching out a -1 for a 1 (or vice versa)
    repeatedly. the proof comes down to this: if we want to get from the min path to the max path, we
    basically just have to switch cells 1-by-1, moving a -1 to a 1 over and over, and we are guaranteed
    to hit every path sum with same parity on the way. so, we just have to keep track of the min and max
    achievable at each cell, and since its parity will be even for that bottom-right-most cell, we just
    check if 0 is contained in the [min, max] interval for that last cell.

    generalizable ideas:
    - how do we know that every value in a range is achievable if the min and max are achievable? try
    making small operations at a time that move a value over by 1 (or by 2, if the parity is forced to be
    the same, or maybe by another step). that way, we can hit every value in the range from the min to the
    max. in this case, the operations consist of removing a cell and adding a cell diagonal to it in order
    to change the location where a "turn" in the path happens.
    - if we know that each cell in a DP grid will have at least one of its left or above cells be valid
    (specifically, we're talking about the borders of the grid, so it's a discussion on edge cases basically),
    then we can initialize the cell's value to something that will definitely change (such as 1e9 if we're going
    to take the minimum), and then outside of the loop, set the base case's cell (e.g., (0, 0)) and then skip
    it in the loop. the alternative is to initialize the cell's value to something else (such as a[i][j]),
    but that could then cause issues because if we take a max (like in
    mem[i][j] = max(mem[i][j], mem[i-1][j] + something)), then the initial value might be "better", but it's
    impossible to get to in the first place (because getting to (i, j) must involve getting there from a
    previous state).
    */

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    if ((n + m) % 2 == 0) {
        cout << "NO\n";
        return;
    }

    vector<vector<pair<int, int>>> mem(n, vector<pair<int, int>>(m));
    mem[0][0] = make_pair(a[0][0], a[0][0]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 && j == 0) continue;

            int cell = a[i][j];
            mem[i][j] = make_pair(1e9, -1e9);
            if (i) {
                mem[i][j].first = min(mem[i][j].first, mem[i-1][j].first + cell);
                mem[i][j].second = max(mem[i][j].second, mem[i-1][j].second + cell);
            }
            if (j) {
                mem[i][j].first = min(mem[i][j].first, mem[i][j-1].first + cell);
                mem[i][j].second = max(mem[i][j].second, mem[i][j-1].second + cell);
            }
        }
    }
    // for (int i = 0; i < n; ++i) print_container(mem[i]);
    cout << ((mem[n-1][m-1].first <= 0 && mem[n-1][m-1].second >= 0) ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
