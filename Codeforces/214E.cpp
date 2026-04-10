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
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> a[i][j];

    vector<array<int, 4>> delta = {
        {-1, 0, -1, 0},
        {-1, 0, 0, -1},
        {0, -1, -1, 0},
        {0, -1, 0, -1}
    };
    auto in_bounds = [&](int i, int j) { return i >= 0 && i < n && j >= 0 && j < n; };

    // have to be very meticulous with bounds checking for i_2 and j_2
    int mem[n][n][n];
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) fill(mem[i][j], mem[i][j] + n, -1e9);
    mem[0][0][0] = a[0][0];
    for (int i1 = 0; i1 < n; ++i1) {
        for (int j1 = 0; j1 < n; ++j1) {
            for (int i2 = 0; i2 < n && i2 <= i1 + j1; ++i2) {
                int j2 = i1 + j1 - i2;
                if (i2 == 0 && j2 == 0) continue;
                if (j2 >= n) continue;

                int added = a[i1][j1] + a[i2][j2];
                if (i2 == i1 && j2 == j1) added -= a[i2][j2];
                for (int k = 0; k < 4; ++k) {
                    auto [di1, dj1, di2, dj2] = delta[k];
                    int pi1 = i1 + di1;
                    int pj1 = j1 + dj1;
                    int pi2 = i2 + di2;
                    int pj2 = j2 + dj2;
                    if (in_bounds(pi1, pj1) && in_bounds(pi2, pj2)) {
                        mem[i1][j1][i2] = max(
                            mem[i1][j1][i2],
                            added + mem[pi1][pj1][pi2]
                        );
                    }
                }
            }
        }
    }
    cout << mem[n - 1][n - 1][n - 1] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
