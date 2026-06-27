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

    SegmentTree(const std::vector<pair<int, int>> &arr) : n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        build(1, 0, n - 1, arr);
    }

    void build(int vertex, int left, int right, const vector<pair<int, int>> &arr) {
        if (left == right) {
            tree[vertex] = arr[left].second;
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid, arr);
        build(2 * vertex + 1, mid + 1, right, arr);
        tree[vertex] = min(tree[2 * vertex], tree[2 * vertex + 1]);
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

    int query(int left, int right) {
        if (left > min(right, n - 1)) return 1e9;

        return _query(1, 0, n - 1, left, right);
    }

private:
    int n;
    std::vector<long long> tree;
};

void solve() {
    int n;
    cin >> n;
    vector<int> p(n), c(n);
    cin >> p >> c;

    int m;
    cin >> m;
    vector<int> tp(m), tc(m), d(m);
    cin >> tp >> tc >> d;

    vector<pair<int, int>> c_by_p, p_by_c, sum_by_p;
    for (int i = 0; i < n; ++i) {
        c_by_p.push_back({p[i], c[i]});
        p_by_c.push_back({c[i], p[i]});
        sum_by_p.push_back({p[i], p[i] + c[i]});
    }
    sort(c_by_p.begin(), c_by_p.end());
    sort(p_by_c.begin(), p_by_c.end());
    sort(sum_by_p.begin(), sum_by_p.end());
    SegmentTree c_by_p_st(c_by_p), p_by_c_st(p_by_c), sum_by_p_st(sum_by_p);
    // cout << "c by p = " << c_by_p << endl;
    // cout << "p by c = " << p_by_c << endl;
    // cout << "sum by p = " << sum_by_p << endl;

    auto get_idx = [](const vector<pair<int, int>> &arr, int threshold) {
        int result = arr.size(), l = 0, r = arr.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (arr[m].first >= threshold) {
                result = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return result;
    };
    auto get_cost = [](int p_or_c, int t, int d) -> int {
        if (p_or_c == 1e9) return 1e9;  // special case for a value we want to discard; we want to propagate a value of infinity

        if (p_or_c < t) return 0;
        else if (p_or_c < t + d) return p_or_c;
        else return t + d;
    };

    for (int j = 0; j < m; ++j) {
        int tpj = tp[j], tcj = tc[j], dj = d[j];
        int pidx1 = get_idx(c_by_p, tpj), pidx2 = get_idx(c_by_p, tpj + dj);
        int cidx1 = get_idx(p_by_c, tcj), cidx2 = get_idx(p_by_c, tcj + dj);
        // cout << "tpj = " << tpj << ", pidx1 = " << pidx1 << endl;
        // cout << "tpj + dj = " << tpj + dj << ", pidx2 = " << pidx2 << endl;
        // cout << "tcj = " << tcj << ", cidx1 = " << cidx1 << endl;
        // cout << "tcj + dj = " << tcj + dj << ", cidx2 = " << cidx2 << endl;
        std::initializer_list<int> il = {
            0 + get_cost(c_by_p_st.query(0, pidx1 - 1), tcj, dj),
            tpj + dj + get_cost(c_by_p_st.query(pidx2, n - 1), tcj, dj),
            sum_by_p_st.query(pidx1, pidx2 - 1),
            0 + get_cost(p_by_c_st.query(0, cidx1 - 1), tpj, dj),
            tcj + dj + get_cost(p_by_c_st.query(cidx2, n - 1), tpj, dj)
        };
        // vector<int> v(il);
        // cout << "v = " << v << endl;
        int ans = min(il);
        cout << ans << endl;

        // int ans = 1e9;
        // for (int i = 0; i < n; ++i) {
        //     int cost = get_cost(p[i], tpj, dj) + get_cost(c[i], tcj, dj);
        //     cout << "cost for j=" << j << ", i=" << i << " is " << cost << endl;
        //     ans = min(ans, cost);
        // }
        // cout << ans << endl;
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
