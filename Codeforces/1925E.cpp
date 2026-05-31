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

struct Lazy {
    Lazy(const std::vector<ll> &val, const std::vector<ll> &base_cost) : n(val.size()) {
        val_t = vector<ll>(4 * n, -1);
        pending_val = vector<ll>(4 * n, -1);
        base_cost_t = vector<ll>(4 * n, 0);
        pending_base = vector<ll>(4 * n, 0);
        total_cost_t = vector<ll>(4 * n, 0);
        build(1, 0, n - 1, val, base_cost);
    }

    void combine(int vertex) {
        base_cost_t[vertex] = base_cost_t[2 * vertex] + base_cost_t[2 * vertex + 1];
        if (val_t[2 * vertex] == val_t[2 * vertex + 1]) {
            val_t[vertex] = val_t[2 * vertex];
        } else {
            // it's simply important to consider both cases.
            // if the children's values aren't the same,
            // this one's value should be updated to -1.
            // otherwise, it will be stale (representing
            // a property of an old state of things).
            val_t[vertex] = -1;

        }
        total_cost_t[vertex] = total_cost_t[2 * vertex] + total_cost_t[2 * vertex + 1];
    }

    void build(int vertex, int left, int right, const std::vector<ll> &val, const std::vector<ll> &base_cost) {
        if (left == right) {
            val_t[vertex] = val[left];
            base_cost_t[vertex] = base_cost[left];
            total_cost_t[vertex] = val_t[vertex] * base_cost_t[vertex];
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid, val, base_cost);
        build(2 * vertex + 1, mid + 1, right, val, base_cost);
        combine(vertex);
    }

    void push_down(int vertex, int left, int right) {
        // updates this node
        bool pbase = pending_base[vertex] != 0;
        bool pval = pending_val[vertex] != -1;
        if (pbase) {
            base_cost_t[vertex] += (right - left + 1) * pending_base[vertex];
        }
        if (pval) {
            val_t[vertex] = pending_val[vertex];
        }
        if (pbase || pval) {
            // only touches total_cost_t if there is a pending operation on this node's corresponding segment.
            // why? if there's a pending operation on the segment, then we know from the problem
            // that the value on this segment is guaranteed to be the same.
            assert(val_t[vertex] != -1);
            total_cost_t[vertex] = base_cost_t[vertex] * val_t[vertex];
        }

        // pushes to children
        if (left != right) {
            if (pbase) {
                pending_base[2 * vertex] += pending_base[vertex];
                pending_base[2 * vertex + 1] += pending_base[vertex];
            }
            if (pval) {
                pending_val[2 * vertex] = pending_val[2 * vertex + 1] = pending_val[vertex];
            }
        }

        // clears pending updates from this node
        pending_base[vertex] = 0;
        pending_val[vertex] = -1;
    }

    ll _query(int vertex, int left, int right, int query_left, int query_right) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return total_cost_t[vertex];
        }

        int mid = left + (right - left) / 2;
        return _query(2 * vertex, left, mid, query_left, query_right) +
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right);
    }

    ll query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }

    void _update_value(int v, int l, int r, int ql, int qr, ll newval) {
        push_down(v, l, r);

        if (r < ql || qr < l) {
            return;
        }
        if (ql <= l && r <= qr) {
            pending_val[v] = newval;
            // cout << "just set pending_val[" << v << "] = " << newval << endl;
            push_down(v, l, r);
            return;
        }

        int m = (l + r) / 2;
        _update_value(2 * v, l, m, ql, qr, newval);
        _update_value(2 * v + 1, m + 1, r, ql, qr, newval);
        combine(v);
    }

    void _update_sum(int v, int l, int r, int ql, int qr, ll adding) {
        push_down(v, l, r);

        if (r < ql || qr < l) {
            return;
        }
        if (ql <= l && r <= qr) {
            pending_base[v] += adding;
            push_down(v, l, r);
            return;
        }

        int m = (l + r) / 2;
        _update_sum(2 * v, l, m, ql, qr, adding);
        _update_sum(2 * v + 1, m + 1, r, ql, qr, adding);
        combine(v);
    }

    void update(int left, int right, int tp, ll val) {
        // cout << "in update(), tp = " << tp << ", and val = " << val << endl;
        if (tp == 0) {
            // setting value
            _update_value(1, 0, n - 1, left, right, val);
            // cout << "updated value of [" << left << ", " << right << "] to " << val << endl;
        } else {
            // adding to sum
            _update_sum(1, 0, n - 1, left, right, val);
            // cout << "updated sum of [" << left << ", " << right << "] to add " << val << endl;
        }
    }

    long long get(int idx, string arr) {
        int v = 1, l = 0, r = n - 1;
        while (l != r) {
            int m = (l + r) / 2;
            if (idx > m) {
                v = 2 * v + 1;
                l = m + 1;
            } else {
                v = 2 * v;
                r = m;
            }
        }
        
        if (arr == "val") {
            return val_t[v];
        } else if (arr == "base cost") {
            return base_cost_t[v];
        } else {
            return total_cost_t[v];
        }
    }

private:
    int n;
    std::vector<ll> val_t, pending_val, base_cost_t, pending_base, total_cost_t;  // t stands for tree, meaning it's a length 4*n array instead of length n
    std::vector<ll> arr;
};

void solve() {
    /*
    after this and https://codeforces.com/problemset/problem/1799/D2, i think i can
    confidently say that debugging lazy segment tree problems gives me more brain damage
    than any other activity in the history of humanity
    */

    int n, m, q;
    cin >> n >> m >> q;
    vector<int> x(m), v(m);
    cin >> x >> v;
    map<int, int> harbors;
    for (int i = 0; i < m; ++i) {
        --x[i];
        harbors[x[i]] = v[i];
    }

    vector<ll> val(n, -1), base_cost(n, 0);
    for (int i = 0; i < n; ++i) {
        auto it = harbors.lower_bound(i);
        if (it->first != i) {
            base_cost[i] = it->first - i;
            auto before = it;
            --before;
            val[i] = before->second;
        }
    }
    // cout << "base_cost = " << base_cost << ", val = " << val << endl;

    Lazy st(val, base_cost);
    auto push_all = [&]() {
        for (int i = 0; i < n; ++i) st.query(i, i);
    };
    auto print = [&](string arr) {
        cout << arr << " = ";
        push_all();
        for (int i = 0; i < n; ++i) {
            cout << st.get(i, arr) << " ";
        }
        cout << endl;
    };
    auto print_all = [&]() {
        print("val");
        print("base cost");
        print("total cost");
    };
    // print_all();
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int xi, vi;
            cin >> xi >> vi;
            --xi;

            auto after = harbors.lower_bound(xi);
            auto before = after; --before;

            // handles left interval (includes x_i)
            int l = before->first + 1, r = xi;
            ll decreasing = after->first - xi;
            // cout << "applying a decrease of " << decreasing << " to [" << l << ", " << r << "]\n";
            st.update(l, r, 1, -decreasing);

            // handles right interval
            if (xi != after->first - 1) {
                l = xi + 1;
                r = after->first - 1;
                st.update(l, r, 0, vi);
            }

            harbors[xi] = vi;  // how did missing this line not get caught until test case #10, type-2 query #3001?
            // cout << "added harbor to " << xi << " with value " << vi << ",\n";
            // print_all();
        } else {
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << st.query(l, r) << "\n";
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
