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
    Lazy(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 1e9);
        pending.resize(4 * n);
        std::fill(pending.begin(), pending.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            tree[v] = -l;  // specific to this problem
            return;
        }

        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
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
        tree[vertex] = min(tree[2 * vertex], tree[2 * vertex + 1]);
    }

    void update(int left, int right, long long val) {
        _update(1, 0, n - 1, left, right, val);
    }

    int find_leftmost_neg() {
        int v = 1, l = 0, r = n - 1;
        push_down(v, l, r);
        if (tree[v] >= 0) {
            // cout << "here\n";
            return n;  // the n of the tree, not of the problem
        }

        while (l != r) {
            int m = (l + r) / 2;
            push_down(2 * v, l, m);  // atp just push down everywhere bruh
            push_down(2 * v + 1, m + 1, r);
            if (tree[2 * v] < 0) {
                v = 2 * v;
                r = m;
            } else {
                v = 2 * v + 1;
                l = m + 1;
            }
        }
        assert(tree[v] < 0);
        return l;
    }

    int find_longest_nonneg_prefix() {
        return find_leftmost_neg() - 1;
    }

    int n;
    std::vector<long long> tree, pending;
    std::vector<int> arr;
};

void solve() {
    /*
    key ideas:
    - if you have an array and you want to make a segment tree over the prefix sum array for that array,
    then either:
        - you can make the prefix sum array then build the segtree, or
        - you can, for each element, lazily range-add it to all elements to the right
            - this way, modifying an element and getting an updated prefix sum array (implicitly, through
            the tree) can be done in O(log n)
    - x < y ==> x - y < 0
        - why is this useful? across all y, we can use the *same comparison value* of 0. basically,
        it makes all the equalities normalized.
        - if we don't do this transformation, then doing a range min of x won't tell us if x < y is satisfied
        for any y.
        - if we do this transformation, then doing a range min of (x - y) will tell us if (x - y) < 0 for
        any y, because we can just check the minimum value against that uniform comparison threshold: 0.
    - if we want to see if any among a set of values is < 0, take the minimum among all of them and check
    if it's < 0. more generally, if we want to see if any object in a set meets some condition, then check
    if the one that's most likely to meet it meets it.
    - we want to find the smallest p such that cnt_left(p) < p.
        - if we only do point-updates, then for each node, we can have a "condition_satisfied" flag, which
        says if the condition was satisfied anywhere within the segment. whenever we do a point update, we
        will update the leaf, then when walking back up the tree, after the children have been updated, we
        can OR the children's values together.
        - however, since we do range-updates, we'd actually have to go and update every leaf, which is no longer
        lazy propagation. that's why we store the range-minimum instead: that can be done efficiently, and
        then the "condition to satisfy" is just that range_min is less than 0.
    */

    int ac, dr, n;
    cin >> ac >> dr >> n;
    vector<int> a(n), d(n);
    cin >> a >> d;

    Lazy cnt_before(n + 1);  // count of people below a given value of p
    for (int i = 0; i < n; ++i) {
        int p_needed = max(0, a[i] - ac) + max(0, d[i] - dr);
        if (p_needed < n) {
            cnt_before.update(p_needed + 1, n, 1);
        }
    }

    int m;
    cin >> m;
    while (m--) {
        // reads in new values
        int k, na, nd;
        cin >> k >> na >> nd;
        --k;

        // removes contribution of old values from segtree
        // "contribution" (n.) - something given from x to y
        int p_needed_before = max(0, a[k] - ac) + max(0, d[k] - dr);
        if (p_needed_before < n) {
            cnt_before.update(p_needed_before + 1, n, -1);
        }

        // adds contribution of new values to segtree
        a[k] = na;
        d[k] = nd;
        int p_needed_after = max(0, a[k] - ac) + max(0, d[k] - dr);
        if (p_needed_after < n) {
            cnt_before.update(p_needed_after + 1, n, 1);
        }
        // cout << cnt_before.tree << endl;

        // gets answer after this change
        int ans = cnt_before.find_longest_nonneg_prefix();
        cout << ans << "\n";
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
