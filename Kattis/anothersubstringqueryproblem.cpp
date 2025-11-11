#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

vector<ll> P = {998244353, 999999937};
vector<ll> MOD = {1000000007, 1000000009};
vector<vector<ll>> PPOW;
const int MAXN = 2e5+5;
ll rolling[2][MAXN];

struct RollingHash {
private:
    string s;
    int n;

    void _build_hashes() {
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[t][i] = (rolling[t][i-1] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        array<ll, 2> result;
        for (int t = 0; t < 2; ++t) {
            result[t] = rolling[t][r] - (rolling[t][l] * PPOW[t][r-l] % MOD[t]);
            if (result[t] < 0) result[t] += MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

ll hashhash(const pair<ll, ll> &hash) {
    return hash.first * (1e9 + 9) + hash.second;
}

struct Hash {
    size_t operator()(const pair<ll, ll> &p) const {
        return hashhash(p);
    }
};

struct KeyEqual {
    bool operator()(const pair<ll, ll> &a, const pair<ll, ll> &b) const {
        return a.first == b.first && a.second == b.second;
    }
};

void _build_powers() {
    PPOW = vector<vector<ll>>(2, vector<ll>(2e5+1, 1));
    for (int t = 0; t < 2; ++t) {
        for (int i = 1; i <= 2e5; ++i) {
            PPOW[t][i] = (PPOW[t][i-1] * P[t]) % MOD[t];
        }
    }
}

void solve() {
    /*
    the brute-force approach would be to generate all possible substring hashes, and for each distinct
    one, store the locations. then, for a given query, we could binary search on the locations for
    that query's hash. however, there are too many substrings. instead, we could just get the substring
    hashes corresponding to substrings of the same length as at least one query. it turns out that this
    is enough! why? because the number of different lengths is bounded by O(sqrt(2e5)). how do we know this?
    the sum of 1+2+...+n is n*(n+1)/2, which is in O(n^2). however, this also means that if we want some
    number of nonnegative integers a_1, a_2, ..., a_k to sum up to n, then the maximum number of distinct
    values among those integers is in O(sqrt(n)). this is because the best we could do (making each integer
    as small as possible to fit in more integers, and making each one unique) would look like a_1=1, a_2=2,
    ..., a_k=k, but we already know that since sum(a_i)=n, that means that n is in O(k^2), so then k is
    in O(sqrt(n)). outside of that best case, the number of distinct integers would be less than or equal
    to O(sqrt(n)).

    generalizable ideas for the future:
    - if we have some nonnegative integer N such that a sequence of nonnegative integers a_1, a_2, ..., a_k
    sums up to N, then the number of distinct values across a_i is in O(sqrt(N))
    - using a vector instead of an array, where appropriate, can literally cause a TLE instead of an AC
    due to the heap allocation; don't you remember that heap allocations are slow compared to stack
    allocations?
        - to be fair, though, this problem is unusually tight in terms of the time limit, with this solution
        passing while taking 5.94s whereas the time limit is 6s
    - re-indexing the same hashmap (or even ordered map) multiple times for the same key duplicates work
    that can be done once by storing the result of the first find() call in an iterator. in this case,
    making this mistake is one of the differences between a TLE and an AC
    */

    _build_powers();
    string s;
    cin >> s;
    int n = s.size();
    int q; cin >> q;
    vector<string> t(q);
    vector<int> k(q);
    unordered_set<int> lengths;
    for (int i = 0; i < q; ++i) {
        cin >> t[i];
        lengths.insert(t[i].size());
        cin >> k[i];
    }
    // cout << "lengths.size() = " << lengths.size() << endl;
    // cout << "n = " << n << endl;

    // we only store positions for hashes equal to a query's hash, but multiple queries might
    // have the same t_i (though not the same k_i), so we just gropu them all together with `firstquery`
    unordered_map<pair<ll, ll>, int, Hash, KeyEqual> hashtoidx;
    vector<int> firstquery(q);
    for (int i = 0; i < q; ++i) {
        RollingHash h(t[i]);
        pair<ll, ll> hash = h.get_hash(0, t[i].size());
        auto it = hashtoidx.find(hash);
        if (it != hashtoidx.end()) {
            firstquery[i] = it->second;
        } else {
            hashtoidx[hash] = firstquery[i] = i;
        }
    }
    
    RollingHash h(s);
    vector<vector<int>> positions(q);
    for (int len : lengths) {
        // cout << "len = " << len << endl;
        for (int i = 0; i <= n - len; ++i) {
            pair<ll, ll> hash = h.get_hash(i, i+len);
            auto it = hashtoidx.find(hash);
            if (it != hashtoidx.end()) {
                int index = it->second;
                positions[index].push_back(i + 1); // 1-indexed position
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        if (positions[firstquery[i]].size() < k[i]) {
            cout << "-1\n";
        } else {
            cout << positions[firstquery[i]][k[i]-1] << "\n";
        }
    }
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
