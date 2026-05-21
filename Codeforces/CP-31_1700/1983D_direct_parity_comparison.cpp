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

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &elem : v) is >> elem;
    return is;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;

public:
    SegmentTree(int n) : n(n), t(4 * n, 0) {}

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

int inversion_parity(vector<int> &v) {
    // sorts elements to get indices in increasing order keyed on array value
    vector<pair<int, int>> sorted;
    int n = v.size();
    for (int i = 0; i < n; ++i) sorted.push_back(make_pair(i, v[i]));
    sort(sorted.begin(), sorted.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second > b.second;
    });

    // counts inversions using segment tree
    ll inversions = 0;
    SegmentTree st(n);
    for (int i = 0; i < n; ++i) {
        int idx = sorted[i].first;
        inversions += st.query(0, idx);
        st.update(idx, 1);
    }
    return inversions % 2;
}

void solve() {
    // reads in input
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    // checks inversion parity equality
    int parity_a = inversion_parity(a), parity_b = inversion_parity(b);
    bool same_parity = parity_a == parity_b;

    // just checks that A and B hold the same elements
    bool same_multiset = true;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < n; ++i) if (a[i] != b[i]) { same_multiset = false; break; }

    // outputs final answer
    cout << ((same_multiset && same_parity) ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
