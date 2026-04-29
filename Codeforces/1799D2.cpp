#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
constexpr long long INF = 1e15;

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

struct Lazy {
    Lazy(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        pending.resize(4 * n);
        std::fill(pending.begin(), pending.end(), 0);
    }

    Lazy(int n, ll val) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), val);  // works because it's a range-min segtree
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
            // - ALWAYS make sure that this is larger than any value in the "tree" array
            // - if not, then a call to query() might retrieve information from a tree
            // node outside of the requested segment, which obviously corrupts everything
            return 10 * INF;
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

    int n;
    std::vector<long long> tree, pending;
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), cold(k), hot(k);
    cin >> a >> cold >> hot;
    a.insert(a.begin(), 0);
    cold.insert(cold.begin(), 0);
    hot.insert(hot.begin(), 0);

    // on each index of the array, calculate the updates we want, in parallel, then apply them,
    // so they don't impact each other
    Lazy st(k + 1, INF);
    st.update(0, 0, -INF);
    auto get_arr = [&](Lazy &st) {
        vector<ll> vals;
        for (int i = 0; i < st.n; ++i) vals.push_back(st.query(i, i));
        return vals;
    };
    for (int i = 1; i <= n; ++i) {
        /*
        - if we connect a[i] to a[i - 1], then all values will get updated,
        but the amount we add is fixed
        */
        ll adding_if_same_segment = (a[i] == a[i - 1]) ? hot[a[i]] : cold[a[i]];

        /*
        - if we connect a[i] to any other color, it's cold, otherwise hot
        - we only update the case where the prev element is the "last program on white CPU",
        but we require range queries to see all the ways we can connect a[i] to another color
        */
        assert(a[i] >= 1 && a[i] <= k);
        // cout << "i = " << i << ", tree dump = " << st.tree << endl;
        ll best_if_different_segment = min({
            st.query(0, a[i] - 1) + cold[a[i]],
            st.query(a[i], a[i]) + hot[a[i]],
            (a[i] == k) ? INF : (st.query(a[i] + 1, k) + cold[a[i]])
        });

        // now, all updates have already been computed based on querying previous values,
        // so we can safely update
        st.update(0, k, adding_if_same_segment);
        ll curr = st.query(a[i - 1], a[i - 1]);  // only want to point-set, not point-add, so we calculate difference
        ll diff = best_if_different_segment - curr;
        if (diff < 0) {
            st.update(a[i - 1], a[i - 1], diff);
        }
        // cout << "i = " << i << ", mem = " << get_arr(st) << endl;
    }
    
    ll ans = st.query(0, k);
    cout << ans << endl;
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
