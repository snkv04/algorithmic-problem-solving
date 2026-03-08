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
std::ostream& operator<<(std::ostream &os, std::vector<T> &v) {
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i < v.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (int i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;

public:
    SegmentTree(int n) : n(n) {
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return -1e9;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return max(
            _query(2 * v, l, m, ql, qr),
            _query(2 * v + 1, m + 1, r, ql, qr)
        );
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
        t[v] = max(t[2 * v], t[2 * v + 1]);
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

void solve() {
    /*
    - problem:
        - given an array, find the minimum number of elements we'd need to remove to ensure that there are no
        two indices i, j for the remaining array such that i < j and a[i] == a[j] - 1
    - solution:
        - come up with a special ordering S such that if S_i is equal to the ((index) of (index i from the original
        array) in (S)), then dp[i] can be computed from all dp[j] such that S_j < S_i
        - then, just run DP on that new ordering, possibly using ordered sets or segment trees to make things more
        efficient by storing the DP array within them
    - details:
        - coming up with the sequence order allows you to define a notion of "previous" elements/indices, so that
        becomes very useful for DP because dp[i] will be computed using dp[j] from a subset of {j : j is "before" i}
            - primary question for determining if a sequence S is useful for defining a notion of "before":
            can we compute dp[i] using dp[j] across some subset of {j : S_j < S_i}, where we don't necessarily need
            all such j, but using those j is sufficient?
        - on coming up with the sequence:
            - we know that for an index i, if we want to let a[i] remain in the array (or, alternatively, be chosen
            for our final sequence), then the other indices j can either be such that:
                - a[j] < a[i] - 1
                - a[j] > a[i] + 1
                - a[j] == a[i] - 1, but j > i
                - a[j] == a[i] + 1, but j < i
            - let's then see if a USEFUL sequence S for defining our notion of "previous" element/index is to sort
            all i by (weakly) increasing a[i], where ties between indices i and j are broken by sorting i and j
            in ascending order. then, can we compute dp[i] by using values of dp[j] where S_j < S_i? no, that will
            not be easy, and will therefore not be useful. for example, assume that we have that a=[5,4,3,4,3,4,5].
            even though a[0] == a[6] == 5, there are 2 problems here:
                - we can't easily compute dp[6] using dp[0], because when computing dp[0] we might have included
                a bunch of j such that a[j] == 4 as part of our final sequence of indices, and then that will be
                a problem when using a[0] to compute a[6]. namely, this doesn't satisfy the "sufficient" condition
                in answering the question above, because in computing dp[j] we allowed some operations that aren't
                allowed for computing dp[i] (where an "operation" is "including an element in our sequence")
                - we can't compute dp[0] using dp[6]; it would be nice to, because we should allow elements of the
                same value in our sequence, but S_6 would be > S_0 when S is defined this way, so this doesn't
                satisfy the "sufficient" condition above because we can't use all indices we need to compute dp[0]
            - how about this? let's see if we can define S as follows: it will hold the indices i by order of
            weakly increasing a[i], where ties betwen indices i and j are broken by sorting i and j in DESCENDING
            order. is this useful? yes, because if we are computing dp[i] from dp[j], then we know that:
                - if a[j] < a[i] - 1, then doing this computation is of course completely fine, meaning that all
                elements included when computing dp[j] will be fine when computing dp[i]
                - if a[j] == a[i] - 1, then doing this comptuation is fine, because even though j might satisfy j < i,
                we can simply skip over such j
                - if a[j] == a[i], then doing this computation is fine, because any elements we included in the
                sequence when computing dp[j] will be fine when computing dp[i]
            - okay, now we've defined S.
        - on computing DP values after getting S:
            - now, we want to compute dp[i] using dp[j] for some subset of {j : S_j < S_i}. i say some subset because
            it is true that some values j where S_j < S_i are not fit for using dp[j] for calculating dp[i]. but, the
            important thing is: for all j whose dp[j] are needed to compute dp[i], we've defined S such that S_j < S_i.
            here's how we compute dp[i]:
                - across all j where (S_j < S_i) and (a[j] < a[i] - 1), we can take max across dp[j]
                - across all j where (S_j < S_i) and (a[j] = a[i] - 1), we can take max across dp[j] for j > i
                - across all j where (S_j < S_i) and (a[j] == a[i]), we already know that j > i, so we can
                take max across dp[j]
            - and that's it.
    - generalizable ideas for the future:
        - we have a different rule for how we obtain DP values based on whether the subproblem corresponds to v-1
        or not (assuming we are processing an index for value v), so we can get the maximum for <=v-2, ==v-1, and
        ==v separately. basically, since we need to break into cases based on a value, we can keep track of some
        info (maximum on DP values) separately for 3 different cases (since the value v-1 breaks the number line
        into 3 segments, and the constraint that we are only considering values <= v caps the rightmost block).
        - we want to minimize the number of elements we remove such that the remaining ones follow some rule.
        we can do this by maximizing the number of elements such that they all follow some rule (and removing
        the other ones)
        - we can compress the entire set of DP values for j where a[j] < a[i] - 1 into one single scalar instead
        of storing it in an implicit DP table, segtree, or sorted set/map. this can speed things up a lot
        - conceptually, we can treat our indices or array elements as part of a sequence S, in order to define
        a notion of "before" (and that will be the order in which we iterate over the elements), but we can just
        use the indices as they already are for the rest of the algorithm
        - in this particular problem, the fact that a_i <= n actually does not help at all, and even if a_i <= 1e9,
        the overall time complexity would be the same because we can just as easily (as we already are) jump from
        each a_i to the next a_i!
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    // cout << "a = " << a << endl;

    map<int, set<int>> indices;
    for (int i = 0; i < n; ++i) indices[a[i]].insert(i);

    // let mem[i] = maximum size of a sequence where we include i and we also can include any j such that
    // S_j < S_i, where S is ordered first by ascending value then by descending index
    int maxltprev = 0;  // max[mem[j]] across all j such that a[j] < a[i] - 1
    map<int, int> prevmem;  // prevmem[j] = mem[j], where j is such that a[j] == a[i] - 1
    for (auto &[ai, is] : indices) {  // iterates through values in increasing order
        // computes mem[i] for all i of the same a[i] value
        map<int, int> currmem;
        for (auto it = is.rbegin(); it != is.rend(); ++it) {  // iterates through indices in decreasing order
            int i = *it;
            int memi = 1 + max({
                maxltprev,
                prevmem.upper_bound(i) == prevmem.end() ? 0 : prevmem.upper_bound(i)->second,
                currmem.upper_bound(i) == currmem.end() ? 0 : currmem.upper_bound(i)->second
            });
            currmem[i] = memi;
        }

        // updates maxltprev and prev for next iteration
        bool jumping = !(indices.upper_bound(ai) != indices.end() && indices.upper_bound(ai)->first == ai + 1);
        if (jumping) {
            // make sure: BOTH curr (ai) and prev (ai - 1) will now be less than the NEW ai-1
            // more generally: if we're iterating over some increasing elements,
            // and we want to maintain a window of "slightly below" the current element,
            // then if we do a big jump, then both the stuff within the window AND the current element
            // will get pushed out of the window for the next iteration, instead of the current element
            // getting pushed down to "within the window"
            for (auto [i, memi] : currmem) {
                maxltprev = max(maxltprev, memi);
            }
            for (auto [i, memi] : prevmem) {
                maxltprev = max(maxltprev, memi);
            }
            prevmem.clear();
        } else {
            for (auto [i, memi] : prevmem) {
                maxltprev = max(maxltprev, memi);
            }
            prevmem = std::move(currmem);
        }
    }
    cout << n - maxltprev << '\n';
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
