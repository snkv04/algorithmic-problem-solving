#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

void solve() {
    /*
    - details:
        - the difference between this solution and the other one is that the other one breaks all the possible
        subsequences into 3 patterns, based on what the start looks like (either 011011..., 101101..., or 110110...).
        then, each of those patterns is separately broken down into possible lengths. in this solution, for
        subsequences of length 1 or 2, we do break them down into separate cases which then correspond to one
        of the 3 above patterns, but for subsequences of length >= 3, we don't care what its length modulo 3 is.
        we only care about what its ending looks like (which can be defined in terms of 2 digits, 3 digits, etc.).
        basically, does it look like ...110, ...101, or ...011? this can be easily done by sharing information
        across the 3 patterns for length 2 and length 3.
    */

    // reads in input
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // counts fully even subsequences with combinatorics
    ll even = 0, ans = 0;
    for (int i = 0; i < n; ++i) even += a[i] % 2 == 0;
    if (even >= 3) {
        ans += mod_pow(2, even);
        ans -= (1 + even + even * (even - 1) / 2) % MOD;
        if (ans < 0) ans += MOD;
    }

    // counts odd, even, odd subsequences with DP
    // mem[0][0] = # of subseq. equal to "11"
    // mem[0][1] = # of subseq. equal to "10"
    // mem[0][2] = # of subseq. equal to "01"
    // mem[1][0] = # of subseq. equal to "110"
    // mem[1][1] = # of subseq. equal to "101"
    // mem[1][2] = # of subseq. equal to "011"
    vector<vector<ll>> last_digit = {
        {1, 0, 1},
        {0, 1, 1}
    };
    vector<vector<ll>> mem(2, vector<ll>(3, 0));
    vector<ll> counts(2, 0);
    for (int i = 0; i < n; ++i) {
        // makes new table of memoized results
        vector<vector<ll>> new_mem = mem;
        
        // updates counts of subsequences with length 2
        for (int j = 0; j < 3; ++j) {
            if (last_digit[0][j] == a[i] % 2) {
                new_mem[0][j] = (new_mem[0][j] + counts[j < 2]) % MOD;
            }
        }

        // updates counts of subsequences with length 3
        for (int j = 0; j < 3; ++j) {
            if (last_digit[1][j] == a[i] % 2) {
                new_mem[1][j] = (new_mem[1][j] + mem[0][j] + mem[1][(j + 2) % 3]) % MOD;
            }
        }

        // updates DP table
        mem = std::move(new_mem);

        // updates counts of subsequences of length 1 (i.e., counts of even/odd values)
        // why after everything else? because otherwise a single element from the array might
        // be counted as both the first and second element of a subsequence
        counts[a[i] % 2] += 1;
    }
    for (int j = 0; j < 3; ++j) ans = (ans + mem[1][j]) % MOD;
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
