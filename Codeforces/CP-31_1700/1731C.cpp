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

void solve() {
    /*
    - problem:
        - we have an array, and we want to find the number of subarrays (defined by bounds l and r) whose XOR
        has an even number of divisors
    - solution:
        - that will be equal to the total number of subarrays minus the number of subarrays with an XOR with
        an odd number of divisors, and that second term is equal to the number of subarrays with an XOR that is
        a perfect square
        - to find the # of subarrays with perfect square XOR, we can loop over all possible square XORs we could
        have at every index, find the other prefix XOR we need to take away, and add the count of them, which just
        requires (1) keeping track of the prefix XOR, and (2) counting the frequency of each prefix XOR
    - details:
        - we want to be able to handle all possible XORs the subarray can have, as well as all possible XORs the
        prefix at the left of the subarray can have. note that if every value we are XORing is <= n, then the maximum
        value of any XOR among such values can be <= 2n-1; therefore, we allow our squares to go up to 2n-1 (or, by
        approximation, 2n). however, to get our "other" value, we XOR our prefix XOR (which is <= 2n-1) with the square
        (which is <= 2n-1), resulting in an "other" value that is <= 4n-2. we need to consider this, because yes it
        is true that we only care about prefix/subarray XORs that are <= 2n-1 because those are the only ones POSSIBLE,
        but due to intermediate calculations we might be CHECKING for XORs <= 4n-2; to deal with this, we can either
        set our bounds for prefcnt to have a max index of 2n-1 and just make sure the thing we're checking for is within
        the bounds, or leniently set our bounds to cover everything we could check for even though their frequency
        values would just be 0 beyond a certain index.
            - to remember for the future: we should always check that a value is within the bounds we expect, because
            even though the set of possible values for one variable has some bounds that it'll always fall within, the
            value we're using for some purpose (like an index) might actually be a slightly different variable that is
            out of the bounds for the first variable (such as due to intermediate calculations).
            in this problem, the first variable is in the set of all possible prefix XORs and subarray XORs for the
            given array. the second variable is the prefix XOR we are checking for when "subtracting" the square, where
            the square can go beyond the bounds that the array's values have.
    */

    int n;
    cin >> n;
    int rtn = sqrt(2*n-1);
    vector<int> a(n);
    cin >> a;

    ll ans = 1LL * n * (n + 1) / 2;
    vector<int> prefcnt(2*n, 0);
    int pref = 0;
    prefcnt[0] = 1;
    for (int i = 0; i < n; ++i) {
        pref ^= a[i];
        for (int rt = 0; rt <= rtn; ++rt) {
            int sq = rt * rt;
            int other = pref ^ sq;
            if (other <= 2*n-1) ans -= prefcnt[other];
        }
        prefcnt[pref] += 1;
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
