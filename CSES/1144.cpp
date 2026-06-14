#include <bits/stdc++.h>
using namespace std;
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

struct SegmentTree {
    SegmentTree(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
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
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int idx, int val) {
        if (left == right) {
            tree[vertex] += val;
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

private:
    int n;
    std::vector<int> tree;
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    cin >> v;
    vector<array<int, 3>> queries(q);
    for (int i = 0; i < q; ++i) {
        char c;
        cin >> c;
        cin >> queries[i][1] >> queries[i][2];
        if (c == '!') { queries[i][0] = 1; queries[i][1] -= 1; }
        else queries[i][0] = 2;
    }

    // simply choosing to not coordinate-compress the bounds of the type-? queries, and instead going for
    // the compressed values of the floor/ceiling elements if those bounds don't already exist in the map,
    // made this solution go from TLE to AC
    map<int, int> c;
    for (int value : v) c[value] = -1;
    for (auto [t, a, b] : queries) {
        if (t == 1) {
            c[b] = -1;
        }
    }
    int timer = 0;
    for (auto &[k, v] : c) v = timer++;

    SegmentTree st(timer);
    for (int value : v) st.update(c[value], 1);
    for (auto [t, a, b] : queries) {
        if (t == 1) {
            int old_val = v[a];
            st.update(c[old_val], -1);
            v[a] = b;
            st.update(c[b], 1);
        } else {
            auto it = c.lower_bound(a);
            if (it == c.end()) {
                cout << "0 ";
                continue;
            }
            int l = it->second;
            it = c.upper_bound(b);
            if (it == c.begin()) {
                cout << "0 ";
                continue;
            }
            --it;
            int r = it->second;

            if (l <= r) {
                cout << st.query(l, r) << " ";
            } else {
                cout << "0 ";
            }
        }
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
