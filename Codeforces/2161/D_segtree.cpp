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
    - maybe we might want to make mem[i] equal to the length of the longest subsequence such that all values
    in the subseqence > a[i] meet the conditions, all values < a[i]-1 meet the conditions, all values a[i] are
    allowed, and there are no indices j < i such that a[j] + 1 = a[i]. however, not only would this make there
    be cyclic dependencies (for example, mem[i] would depend on some mem[j] such that a[j] = a[i]+2, but mem[j]
    would also then depend on mem[i]), but this is also just hard to calculate in general. how would one do it
    efficiently?
    - instead, let's make mem[i] equal to the length of the longest subsequence such that all values in the
    subsequence are <= a[i] and there are no indices j in the subsequence such that j < i and a[j] + 1 = a[i].
    in other words, we are making mem[i] equal to the length of the longest valid subsequence where the subsequence
    includes the instance of a[i] at index i, and only values <= a[i] (if equal to a[i], then they are to the right)
    are in the subsequence. is this what we want? well, why wouldn't it be? the exclusion of elements greater than
    a[i] when processing a[i] is suspicious. well, if we are processing a 5 and we want to include some element with
    value 7 in our subsequence, then we don't have to worry about including that 7 right now, because by the time
    we process that 7, the possibility of including this 5 (and all other 5s) are being considered anyway.
    - now, we can compute mem[i] by setting it equal to 1 + max(mem[j]) across all j such that:
        - a[j] < a[i] - 1, and j can be to the left or right of i
        - a[j] == a[i], and j can again be anywhere (though we only process elements with equal value from right to left)
        - a[j] == a[i] - 1, and j > i
    - why do we process elements with equal value from right to left? if we have two indices i1 and i2 such that
    a[i1] == a[i2], then the subsequence including a[i1] might include some a[j] such that a[j] + 1 == a[i1] == a[i2]
    but i1 < j < i2, so then when we process i2 after i1, we would include that a[j], which is invalid. so, we'd want
    to process i2 before i1. in simpler terms, when computing the subproblem for some index, we don't want to use
    information from subproblems that are not compatible with that index.

    summary of solution:
    - let mem[i] be the length of the longest subsequence that includes the instance of a[i] at index i, only has
    elements <= a[i], and is valid. recall that a valid subsequence is such that for any j < i, a[j] != a[i] - 1.
    - then, to get mem[i], assuming we process i in order of a[i] (going right to left if tied), we can get the maximum
    of all mem[j] where a[j] < a[i-1] or a[j] == a[i], as well as of all mem[j] where a[j] == a[i]-1 but j > i. we
    then add 1 to that, since we are now including a[i].
    - to actually compute this, note that one part of that computation is getting the max across all indices, and the
    other part is getting the max across indices to the right. we can separate this out into two arrays mem and mem2,
    where the differentiating factor is which indices have their values active. while index i (from the original array)
    is being processed, the indices in mem that are active are all indices j where a[j]<=a[i] but a[j]!=a[i]-1, whereas
    the indices in mem2 that are active are all indices j where a[j] == a[i] - 1. this allows us to get the maximum
    across all indices for mem, and the maximum across right-side indices for mem2. the separation into arrays is just
    an implementation detail, and the usage of segment trees to perform range max queries (RMQ) is also an implementation
    detail.
        - in fact, because we process the current value's indices from right to left, so we only need the right-side
        indices for the current value, we just place the mem values for the current value in mem2, and then move them
        to mem once the current value becomes >= that value + 2.
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    map<int, set<int>> indices;
    for (int i = 0; i < n; ++i) indices[a[i]].insert(i);

    int maxltprev = 0;
    SegmentTree prevmem(n);
    for (auto &[val, index_set] : indices) {
        // computes mem[i] for each index i in index_set
        int maxcurr = 0;
        map<int, int> currmem;
        for (auto it = index_set.rbegin(); it != index_set.rend(); ++it) {
            int i = *it;
            int memi = 1 + max({
                maxltprev,
                maxcurr,  // fine, because we're going from right to left
                (int) prevmem.query(i, n-1)
            });
            currmem[i] = memi;
            maxcurr = max(maxcurr, memi);
        }

        // updates maxltprev (below window) and prevmem (within window) for next value
        // (1) move prevmem into maxltprev, and also update prevmem
        int a_i = val;
        int last_a_i = a_i - 1;
        if (indices.find(last_a_i) != indices.end()) {
            for (auto i : indices[last_a_i]) {
                maxltprev = max(maxltprev, (int) prevmem.query(i, i));
                prevmem.update(i, 0);
            }
        }
        // (2) move currmem to either maxltprev or prevmem
        int next_a_i = indices.upper_bound(a_i) == indices.end() ? 1e9 : indices.upper_bound(a_i)->first;
        bool jumping = next_a_i > (a_i + 1);
        if (jumping) {
            for (auto [i, memi] : currmem) {
                maxltprev = max(maxltprev, memi);
            }
        } else {
            for (auto [i, memi] : currmem) {
                prevmem.update(i, memi);
            }
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
