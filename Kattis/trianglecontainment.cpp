#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;

public:
    SegmentTree(int n) {
        this->n = n;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

void solve() {
    int n; ll x;
    cin >> n >> x;

    vector<pair<int, pair<ll, ll>>> points(n);
    vector<ll> val(n);
    for (int i = 0; i < n; ++i) {
        ll x, y, v;
        cin >> x >> y >> v;
        points[i] = make_pair(i, make_pair(x, y));
        val[i] = v;
    }
    
    vector<pair<int, pair<ll, ll>>> by_l = points, by_r = points;
    sort(by_l.begin(), by_l.end(), [&x](const pair<int, pair<ll, ll>> &a, const pair<int, pair<ll, ll>> &b) {
        pair<ll, ll> c = a.second, d = b.second;
        return c.first * d.second - c.second * d.first > 0;
    });
    sort(by_r.begin(), by_r.end(), [&x](const pair<int, pair<ll, ll>> &a, const pair<int, pair<ll, ll>> &b) {
        pair<ll, ll> c = make_pair(a.second.first - x, a.second.second), d = make_pair(b.second.first - x, b.second.second);
        return c.first * d.second - c.second * d.first < 0;
    });
    // cout << "by_l: ";
    // for (int i = 0; i < n; ++i) {
    //     cout << by_l[i] << " ";
    // }
    // cout << endl << "by_r: ";
    // for (int i = 0; i < n; ++i) {
    //     cout << by_r[i] << " ";
    // }
    // cout << endl;

    map<int, int> to_by_l;
    for (int i = 0; i < n; ++i) to_by_l[by_l[i].first] = i;

    SegmentTree st(n);
    vector<ll> ans(n);
    for (int i = 0; i < n; ++i) {
        int idx = by_r[i].first;
        int by_l_idx = to_by_l[idx];
        ans[idx] = st.query(0, by_l_idx);
        st.update(by_l_idx, val[idx]);
    }
    for (ll num : ans) cout << num << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
