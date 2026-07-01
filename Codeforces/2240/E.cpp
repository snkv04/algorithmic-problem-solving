#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
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
        if (left > right) return 0;

        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int idx, long long val) {
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

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

    int select(int rank) {
        assert(rank > 0);
        int v = 1, l = 0, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (rank > tree[2 * v]) {
                rank -= tree[2 * v];
                v = 2 * v + 1;
                l = m + 1;
            } else {
                v = 2 * v;
                r = m;
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
    vector<char> c(n + 1, 's');
    vector<ll> x(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> c[i] >> x[i];
    }

    SegmentTree placed(n + 1), unplaced(n + 1);
    vector<int> known_invs(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (c[i] == 'p') {
            known_invs[x[i]] = placed.query(x[i], n);
            placed.update(x[i], 1);
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (placed.query(i, i) == 0) {
            unplaced.update(i, 1);
        }
    }

    vector<int> ans(n + 1);
    for (int i = n; i >= 1; --i) {
        if (c[i] == 'p') {
            ans[i] = x[i];
            placed.update(x[i], 0);
        } else {
            int j = i - 1;
            while (c[j] == 'p') --j;

            ll block_invs = 0;
            for (int k = j + 1; k < i; ++k) {
                block_invs += known_invs[x[k]] + unplaced.query(x[k] + 1, n);
            }

            int l = 1, r = unplaced.query(1, n), idx = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                int val = unplaced.select(m);

                ll new_block_invs = block_invs;
                for (int k = j + 1; k < i; ++k) {
                    if (x[k] < val) --new_block_invs;
                }

                int chosen_invs = unplaced.query(val + 1, n) + placed.query(val + 1, n);
                ll total_invs = new_block_invs + chosen_invs;

                if (total_invs >= x[i] - x[j]) {
                    idx = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }

            int val = unplaced.select(idx);
            unplaced.update(val, 0);
            ans[i] = val;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " \n"[i == n];
    }
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
