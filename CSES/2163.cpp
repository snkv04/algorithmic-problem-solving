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
        build(1, 0, n - 1);
    }

    void build(int vertex, int left, int right) {
        if (left == right) {
            if (left == 0) {
                tree[vertex] = 0;
            } else {
                tree[vertex] = 1;
            }
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid);
        build(2 * vertex + 1, mid + 1, right);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    int _query(int vertex, int left, int right, int query_left, int query_right) {
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

    int query(int left, int right) {
        if (left > right) return 0;
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int idx, int val) {
        if (left == right) {
            tree[vertex] = val;
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

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }

    int walk(int want) {
        int v = 1, l = 0, r = n - 1;
        while (l != r) {
            int m = (l + r) / 2;
            if (tree[2 * v] >= want) {
                v = 2 * v;
                r = m;
            } else {
                want -= tree[2 * v];
                v = 2 * v + 1;
                l = m + 1;
            }
        }
        return l;
    }

private:
    int n;
    std::vector<int> tree;
};

void solve() {
    int n, k;
    cin >> n >> k;

    SegmentTree st(n + 1);
    int rem = n;
    int curr = 1;
    do {
        int want = (k % rem) + 1;
        int to_right = st.query(curr, n);
        if (to_right >= want) {
            want += st.query(1, curr - 1);
        } else {
            want -= to_right;
        }

        int idx = st.walk(want);
        cout << idx << " ";
        st.update(idx, 0);
        curr = idx;
    } while (--rem);
    cout << "\n";
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
