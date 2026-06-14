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

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        if (right < query_left || query_right < left) {
            return 1e9;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return min(
            _query(2 * vertex, left, mid, query_left, query_right),
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right)
        );
    }

    long long query(int left, int right) {
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
        tree[vertex] = min(tree[2 * vertex], tree[2 * vertex + 1]);
    }

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<int> arr;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    cin >> v; v.insert(v.begin(), 0);

    map<int, set<int>> indices;
    for (int i = 1; i <= n; ++i) {
        if (indices.count(v[i]) == 0) {
            indices[v[i]] = {0, n + 1};
        }
        indices[v[i]].insert(i);
    }

    SegmentTree next_idx(n + 1);
    for (int i = 1; i <= n; ++i) next_idx.update(i, *indices[v[i]].upper_bound(i));
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int idx, val;
            cin >> idx >> val;
            if (val == v[idx]) continue;

            // updates "next" index for old value
            int old_val = v[idx];
            indices[old_val].erase(idx);
            auto it = indices[old_val].upper_bound(idx);
            --it;
            next_idx.update(*it, *indices[old_val].upper_bound(idx));

            // updates "next" indices for new value
            if (!indices.count(val)) {
                indices[val] = {0, n + 1};
            }
            indices[val].insert(idx);
            next_idx.update(idx, *indices[val].upper_bound(idx));
            it = indices[val].lower_bound(idx);
            --it;
            next_idx.update(*it, idx);
        } else {
            assert(t == 2);

            // checks if minimum "next" index for any index in range is also <= right bound of range
            int l, r;
            cin >> l >> r;
            int mn = next_idx.query(l, r);
            cout << (mn > r ? "YES" : "NO") << endl;
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
