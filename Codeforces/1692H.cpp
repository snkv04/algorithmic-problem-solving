#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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

    void _update(int v, int l, int r, int idx, ll val) {
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

    void update(int idx, ll val) {
        _update(1, 0, n - 1, idx, val);
    }
};

struct RollingHash {
private:
    vector<ll> P = {998244353, 999999937};
    vector<ll> MOD = {1000000007, 1000000009};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling;
    string s;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[i][t] = (rolling[i - 1][t] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

    void _build_powers() {
        PPOW = vector<vector<ll>>(n + 1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                PPOW[i][t] = (PPOW[i - 1][t] * P[t]) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
        _build_powers();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        array<ll, 2> result;
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

struct DSU {
private:
    int n;
    vector<int> parent, size;

public:
    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        size = vector<int>(n, 1);
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            if (size[c] >= size[d]) {
                parent[d] = c;
                size[c] += size[d];
            } else {
                parent[c] = d;
                size[d] += size[c];
            }
        }
    }
};

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

struct Frac {
    ll num, denom;

    Frac(ll n, ll d) : num(n), denom(d) {
        reduce();
    }

    Frac(ll x) : num(x), denom(1) {}

    bool operator<(const Frac &other) const {
        ll d = lcm(denom, other.denom);
        ll n1 = num * (d / denom), n2 = other.num * (d / other.denom);
        return n1 < n2;
    }

    bool operator==(const Frac &other) const {
        Frac f1 = *this, f2 = other;
        f1.reduce(); f2.reduce();
        return f1.num == f2.num && f1.denom == f2.denom;
    }

    bool operator!=(const Frac &other) const {
        return !((*this) == other);
    }

    bool operator<=(const Frac &other) const {
        return *this < other || *this == other;
    }

    void reduce() {
        ll g = gcd(num, denom);
        num /= g;
        denom /= g;
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

    Frac operator+(const Frac &other) {
        ll d = lcm(denom, other.denom);
        ll n1 = num * (d / denom), n2 = other.num * (d / other.denom);
        Frac result(n1 + n2, d);
        result.reduce();
        return result;
    }

    Frac operator-(const Frac &other) {
        return (*this) + (Frac(-1) * other);
    }

    Frac operator*(const Frac &other) {
        Frac result(num * other.num, denom * other.denom);
        result.reduce();
        return result;
    }

    Frac operator/(const Frac &other) {
        Frac recip(other.denom, other.num);
        return (*this) * recip;
    }

    ll sign() {
        reduce();
        if (num == 0) return 0;
        else if (num > 0) return 1;
        else return -1;
    }
};

void solve() {
    /*
    - we can reformulate the thing we are trying to maximize (over all segments [l, r]) as the count of the
    element we care about minus the count of the elements we don't care about in the segment. why? each of
    those two types cancel each other out, so we just want the maximum difference. also, it's clear that we
    don't want a segment where x[l] != x[r], because we can shrink the interval and get better results. then,
    we can just separate out the thing we are trying to maximize into a left and right expression, and for each
    value of right, pick the left bound that maximizes the left part of the quantity.

    generalizable ideas for the future:
    - if we are trying to maximize something and we need to keep track of the values of some other variables at
    the time when that thing was maximized, then we can store them all together. that's obvious, but it's interesting
    in this problem because we store the best left quantity and the left bound corresponding to that left quantity
    as values in a map where we are keying on x[i].
    */

    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;
    
    /*
    - we want to maximize   count[l] - (length - count[l]) =
                            2 * count[l] - length =
                            l - r - 1 + 2 * (pref[r] - pref[l-1]) =
                            l - r - 1 + 2 * (pref[r] - (pref[l] - 1)) =
                            (l - 2 * pref[l] + 1) + (2 * pref[r] - r)
    */
    map<int, pair<int, int>> bestl;
    map<int, int> pref;
    int maxtotal = 1, ansdie = x[0], ansl = 0, ansr = 0;
    for (int i = 0; i < n; ++i) {
        int xi = x[i];
        if (bestl.find(xi) == bestl.end()) {
            pref[xi] = 1;
            bestl[xi] = make_pair(i, i - 1);
        } else {
            pref[xi] += 1;
            int best = (2 * pref[xi] - i) + bestl[xi].second;
            // cout << "i = " << i << ", best = " << best << ", maxtotal = " << maxtotal << endl;
            if (best > maxtotal) {
                maxtotal = best;
                ansdie = xi;
                ansl = bestl[xi].first;
                ansr = i;
            }

            int leftpart = i - 2 * pref[x[i]] + 1; // the left-side quantity we want to save the best of, for each x[i]
            if (leftpart > bestl[xi].second) {
                bestl[xi] = make_pair(i, leftpart);
            }
        }
    }
    cout << ansdie << ' ' << ansl + 1 << ' ' << ansr + 1 << '\n';
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
