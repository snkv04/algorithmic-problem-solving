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

void solve() {
    /*
    - given some array, in one operation, we can take some integer and XOR two adjacent elements with it.
    for that array, the cost is the number of operations needed to make all elements 0, or the length of
    the array if it's impossible. we want to compute the cost of all n*(n+1)/2 subarrays of the given array.
    - we can first observe, that it's impossible to make the subarray into all 0s if its subarray XOR sum
    is nonzero. so, we can break the subarrays into two cases: where the subarray sum is 0 and where it
    isn't. we can also precompute the prefix XOR sums to be able to find, for a given index, which previous
    indices had the same prefix sum.
    - for a given index, we want to find the cost for all subarrays ending at that index whose sum is nonzero.
    basically, we want to consider the subarrays corresponding to previous prefix sums that aren't equal to
    the one at this index. (for example, if we are at 1-based index 8 and there are 2 previous indices with
    the same prefix sum, then there are 6 without.) that is just the length of all of those subarrays, summed.
    this can be efficiently calculated by keeping track of the number of each prefix sum, the total index
    sum of each prefix sum, and a quick gaussian sum so that we take the complement by subtracting the total
    index sum.
    - now, we also want the cost for all subarrays that we can flatten. it turns out that, for a given subarray
    [l, r] where the prefix sum of l-1 is the same as that of r, the number of operations we need is just the
    number of non-same prefix sums as pref[r] between l and r. basically, if we pass through the subarray
    left-to-right and flatten it, then whenever the subarray sum resets to 0, we don't have to do any operations
    until it becomes nonzero again. to calculate this, for each prefix sum value p, consider a contiguous segment
    of indices [i_1, i_2, ..., i_k] where pref[i_j] isn't equal to p. then, the number of times that segment
    will be used is the number of subarrays covering it whose ending and beginning prefix sums are p, which
    is just the count of p to the left times the count of p to the right.
    */

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    vector<ll> pre(n+1, 0);
    ll nonmatching = 0;
    map<ll, set<ll>> pre_to_idx_set;
    pre_to_idx_set[0] = {0};
    map<ll, ll> pre_to_idx_sum;
    pre_to_idx_sum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i-1] ^ a[i-1];
        if (pre_to_idx_set.find(pre[i]) == pre_to_idx_set.end()) {
            pre_to_idx_set[pre[i]] = set<ll>();
        }
        if (pre_to_idx_sum.find(pre[i]) == pre_to_idx_sum.end()) {
            pre_to_idx_sum[pre[i]] = 0;
        }
        nonmatching += ((ll) i * (i - pre_to_idx_set[pre[i]].size()))
            - ((ll) i * (i - 1) / 2) + pre_to_idx_sum[pre[i]];
        // cout << "for idx " << i << ", nonmatching += " << (((ll) i * (i - pre_to_idx_set[pre[i]].size()))
        //     - ((ll) i * (i - 1) / 2) + pre_to_idx_sum[pre[i]]) << "\n";;

        pre_to_idx_set[pre[i]].insert(i);
        pre_to_idx_sum[pre[i]] += i;
    }
    // print_container(pre, "pre = ");

    map<ll, set<ll>> pre_to_idx_set_2;
    pre_to_idx_set_2[0] = {0};
    ll matching = 0;
    for (int i = 1; i <= n; ++i) {
        ll dist = pre_to_idx_set_2.find(pre[i]) == pre_to_idx_set_2.end() ? 0 : (i - *pre_to_idx_set_2[pre[i]].rbegin() - 1);
        ll num_before = pre_to_idx_set_2.find(pre[i]) == pre_to_idx_set_2.end() ? 0 : pre_to_idx_set_2[pre[i]].size();
        matching += dist * num_before * (pre_to_idx_set[pre[i]].size() - num_before);
        pre_to_idx_set_2[pre[i]].insert(i);
    }

    // cout << "m = " << matching << ", nm = " << nonmatching << "\n";
    ll ans = nonmatching + matching;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
