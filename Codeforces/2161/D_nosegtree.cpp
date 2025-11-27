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
    generalizable ideas for the future:
    - we have a different rule for how we obtain DP values based on whether the subproblem corresponds to v-1 or not
    (assuming we are processing an index for value v), so we can get the maximum for <=v-2, ==v-1, and ==v separately.
    basically, since we need to break into cases based on a value, we can keep track of some info (maximum on DP values)
    separately for 3 different cases (since the value v-1 breaks the number line into 3 segments, and the constraint
    that we are only considering values <= v caps the rightmost block).
    - we want to minimize the number of elements we remove such that the remaining ones follow some rule. we can do
    this by maximizing the number of elements such that they all follow some rule (and removing the other ones)
    */

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    map<int, set<int>> indices;
    for (int i = 0; i < n; ++i) {
        indices[a[i]].insert(i);
    }

    map<int, map<int, int>> mem;
    int maxprev = 0, ans = 0;
    for (auto e : indices) {
        int val = e.first;
        int maxcurr = 0, maxminus1 = 0;
        for (auto it = e.second.rbegin(); it != e.second.rend(); ++it) {
            int idx = *it;

            // get max DP value across all right-side indices for value val-1
            if (indices.find(val - 1) != indices.end()) {
                auto it2 = mem[val-1].lower_bound(idx);
                if (it2 != mem[val-1].end()) {
                    maxminus1 = max(maxminus1, it2->second);
                }
            }

            int best = 1 + max({maxprev, maxcurr, maxminus1});
            mem[val].insert(make_pair(idx, best));
            ans = max(best, ans);

            // update max DP value across all (implicitly right-side) indices for value val
            maxcurr = max(maxcurr, best);
        }

        // update max DP value across all indices for values <= val - 2 for any future value val.
        // all indices of the current val have been processed, so runs the following two cases:
        // - the last value was == val - 1, so all mem values for val - 1 are integrated into maxprev
        // - the next value is >= val + 2 for the current val, so all mem values for val are integrated
        // into maxprev
        if (indices.find(val - 1) != indices.end()) {
            for (auto it2 : mem[val-1]) {
                maxprev = max(maxprev, it2.second);
            }
        }
        if (indices.upper_bound(val) != indices.end() && indices.upper_bound(val)->first >= val+2) {
            for (auto it2 : mem[val]) {
                maxprev = max(maxprev, it2.second);
            }
        }
    }
    ans = n - ans;
    cout << ans << "\n";
    // cout << "====\n";
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
