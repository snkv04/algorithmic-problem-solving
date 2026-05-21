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
        - you are given two strings A and B of length up to 5e3
        - for two strings C and D, let their score be defined as f(C, D) = 4 * LCS(C, D) - |C| - |D|
        - find the maximum score across all substrings C of A and all substrings D of B
    - solution:
        - obvious brute-force:
            - iterate over all O(n^2) substrings C of A, iterate over all O(m^2) substrings
            D of B, and compute LCS(C, D) in O(|C| * |D|)=O(n*m), for a total of O(n^3 * m^3)
        - optimized brute-force:
            - let C be [a[l_a], a[l_a+1], ..., a[r_a-1], a[r_a]] and let D similarly be the
            substring of B with indices in the interval [l_b, r_b]
            - then, for all O(n*m) pairs (l_a, l_b), we can find LCS(a[la, ra], b[lb, rb]) for all
            O(n*m) pairs (ra, rb) in O(1) each with DP.
            - in other words, since we fix the starting indices to be the same for the two substrings,
            we can reuse the information for all pairs (ra, rb) from previous subproblems.
                - why? that's how the LCS DP works anyway, given the fixed starting indices: for all
                substrings ending at ra (for A) and rb (for B), we get LCS of those two prefixes by
                looking at previous prefixes, where the start points of the two prefixes are fixed
        - DP solution:
            - recognize that we can directly apply Kadane's greedy logic here: if we are at (ra, rb) and we
            want to restart our two substrings by setting la==ra and lb==rb (instead of leaving la and lb
            at whatever they were before) because that is better for THIS value of (ra, rb), then those
            "left bound" values will always be better for FUTURE values of (ra, rb) as well
            - therefore, we don't need to track (la, lb) in our DP state as we did in the previous solution,
            with the reason being that we can just greedily restart our substring, and such a greedy restarting
            will also be optimal for future (ra, rb) pairs
    - details:
        - in Kadane's, when we restart on index i, the "restart" or "fresh start" works by taking the
        sum of only the current element. in this problem, the "restart" works by not including the current
        element, or any element at all. why?
            - in Kadane's, we're not allowed to take an empty subarray.
            - in this problem, we can take empty substrings.
            - if we are allowed to take empty subarrays in Kadane's, then as soon as we go negative, we can
            also max that with 0, and our subarray would become empty in preparation for the next element.
            - if we aren't allowed to take empty substrings in this problem, the modification is actually
            pretty straightforward: instead of maxing mem[i][j] with 0, meaning that the substrings ending at
            (ra, rb) are empty, we'd max it with -2, meaning that the substrings ending at (ra, rb) only include
            the characters at ra and rb.
                - equivalently, you can think about it as the substrings right BEFORE ra and rb being empty,
                and we start a new substring (on both strings A and B) using only the characters ra and rb.
        - how can we even recognize that the O(n^6) can go to the O(n^4) solution? write out what is needed
        to actually be computed for both: for the former, we need mem[la][ra][lb][rb], which is the same as
        the latter, in other words, there really are only O(n^4) total states, and we don't need to compute
        each one more than once.
            - think about it like this: if we iterated over all substrings (la, ra, lb, rb), then it depends
            on the value of mem[la][ra'][lb][rb'], where la<=ra'<=ra and lb<=rb'<=rb. that means that
            mem[la][ra'][lb][rb'] can be used for multiple different substring pairs, or its information can
            be shared across different (la, ra, lb, rb) tuples. so, we can just iterate over all the tuples
            in an order that lets us compute each one in O(1) based on the previous states.
    */

    // reads in strings
    int n, m;
    cin >> n >> m;
    string a, b;
    cin >> a >> b;

    // initializes DP array
    vector<vector<int>> mem(n + 1, vector<int>(m + 1, -1e9));
    for (int i = 0; i <= n; ++i) mem[i][0] = 0;
    for (int j = 0; j <= m; ++j) mem[0][j] = 0;

    // runs DP, keeping track of max value across all pairs of prefixes
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            mem[i][j] = max({
                0,
                mem[i - 1][j] - 1,
                mem[i][j - 1] - 1,
                (a[i - 1] == b[j - 1]) ? (mem[i - 1][j - 1] + 2) : (mem[i - 1][j - 1] - 2)
            });
            ans = max(ans, mem[i][j]);
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
