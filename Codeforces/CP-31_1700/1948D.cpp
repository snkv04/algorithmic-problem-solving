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

bool matching(char a, char b) {
    return !(a != '?' && b != '?' && a != b);
}

void solve_prefix_sums_precomputed() {
    string s;
    cin >> s;
    int n = s.size();

    vector<vector<int>> pref(n, vector<int>(n, 0));
    for (int len = 1; len <= n/2; ++len) {
        for (int i = 0; i < n - len; ++i) {
            pref[len][i] = (i == 0 ? 0 : pref[len][i-1]) + (matching(s[i], s[i+len]) ? 0 : 1);
        }
    }

    // now, order of loops doesn't matter, since prefix sums were already computed correctly
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int halflen = 1; halflen <= n/2 && i + 2 * halflen <= n; ++halflen) {
            if (pref[halflen][i-1+halflen] - (i==0 ? 0 : pref[halflen][i-1]) == 0) {
                ans = max(ans, 2 * halflen);
            }
        }
    }
    cout << ans << '\n';
}

void solve_prefix_sums_on_the_fly() {
    string s;
    cin >> s;
    int n = s.size();

    // only uses a 1D array to keep track of prefix sums, because we go through each length fully separately
    int ans = 0;
    for (int len = 1; len <= n/2; ++len) {
        vector<int> pref(n, 0);
        for (int i = 0; i < n-len; ++i) {
            pref[i] = (i == 0 ? 0 : pref[i-1]) + (matching(s[i], s[i+len]) ? 0 : 1);
        }

        // make sure that when looking over candidates for the final substring, the full substring
        // can fit within the string
        for (int i = 0; i + 2 * len <= n; ++i) {
            if (pref[i+len-1] - (i==0 ? 0 : pref[i-1]) == 0) {
                ans = 2 * len;
                break;
            }
        }
    }
    cout << ans << '\n';
}

void solve_sliding_window() {
    string s;
    cin >> s;
    int n = s.size();

    int ans = 0;
    for (int len = 1; len <= n/2; ++len) {
        int mismatches = 0;
        for (int pos = 0; pos < len; ++pos) {
            mismatches += matching(s[pos], s[pos+len]) ? 0 : 1;
        }
        if (!mismatches) {
            ans = 2 * len;
            continue;
        }

        // i will be the last character of the first half of the substring, but any loop with equivalent
        // logic will be sufficient
        for (int i = len; i + len < n; ++i) {
            // usually, the definition of the for loop (in this case, the first 2 clauses) should eliminate
            // ALL edge cases (such as out of bounds errors) that can happen from ANY indexing operations
            mismatches += (matching(s[i], s[i+len]) ? 0 : 1);
            mismatches -= (matching(s[i-len], s[i]) ? 0 : 1);
            if (!mismatches) {
                ans = 2 * len;
                break;
            }
        }
    }
    cout << ans << '\n';
}

void solve() {
    /*
    - problem:
        - given a string of lowercase Latin letters, where some positions don't have any letter specified
        and simply have a question mark, find the length of the longest substring such that by replacing
        the question marks however we want, our substring has an equal first and second half
    - solution:
        - replace the condition that the first half must equal the second half to an equivalent condition
        that offers itself more easily to prefix sums/sliding windows: if the length of the substring is
        L, then the condition is that each of the first L/2 characters must not mismatch with the character
        that's L/2 chars to the right of it
        - then, instead of iterating first through start position and second through end position/length,
        iterate first through length and then efficiently check each start position using prefix sums
    - details:
        - some problems want you to find the substring/object itself, some only want you to find a property
        of it (like the length); in this problem, we only need a property, but this also happens to be a
        problem where we need to construct the full object
        - explanation of the "equivalent" condition:
            - if the length of our substring that we care about is fixed at L, then we can imagine a new
            array p_{L/2}, where p_{L/2, i} is an indicator variable (which we can think of as an "error
            indicator") equal to:
                - 0, if any of the following are true:
                    - s_i is a '?'
                    - s_{i + L/2} is a '?'
                    - s_i =/= '?', s_{i + L/2} =/= '?', and s_i == s_{i + L/2}
                - 1, if the remaining case is true:
                    - s_i =/= '?', s_{i + L/2} =/= '?', but s_i != s_{i + L/2}
            - now, an equivalent condition is that for all j in [i, i + L/2 - 1], we must have that p_{L/2, j} == 0,
            and checking that p's subarray sum is equal to 0 (good) or is nonzero (bad) is easily doable with a
            prefix sum over p
            - the reason why it "easily offers itself to prefix sums" is that by doing this conceptual transformation,
            we form a new array (p), where there's an associated value for each index, and these values are reusable
            for different subarrays/windows
        - it doesn't matter in which order a matrix is indexed; just do whatever is most intuitive, for ease of coding,
        then change later if needed
        - in the end, this problem transforms into: for a fixed L/2, check if there's a subarray of length L/2 of some
        new "error indicator" array (so all elements are 0 or 1) where the subarray sum is 0
            - alternatively, we can treat it as a "success indicator", and check that the subarray sum is equal to the
            length of the subarray
    */

    // solve_prefix_sums_precomputed();
    // solve_prefix_sums_on_the_fly();
    solve_sliding_window();
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
