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
    - problem:
        - given an array and a subarray defined by (x, l, r), the value of the subarray [a[l], ..., a[r]]
        starts at 1, doubles for every instance of x, and halves for every instance of anything that's not x
        - pick (x, l, r) to maximize the value of the subarray [a[l], ..., a[r]]
    - solution:
        - we want to basically pick a subarray and an element x such that the value of (frequency of x within
        the subarray minus frequency of anything non-x within the subarray) is maximized
        - to do this, simply iterate over r, and for each r, look over all l and pick the l that maximizes
        the target quantity; that's the main idea, but there are two simplifications:
            - note that we want to choose l and r such that a[l] == a[r] == x, because if that's not the case,
            we can tighten the subarray and increase our value; as a result, for a given r, the value of x
            is fixed
            - since the quantity we care about can be split up into an "r" portion and an "l" portion, we can
            search over all "l" (for a fixed "x") in O(1) by keeping track of the best value for the "l" portion
    - details:
        - the task of "maximize the product, where we double on preferable element, and halve on non-preferred element"
        can be converted into "maximize count of preferred elements minus count of non-preferred elements",
        and the whole process of counting can simply be converted into "add +1 on preferred element, and
        add -1 on non-preferred element; now, maximize the sum"
            - this simple conversion of "counting" into "using +1 and -1" is analogous to the standard idea of
            indicator variables
        - we can get an O(n) complexity in a couple of ways: either we iterate through values in the array,
        and for each value x, we only process the indices i such that a[i]=x (so then the sum of indices that
        we process is equal to n), or we iterate through all indices in order at once so we aren't just
        looking at indices with the same value in an inner loop
            - the latter solution is this one
            - the former solution is what the kadane's solution and segment tree solution do
        - in general, there are 2 ways of processing a sequence of elements while keeping track of some record-keeping
        variables: process the element before updating the record-keeping variable, and update the record-keeping variable
        before processing the element
    */

    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;
    
    /*
    - we want to maximize   count(l, r) - (length - count(l, r)) =
                            2 * count(l, r) - length =
                            l - r - 1 + 2 * (pref[r] - pref[l-1]) =
                            l - r - 1 + 2 * (pref[r] - (pref[l] - 1)) =
                            (l - 2 * pref[l] + 1) + (2 * pref[r] - r)    */
    map<int, int> pref;  // maps a value x to its prefix count for efficient subarray frequency counting
    map<int, pair<int, int>> best;  // maps a value x to its optimal (l, l - 2*pref[l] + 1)
    int ans = -1, ansx = -1, ansl = -1, ansr = -1;
    for (int i = 0; i < n; ++i) {
        int xi = x[i];

        // two ways of implementation:
        // 
        // (1) assume `pref` and `best` only refer to indices strictly < i, and break into two cases:
        // i holds the first instance of x[i], and i doesn't hold the first instance of x[i]
        // (2) assume `pref` and `best` refer to indices <= i, and just enforce this before processing
        // index i, so then no breaking into cases is needed when processing index i
        // 
        // the second way is more intuitive, because it is more general in the sense that it deals with
        // all indices <= i in the same way; either one works, though, so don't overcomplicate it, and
        // in the future just go with something that works (i.e., break into cases if clearer to understand)
        // instead of trying to make it clean before even getting something working

        auto assume_strictly_left = [&]() {
            // break into two cases: first instance of x (so there's nothing strictly left),
            // and not first instance of x (so there is somethign strictly left)
            if (pref.find(xi) == pref.end()) {
                pref[xi] = 1;
                best[xi] = make_pair(i, i - 1);  // make_pair(i, i - 2 * pref[x] + 1);

                // check if this (l, r) is good enough to be the new answer
                if (1 > ans) {
                    ans = 1;
                    ansx = xi;
                    ansl = ansr = i;
                }
            } else {
                // find the best "l portion" across all l
                int right = 2 * (pref[xi] + 1) - i;
                int val = best[xi].second + right;

                // check if this (l, r) is good enough to be the new answer
                if (val > ans) {
                    ans = val;
                    ansx = xi;
                    ansl = best[xi].first;
                    ansr = i;
                }

                // update pref[x] and best[x]
                pref[xi] += 1;
                int left = i - 2 * pref[xi] + 1;
                if (left > best[xi].second) {
                    best[xi] = make_pair(i, left);
                }
            }
        };

        auto assume_at_or_left = [&]() {
            // update pref and best
            if (pref.find(xi) == pref.end()) {
                pref[xi] = 1;
                best[xi] = make_pair(i, i - 1);
            } else {
                pref[xi] += 1;
                int left = i - 2 * pref[xi] + 1;
                if (left > best[xi].second) {
                    best[xi] = make_pair(i, left);
                }
            }

            // find the best "l portion" across all l
            int right = 2 * pref[xi] - i;
            int val = best[xi].second + right;

            // check if this (l, r) is good enough to be the new answer
            if (val > ans) {
                ans = val;
                ansx = xi;
                ansl = best[xi].first;
                ansr = i;
            }
        };

        // assume_strictly_left();
        assume_at_or_left();
    }
    cout << ansx << ' ' << (ansl + 1) << ' ' << (ansr + 1) << '\n';
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
