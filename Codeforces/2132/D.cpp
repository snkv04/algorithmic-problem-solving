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

ll getnumdigits(ll n) {
    ll len = 1, mult = 1, digits = 0;
    while (n) {
        ll numintegers;
        if (n >= 9 * mult) {
            numintegers = 9 * mult;
        } else {
            numintegers = n;
        }
        digits += numintegers * len;
        n -= numintegers;
        ++len;
        mult *= 10;
    }
    return digits;
}

ll getmaxfull(ll numdigits) {
    ll l = 0, r = 1e16, ans = -1;
    while (l <= r) {
        ll m = (l + r) / 2;
        ll digits = getnumdigits(m);
        if (digits < numdigits) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans;
}

void solve() {
    ll k;
    cin >> k;
    if (k <= 9) {
        cout << (k * (k + 1) / 2) << "\n";
        return;
    }

    ll x = getmaxfull(k);
    string s = to_string(x);
    vector<ll> pow10(17, 1); for (int i = 1; i <= 16; ++i) pow10[i] = pow10[i-1] * 10;
    ll numloops = 0;
    ll ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        int place = s.size() - 1 - i;
        ll digit = s[i] - '0';

        ans += numloops * 45;
        if (place) numloops += digit * pow10[place-1];

        for (int d = 0; d <= digit; ++d) {
            if (d == digit) {
                ans += d * (1 + (x % pow10[place]));
            } else {
                ans += d * pow10[place];
            }
        }
    }

    ll already = getnumdigits(x);
    k -= already;
    ++x;
    stack<int> stk; while (x) { stk.push(x % 10); x /= 10; }
    while (k--) { ans += stk.top(); stk.pop(); }
    cout << ans << endl;
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
