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
        Frac flipped(other.denom, other.num);
        return (*this) * flipped;
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
    generalizable ideas for the future:
    - when using DP to move from some state to some other state, check to see if the "from" state is invalid.
    - if jumping from index i to index j, we are basically skipping over, or "removing", the states in between.
    - why does the category of "segment DP" found in https://codeforces.com/problemset/problem/1826/D or
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/ not work here? in those problems,
    we keep track of the current index i and the number of operations k as a state, and make the decision to either
    start a new segment or continue the previous segment, so that for a given state, mem[i][k] is equal to the
    <optimal value> of using k operations AT OR BEfORE index i. in this problem, we similarly keep track of index
    and operation count, so that mem[i][j] is the <optimal value> of using k operations AT OR BEFORE index i. however,
    in the previous problem, we could certainly iterate over all the points at which to perform the (k-1)th operation
    across indices < i (though that would be too slow, so we don't), but we don't need to because EVEN THOUGH the place
    where the (k-1)th operation took place is important for the calculation of the DP values for mem[i][k], we don't
    need to know where it happened if we just want to set mem[i][k] = max(mem[i-1][k], some_val + mem[i-1][k-1]).
    in this problem, we cannot just do that, because knowing WHERE the "segment" starts from (where we are "jumping"
    from), as well as its length, is important to calculate the DP value for mem[i][j]. so, we iterate over all places
    to start the segment.
        - one side note: it is probably more intuitive to iterate over i backwards instead of forwards. in other words,
        if a sign at point i is used (meaning we travel at its speed) from point i to point j > i, then we can calculate
        the cost of the subproblem for the interval [i, n] by using the subproblem for [j, n], and this is more intuitive
        because moving from j to i requires "information" (the speed limit) from point i, not point j. this more clearly
        falls into the pattern of "use subproblems then tack on the last operation" that basically every DP problem falls
        into, because when moving from a previous subproblem to a current subproblem, we use information sourced from the
        current subproblem (which is also the reason why the solution for https://leetcode.com/problems/dungeon-game/
        is what it is).
        - however, that change wouldn't really resolve the issue of "not knowing where the segments starts" (even though
        it would start at the current position i and end at some later position j). why? because we still need to know
        the LENGTH of the segment over which we make the jump.
    */

    int n, k, l;
    cin >> n >> l >> k;
    vector<int> d(n), a(n);
    cin >> d >> a;
    d.push_back(l);
    vector<int> dist(n);
    for (int i = 0; i < n; ++i) dist[i] = d[i+1] - d[i];

    // mem[i][j] = min cost to get to point i, using exactly j removals
    vector<vector<int>> mem(n+1, vector<int>(k+1, 2e9));
    mem[0][0] = 0;
    for (int i = 1; i <= n; ++i) mem[i][0] = mem[i-1][0] + a[i-1] * dist[i-1];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            for (int r = 0; r <= k && i-r-1 >= 0 && r <= j; ++r) { // r = removed
                int from = i - r - 1;
                if (mem[from][j-r] != 2e9)
                    mem[i][j] = min(mem[i][j], mem[from][j-r] + (d[i] - d[from]) * a[from]);
            }
        }
    }

    int ans = 2e9;
    for (int i = 0; i <= k; ++i) ans = min(ans, mem[n][i]);
    cout << ans << endl;
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
