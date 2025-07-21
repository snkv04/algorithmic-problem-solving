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
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
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

ll gcd(ll a, ll b) {
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

void solve() {
    int f, b;
    cin >> f >> b;
    vector<ll> fronts(f, 0), backs(b, 0);
    for (int i = 0; i < f; ++i) cin >> fronts[i];
    for (int i = 0; i < b; ++i) cin >> backs[i];

    vector<pair<ll, ll>> pairs;
    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < b; ++j) {
            pairs.push_back(make_pair(fronts[i], backs[j]));
        }
    }
    
    sort(pairs.begin(), pairs.end(), [](pair<ll, ll> &p1, pair<ll, ll> &p2) {
        ll n1 = p1.first, d1 = p1.second, n2 = p2.first, d2 = p2.second;
        ll g1 = gcd(n1, d1), g2 = gcd(n2, d2);
        n1 /= g1; d1 /= g1;
        n2 /= g2; d2 /= g2;

        ll common_denom = d1 * d2 / gcd(d1, d2);
        n1 *= common_denom / d1;
        n2 *= common_denom / d2;
        if (n1 != n2) {
            return n1 < n2;
        } else {
            return p1.first < p2.first;
        }
    });

    for (int i = 0; i < f * b; ++i) {
        cout << "(" << pairs[i].first << "," << pairs[i].second << ")\n";
    }
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
