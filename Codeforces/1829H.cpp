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

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
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

ll modpow(ll b, ll e) {
    if (e == 0) return 1;

    if (e % 2) {
        ll res = modpow(b, e - 1);
        return (res * b) % MOD;
    } else {
        ll res = modpow(b, e / 2);
        return (res * res) % MOD;
    }
}

void solve() {
    /*
    - problem:
        - given an array whose values must be small, count the number of subsets whose bitwise AND has
        exactly k turned-on bits
    - solution:
        - for each possible mask, count the number of subsets whose bitwise AND is exactly that mask using DP,
        where the DP table is 
        - then, iterate over the masks with exactly k turned-on bits, and add all of their DP values together
    - generalized ideas for the future:
        - suppose we want to inefficiently calculate the number of subsets of an array using DP instead
        of the closed-form combinatorics formula. there are two possible tasks:
            - count number of total subsets
                - we'd let dp[i][0] be the number of subsets using the first i elements where we don't
                include the i'th element, and dp[i][1] be the number of subsets using the first i elements
                where we DO include the i'th element
                - then, the base case is dp[0][0] = 0, dp[0][1] = 1
                - and the transition is dp[i][0] = dp[i-1][0] + dp[i-1][1] and
                                        dp[i][1] = dp[i-1][0] + dp[i-1][1]
            - count number of non-empty subsets
                - we'd let dp[i][0] be the number of non-empty subsets using the first i elements where
                we don't include the i'th element, and dp[i][1] be the number of non-empty susbets using
                the first i elements where we DO include the i'th element
                - then, the base case is dp[0][0] = dp[0][1] = 0, since we can't have a non-empty subset
                where we don't use any elements
                - and the transition is dp[i][0] = dp[i-1][0] + dp[i-1][1] and
                                        dp[i][1] = dp[i-1][0] + dp[i-1][1] + 1
            - so basically, the difference is that when we're counting all subsets, the base case is 1
            since we CAN have empty subsets, and the future states don't add anything, but when we're counting
            non-empty subsets, the base case is 0, and the future states have an explicit addition for the
            case where we have the current element ALONE.
            so, 3 cases in second problem: don't use current element, do use current element but it's
            definitively NOT alone, do use current element but it's definitively alone. we know that the
            element is definitively NOT alone in the second case, because dp[i][j] assumes the subsets are
            non-empty, and reaching into dp[i-1][0] or dp[i-1][1] makes the assumption that those values
            count the number of non-empty subsets at a previous index
            - and this problem is just a special case of the second problem
        - when using a mask itself as an index for one of the dimensions of the memoized results table,
        we can iterate over the thing used to compute the current index (i.e., the previous AND value)
        instead of over the current index
        - subsets are nice for DP, because there are a large number of subsets but the property that we
        care about from the subset (the AND value across the subset) is something that has much fewer values
        - make it so that when you solve a problem, if you were to see the exact problem again, you'd (1) have
        the exact solution memorized and (2) understand the justification for (and alternatives to) every part
        of the solution, which makes it easier to match parts of future problems into variations of parts from
        this problem
    */

    // condenses the input array into 64 possible values; reduces time complexity from O(n * 64)
    // to O(n + 64^2)
    int n, k;
    cin >> n >> k;
    map<int, int> freqs;
    while (n--) {
        int ai;
        cin >> ai;
        freqs[ai] += 1;
    }
    
    // count number of subsets whose bitwise AND equals each possible mask value
    vector<ll> mem(64, 0);
    for (auto [ai, cnt] : freqs) {
        // gets number of subsets of this value
        ll empty = 1;
        ll nonempty = modpow(2, cnt) - empty;

        // gets DP states at this index
        // note: we iterate over the masks that the previous subsets could have had as their AND,
        // and compute the current mask (which doubles as an index) based on the previous mask and
        // the current element, not the other way around (like iterating through possible current
        // masks and seeing which previous masks achieve it when including the current element),
        // because that is easier to code
        vector<ll> newmem(64, 0);
        for (int mask = 0; mask < 64; ++mask) {
            // case 1: we don't use the current element
            // index being updated: previous mask
            newmem[mask] = (newmem[mask] + mem[mask] * empty) % MOD;
            
            // case 2, part 1: we do use the current element, but there are guaranteed to be stuff before
            // index being updated: previous mask (mask of previous subsets) ANDed with current element
            newmem[mask & ai] = (newmem[mask & ai] + mem[mask] * nonempty) % MOD;
        }
        // case 2, part 2: we do use the current element, and it is the only element in the subset
        // index being updated: mask of (so basically equal value to) current element
        newmem[ai] = (newmem[ai] + nonempty) % MOD;

        // update DP states
        mem = std::move(newmem);
    }

    // looks over all masks
    ll ans = 0;
    for (int mask = 0; mask < 64; ++mask) {
        if (__builtin_popcount(mask) == k) {
            ans = (ans + mem[mask]) % MOD;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
