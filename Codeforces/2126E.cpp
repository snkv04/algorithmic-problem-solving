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

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

void solve() {
    int n;
    cin >> n;

    vector<ll> p(n), s(n);
    for (int i = 0; i < 2*n; ++i) {
        if (i < n) cin >> p[i];
        else cin >> s[i%n];
    }

    for (int i = 1; i < n; ++i) {
        if (p[i-1] % p[i] != 0) {
            cout << "NO\n";
            return;
        }
    }
    for (int i = n-2; i >= 0; --i) {
        if (s[i+1] % s[i] != 0) {
            cout << "NO\n";
            return;
        }
    }

    vector<ll> a = p;
    for (int i = n-1; i >= 0; --i) {
        a[i] = lcm(a[i], s[i]);
    }

    bool works = true;
    ll pref = 0;
    for (int i = 0; i < n; ++i) {
        pref = gcd(pref, a[i]);
        if (pref != p[i]) {
            works = false;
            break;
        }
    }
    ll suf = 0;
    for (int i = n-1; i >= 0; --i) {
        suf = gcd(suf, a[i]);
        if (suf != s[i]) {
            works = false;
            break;
        }
    }

    cout << (works ? "YES" : "NO") << '\n';
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
