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

private:
    int n;
    std::vector<long long> tree;
    std::vector<int> arr;
};

void solve() {
    /*
    - when can you use this line-sweep algorithm/query reordering idea?
        - basically the 3 things we want are:
            - (1) the queries must be answerable offline (duh)
            - (2) if we assume that all queries have their left value as equal,
            then the problem becomes easily solvable
            - (3) it is easy to move that "left" value (the "line") over from a position to the
            next/previous position
        - examples:
            - in this problem (https://cses.fi/problemset/task/1734/):
                - we have multiple indices for each value
                - if the left bound for all queries was fixed, then we know we can easily just use
                the leftmost index for each value, and then apply a segtree
                - so, we move the left line from left to right
            - Doorway (https://codeforces.com/problemset/problem/2181/D):
                - we have multiple possible windows at each level, and we can only pick one
                - if we know that there is some x-value such that all windows' right bounds must
                be >= that x value, and that there is some window whose right bound is == that x-value,
                then:
                    - the intersection of windows is guaranteed to occur <= that x-value, or not at all
                    - for each level, we want to take the leftmost window whose right bound is >= x
                - so, we can sweep that line from right to left, and for a given line, for each layer,
                we take the best window
            - Yunli's Subarray Queries (hard version) (https://codeforces.com/problemset/problem/2009/G2):
                - if we know that all queries have the same left bound, then we can construct the prefix-minimum
                array starting at that left bound and use a segtree (or some alternative method, like binary
                search)
                - so, we sweep the left bound from left to right
    */

    // reads in input
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    // gets indices of each value, and places first index of each into a segment tree
    map<int, queue<int>> indices;
    for (int i = 0; i < n; ++i) indices[a[i]].push(i);
    SegmentTree st(n);
    for (auto [k, v] : indices) st.update(v.front(), 1);

    // sorts queries
    vector<array<int, 3>> queries;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        queries.push_back({l - 1, r - 1, i});
    }
    sort(queries.begin(), queries.end());

    // walks through queries, updating the segment tree as necessary
    vector<int> ans(q);
    int last = 0;
    for (auto [l, r, i] : queries) {
        for (int j = last; j < l; ++j) {
            int val = a[j];
            st.update(indices[val].front(), 0);  // unnecessary
            indices[val].pop();
            if (indices[val].size()) st.update(indices[val].front(), 1);
        }
        ans[i] = st.query(l, r);
        last = l;
    }

    // outputs answers to queries in correct order
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << " ";
    }
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
