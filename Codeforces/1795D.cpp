#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

ll pow(ll base, ll exp, ll mod) {
    if (exp == 0) return 1;
    ll result = pow(base, exp / 2, mod);
    result *= result;
    result %= mod;
    if (exp % 2) {
        result *= base;
        result %= mod;
    }
    return result;
}

ll mod_inv(ll num, ll mod) {
    return pow(num, mod - 2, mod);
}

ll div(ll a, ll b, ll mod) {
    return (a * mod_inv(b, mod)) % mod;
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

void solve() {
    int n;
    cin >> n;

    vector<ll> fact(n/3+1, 1);
    for (int i = 1; i <= n/3; ++i) {
        fact[i] = fact[i-1] * i;
        fact[i] %= MOD;
    }

    ll ans = fact[n/3];
    ans = div(ans, fact[n/6], MOD);
    ans = div(ans, fact[n/6], MOD);
    // print_container(fact);
    // cout << "ans = " << ans << "\n";
    
    while (n) {
        n -= 3;
        vector<int> a(3);
        for (int i = 0; i < 3; ++i) cin >> a[i];
        sort(a.begin(), a.end());
        if (a[0] == a[1] && a[1] == a[2]) {
            ans *= 3;
        } else if (a[0] == a[1]) {
            ans *= 2;
        } else {
            ans *= 1;
        }
        ans %= MOD;
    }
    
    cout << ans << "\n";
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
