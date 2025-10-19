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

vector<vector<int>> adj, dp;
int n;

int recurse(int i, int j) {
    int len = (j + n - i) % n + 1;
    if (len <= 1) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    // subproblems which don't split the interval
    int result = max({
        recurse((i+1)%n, j),  // technically does split the interval lol
        recurse(i, (j+n-1)%n),  // technically does split the interval lol
        (len <= 2 ? 0 : recurse((i+1)%n, (j+n-1)%n)) + adj[i][j]
    });

    // subproblems which do split the interval
    int left = (j + n - 1) % n;
    while (left != i) {
        int right = (left + n - 1) % n;
        result = max(result, recurse(i, right) + recurse(left, j));
        left = right;
    }
    dp[i][j] = result;
    return result;
}

void solve() {
    /*
    generalizable ideas for the future:
    - if calculating "length" during modular arithmetic, and we have a left and right bound where we
    always assume that the right is "to the right" of the left, then make sure to consider edge cases
    where the left is actually >= the right (modulo n) and that should signify a length of -1 but instead
    we calculate it as a length of n-1. to avoid such cases, just be careful making any call to a function
    where the length between the left and right might be negative, and compute those base cases separately.
    - the reason why my first attempt didn't work is as follows. basically, i tried to pick a left-start
    and an adjacent right-start, and then calculate the maximum number of segments achievable where each
    segment connects the left side to the right side. for example, if the left-start is 8 o'clock and the
    right-start is 7 o'clock, then dp[3][4] would be the maximum number of lines where each one goes from
    the segment [8, 11] to the segment [7, 3] and none of them intersect. the obvious issue is that no
    segments are allowed to connect within their own segment, and they always cross over this "bridge"
    in the middle for no reason. so, having a line on [5, 6] then [7, 8] then [9, 10] could never happen.
    - the reason why my second attempt didn't work is similar. basically, we consider contiguous segments
    around the perimeter now, but we actually make a very similar mistake as before. in this one, i had
    dp[i][j] be the maximum number of non-crossing lines over the section [i, j], but i calculated it
    as max(dp[i+1, j], dp[i, j-1], dp[i+1, j-1] + adj[i][j]). this doesn't allow line segments next to
    each other either, only line segments that are on top of each other.
    - this problem is can actually be unrolled into a problem on a 1-dimensional number line. concisely,
    given a bunch of intervals [l_i, r_i], count the maximum number of intervals that you can pick such
    that none of them "cross" over any other one's endpoints; namely, given two intervals, either one should
    be entirely contained in the other or not overlap at all. this can't be solved with a simple dp[i],
    where i is the rightmost value of any segments being considered, because if we want to include a segment,
    then we need to be able to get everything to the left of that segment but also everything under that
    segment. so, we need to be able to place a left bound, which is what motivates having dp[i][j] be the
    maximum number of segments over the interval [i, j] that meet the conditions of the problem.
        - to compute it, note that there are two ways that different segments can interact: either one can
        entirely contain some others, or one can not overlap another at all. so, we need to be able to place
        an interval on [i, j] (if one exists) then take the subproblem from [i+1, j-1], as well as look over
        all possible ways to split the interval into [i, m] + [m+1, j], and then take whichever one is better.
        - by the way, why do we only have to consider splitting a segment once (sure, over different positions
        for the split, but still only one split happens), instead of splitting it in all possible ways (like
        getting the subproblem where you place 5 splits in [i, j])? well, that's a basic idea at the core of
        DP. basically, by splitting it once (selecting an "m" index) but also considering splitting it once
        for each of the subproblems (which are [i, m] and [m+1, j]), we actually do end up considering all ways
        to place any number of splits. in short, the "multiple splits" propagate through the subproblem chain.
        this same idea is common in DP problems; for instance, in the coin combinations problem, we only
        consider using each coin once for the given current value, because in the subproblems that we look at,
        we might use the same coin again. similarly, we only consider placing one split in our interval
        [i, j], because in the subproblems we look at, it might be optimal to place more splits within those
        subproblems' intervals. the same idea is applied with projectors in linear algebra; once you know that
        P^2 = P, then P^k for any positive k can also be found to be equal to P by splitting up that exponent
        repeatedly until each term is either P^2 or P, and similarly, since we know that dp[i][j] is calculated
        the same way for all i and j, then placing one split is enough since we know that if we break it down
        using one split then each of those subproblems will check if using further splits is optimal or not.
    */

    cin >> n;
    adj = vector<vector<int>>(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> adj[i][j];

    int ans = 0;
    dp = vector<vector<int>>(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int len = 2; len <= n; ++len) {
            int j = (i + len - 1) % n;
            ans = max(ans, recurse(i, j));
        }
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
