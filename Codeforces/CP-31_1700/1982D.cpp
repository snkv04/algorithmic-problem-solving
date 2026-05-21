#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

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

ll gcd(ll a, ll b) {
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll r = A % B;
        A = B;
        B = r;
    }
    return A;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }
    vector<string> mask(n);
    for (int i = 0; i < n; ++i) cin >> mask[i];

    vector<vector<int>> prefsums0(n, vector<int>(m, 0)), prefsums1(n, vector<int>(m, 0));;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int val0 = mask[i][j] == '0';
            if (i > 0) val0 += prefsums0[i-1][j];
            if (j > 0) val0 += prefsums0[i][j-1];
            if (i > 0 && j > 0) val0 -= prefsums0[i-1][j-1];
            prefsums0[i][j] = val0;

            int val1 = mask[i][j] == '1';
            if (i > 0) val1 += prefsums1[i-1][j];
            if (j > 0) val1 += prefsums1[i][j-1];
            if (i > 0 && j > 0) val1 -= prefsums1[i-1][j-1];
            prefsums1[i][j] = val1;
        }
    }

    ll s0 = 0, s1 = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mask[i][j] == '0') s0 += grid[i][j];
            else s1 += grid[i][j];
        }
    }

    int factor = 0;
    for (int i = k-1; i < n; ++i) {
        for (int j = k-1; j < m; ++j) {
            auto get_window = [k](vector<vector<int>> &prefixsums, int i2, int j2) {
                ll area = prefixsums[i2][j2];
                if (i2-k >= 0) area -= prefixsums[i2-k][j2];
                if (j2-k >= 0) area -= prefixsums[i2][j2-k];
                if (i2-k >= 0 && j2-k >= 0) area += prefixsums[i2-k][j2-k];
                return area;
            };

            int window = abs(get_window(prefsums0, i, j) - get_window(prefsums1, i, j));
            factor = gcd(factor, window);
        }
    }

    ll diff = abs(s0 - s1);
    cout << ((diff == 0 || (factor != 0 && diff % factor == 0)) ? "YES" : "NO") << "\n";
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
