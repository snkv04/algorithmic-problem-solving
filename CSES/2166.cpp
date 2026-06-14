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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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

struct Lazy {
    Lazy(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        pending.resize(4 * n);
        std::fill(pending.begin(), pending.end(), 0);
    }

    void push_down(int vertex, int left, int right) {
        if (pending[vertex] != 0) {
            tree[vertex] += pending[vertex];

            if (left != right) {
                pending[2 * vertex] += pending[vertex];
                pending[2 * vertex + 1] += pending[vertex];
            }

            pending[vertex] = 0;
        }
    }

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return -1e18;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return max(
            _query(2 * vertex, left, mid, query_left, query_right),
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right)
        );
    }

    long long query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int query_left, int query_right, long long val) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            pending[vertex] += val;
            push_down(vertex, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        _update(2 * vertex, left, mid, query_left, query_right, val);
        _update(2 * vertex + 1, mid + 1, right, query_left, query_right, val);
        tree[vertex] = max(tree[2 * vertex], tree[2 * vertex + 1]);
    }

    void update(int left, int right, long long val) {
        _update(1, 0, n - 1, left, right, val);
    }

private:
    int n;
    std::vector<long long> tree, pending;
    std::vector<int> arr;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    Lazy pre(n);
    for (int i = 0; i < n; ++i) {
        pre.update(i, n - 1, a[i]);
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int idx, val;
            cin >> idx >> val;
            --idx;
            pre.update(idx, n - 1, -a[idx]);
            a[idx] = val;
            pre.update(idx, n - 1, a[idx]);
        } else {
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << max(0LL, pre.query(l, r) - (l == 0 ? 0 : pre.query(l - 1, l - 1))) << endl;
        }
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
