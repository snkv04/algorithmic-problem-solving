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

enum class UpdateType {
    MULTIPLY, ADD, NONE
};

struct Update {
    UpdateType t;
    ld val;
};

struct Node {
    // the node holds both the tree value and the pending values
    // x holds the node's "tree" value, while a and b hold the node's pending updates (total = ax + b)
    ld x, a, b;
};

struct Lazy {
    Lazy(const std::vector<int> &arr) : n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), Node{0, 1, 0});
        build(1, 0, n - 1, arr);
    }

    void combine(int v, int l, int r) {
        // build a node's value (with no pending updates) based on the child nodes
        int m = (l + r) / 2;
        tree[v] = {tree[2 * v].x + tree[2 * v + 1].x, 1, 0};
    }

    void build(int vertex, int left, int right, const vector<int> &arr) {
        if (left == right) {
            tree[vertex] = {(ld) arr[left], 1, 0};
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid, arr);
        build(2 * vertex + 1, mid + 1, right, arr);
        combine(vertex, left, right);
    }

    void apply(int vertex, const Update &u) {
        // simply take an update and update the "pending" values for the specified node
        if (u.t == UpdateType::MULTIPLY) {
            tree[vertex].a *= u.val;
            tree[vertex].b *= u.val;
        } else {
            tree[vertex].b += u.val;
        }
    }

    void push_down(int vertex, int left, int right) {
        // take pending updates for this node and apply them to the tree value for the node
        ld a = tree[vertex].a, b = tree[vertex].b;
        tree[vertex] = {a * tree[vertex].x + (right - left + 1) * b, 1, 0};

        // then, push pending updates to children nodes
        if (left != right) {
            apply(2 * vertex, Update{UpdateType::MULTIPLY, a});
            apply(2 * vertex, Update{UpdateType::ADD, b});
            apply(2 * vertex + 1, Update{UpdateType::MULTIPLY, a});
            apply(2 * vertex + 1, Update{UpdateType::ADD, b});
        }
    }

    long double _query(int vertex, int left, int right, int query_left, int query_right) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex].x;
        }

        int mid = left + (right - left) / 2;
        return _query(2 * vertex, left, mid, query_left, query_right) +
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right);
    }

    long double query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int query_left, int query_right, Update &u) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            apply(vertex, u);
            push_down(vertex, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        _update(2 * vertex, left, mid, query_left, query_right, u);
        _update(2 * vertex + 1, mid + 1, right, query_left, query_right, u);
        combine(vertex, left, right);
    }

    void update(int left, int right, Update u) {
        _update(1, 0, n - 1, left, right, u);
    }

private:
    int n;
    std::vector<Node> tree;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    Lazy st(a);
    auto print = [&]() {
        vector<ld> v(n);
        for (int i = 0; i < n; ++i) {
            v[i] = st.query(i, i);
        }
        cout << v << endl;
    };
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            --l1; --r1; --l2; --r2;

            ld len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
            ld ev1 = st.query(l1, r1) / len1, ev2 = st.query(l2, r2) / len2;
            st.update(l1, r1, Update{UpdateType::MULTIPLY, (len1 - 1) / len1});
            st.update(l1, r1, Update{UpdateType::ADD, 1.0 / len1 * ev2});
            st.update(l2, r2, Update{UpdateType::MULTIPLY, (len2 - 1) / len2});
            st.update(l2, r2, Update{UpdateType::ADD, 1.0 / len2 * ev1});
        } else {
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << fixed << setprecision(12) << st.query(l, r) << endl;
        }
        // cout << "after query of type " << t << ": ";
        // print();
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
