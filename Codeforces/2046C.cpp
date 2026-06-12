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

struct SegmentTree {
    SegmentTree(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
    }

    SegmentTree(const std::vector<int> &arr) : arr(arr), n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int vertex, int left, int right) {
        if (left == right) {
            tree[vertex] = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid);
        build(2 * vertex + 1, mid + 1, right);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        if (right < query_left || query_right < left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return _query(2 * vertex, left, mid, query_left, query_right) +
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right);
    }

    long long query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int idx, long long val) {
        if (left == right) {
            tree[vertex] += val;  // adds, not sets
            return;
        }

        int mid = left + (right - left) / 2;
        if (idx <= mid) {
            _update(2 * vertex, left, mid, idx, val);
        } else {
            _update(2 * vertex + 1, mid + 1, right, idx, val);
        }
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

    int walk(int want) {
        if (want == 0) return n - 1;

        int v = 1, l = 0, r = n - 1;
        while (l != r) {
            int m = (l + r) / 2;
            if (want > tree[2 * v + 1]) {
                want -= tree[2 * v + 1];
                v = 2 * v;
                r = m;
            } else {
                v = 2 * v + 1;
                l = m + 1;
            }
        }
        return l;
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<int> arr;
};

void solve() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    map<int, int> cx, cy;
    for (int i = 0; i < n; ++i) {
        cx[x[i]] = -1;
        cy[y[i]] = -1;
    }
    if (cx.size() == 1 || cy.size() == 1) {
        cout << "0\n";
        cout << cx.begin()->first << " " << cy.begin()->first << "\n";
        return;
    }

    int timer = 0;
    map<int, int> dcx, dcy;
    for (auto &[k, v] : cx) {
        dcx[timer] = k;
        v = timer++;
    }
    timer = 0;
    for (auto &[k, v] : cy) {
        dcy[timer] = k;
        v = timer++;
    }

    map<int, vector<int>> coords;
    for (int i = 0; i < n; ++i) coords[cx[x[i]]].push_back(cy[y[i]]);
    SegmentTree left(cy.size()), right(cy.size());
    for (auto [x, ys] : coords) {
        for (auto y : ys) {
            right.update(y, 1);
        }
    }

    int ans = 0, ansx = cx.begin()->first, ansy = cy.begin()->first;
    int cntx = cx.size(), cnty = cy.size();
    for (auto [x, ys] : coords) {
        int l = ans, r = min(left.query(0, cnty - 1), right.query(0, cnty - 1));
        while (l <= r) {
            int m = (l + r) / 2;

            int lefty = left.walk(m), righty = right.walk(m);
            int y = min(lefty, righty);
            if (
                left.query(0, cnty - 1) - left.query(y, cnty - 1) >= m &&
                right.query(0, cnty - 1) - right.query(y, cnty - 1) >= m
            ) {
                ans = m;
                ansx = dcx[x];
                ansy = dcy[y];
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        for (auto y : ys) {
            right.update(y, -1);
            left.update(y, 1);
        }
    }
    cout << ans << "\n" << ansx << " " << ansy << "\n";
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
