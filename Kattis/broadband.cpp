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
        vector<ll> result(2);
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
            parent[d] = c;
            size[c] += size[d];
        }
    }
};

void solve() {
    /*
    - we can separate out the y dimension so that we are doing this "minimizing sum of squares" idea
    in one dimension.
    - sort all of the x-coordinates, and let dp[i][j] be the minimum cost incurred for using the first
    i access points to deal with the first j customer points. base cases are straightforward: 0 customers
    has 0 cost, nonzero customers with no access points is impossible, having more access points than customers
    has 0 cost, and having 1 access point means the cost is the sum of squares of all of those j customers
    from their mean.
    now, to calculate dp[i][j], we iterate over all the possible customers that the last access point can
    handle. for each, we check that for each customer it covers, that access point is the closest access point,
    and for each customer it doesn't cover, that access point isn't the closest one. this can just be done in
    2 checks, but it requires efficiently calculating the mean, as well as keeping track of where the previous
    access point is.
    that last idea is why we keep track of both dp[i][j] (the cost) and mean[i][j] (the location needed to place
    access point i that results in that cost).

    generalizable ideas for the future:
    - when keeping track of some dp[i][j], we might also want to keep track of some additional information of how
    we got that dp[i][j] (such as the location of some object that resulted in the cost of dp[i][j]), as it may
    be needed when calculating dp[i][j] and looking back on some previous values, like dp[i-1][j-1].
    - minimum sum of squared distances equals sum of squares minus (square of sum divided by count).
    - when reading in the initial values, we can just place a buffer on the left, so that everything is 1-indexed.
    this is especially helpful to avoid getting confused when using these values to calculate DP states' values.
    - we can keep a prefix sum of squares. is obvious, but useful to remember.
    - 2000*2000*100 operations is actually possible if each of those operations has a non-volatile O(1) complexity
    (non-volatile as in doesn't require some sketchy amortized O(1) operation like hashing).
    */

    int m, n, k, s;
    cin >> m >> n >> k >> s;
    n += m;
    vector<ld> x(n+1);
    for (int i = 1; i <= n; ++i) cin >> x[i];
    sort(x.begin(), x.end());

    vector<ld> pref(n+1), sqpref(n+1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i-1] + x[i];
        sqpref[i] = sqpref[i-1] + x[i] * x[i];
    }
    auto getsumsqdists = [&](int l, int r) {
        ld sumsq = sqpref[r] - (l == 0 ? 0 : sqpref[l-1]); // unnecessary ternary operator if 1-indexing
        ld sum = pref[r] - (l == 0 ? 0 : pref[l-1]);
        return sumsq - (sum * sum) / (0.0 + r - l + 1);
    };
    auto getmean = [&](int l, int r) {
        ld sum = pref[r] - (l == 0 ? 0 : pref[l-1]);
        return sum / (0.0 + r - l + 1);
    };
    // print_container(pref, "pref = ");
    // print_container(sqpref, "sqpref = ");

    ld ans = s * s * n / 4.0;
    vector<vector<ld>> dp(k+1, vector<ld>(n+1, 1e15));
    vector<vector<ld>> mean(k+1, vector<ld>(n+1, -1));
    for (int i = 0; i <= k; ++i) {
        dp[i][0] = 0;
        mean[i][0] = 0; // no customers present
    }
    for (int j = 1; j <= n; ++j) {
        dp[1][j] = getsumsqdists(1, j);
        mean[1][j] = getmean(1, j);
    }
    for (int i = 2; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j <= i) {
                dp[i][j] = 0;
                continue;
            }

            ld best = 1e9, bestmean = -1;
            for (int prev = i; prev < j; ++prev) {
                ld prevdp = dp[i-1][prev], prevmean = mean[i-1][prev], currmean = getmean(prev+1, j);
                // have to make sure that this access point is the closest to all those it covers,
                // and isn't the closest to all those it doesn't cover.
                if (x[prev]-prevmean <= currmean-x[prev] && x[prev+1]-prevmean >= currmean-x[prev+1]) {
                    if (getsumsqdists(prev+1, j) + prevdp < best) {
                        best = getsumsqdists(prev+1, j) + prevdp;
                        bestmean = currmean;
                    }
                }
             }

            dp[i][j] = best;
            mean[i][j] = bestmean;
        }
    }
    // cout << "dp:\n";
    // for (int i = 0; i <= k; ++i) {
    //     for (int j = 0; j <= n; ++j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "mean:\n";
    // for (int i = 0; i <= k; ++i) {
    //     for (int j = 0; j <= n; ++j) {
    //         cout << mean[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    ans += dp[k][n];
    cout << fixed << setprecision(12) << ans << endl;
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
