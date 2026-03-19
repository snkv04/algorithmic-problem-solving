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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

void solve() {
    /*
    - problem:
        - given two numbers n and k, find the number of arrays of length n (where every element a_i satisfies
        0 <= a_i < 2^k) such that AND(a_1, a_2, ..., a_n) >= XOR(a_1, a_2, ..., a_n)
    - solution:
        - do dynamic programming for each state mem[i][j]--where i is the bit and j is whether AND is >, =,
        or < XOR for the bits so far--which gives the number of ways for that state to happen
        - to move from i-1 to i, we can count the number of ways for the bits at index i to cause AND to be >
         =, or < the XOR, and we can do that efficiently with combinatorics
    - details:
        - full solution:
            - we want to look over all the possible 2^(k*n) arrays and see how many of them have a bitwise
            AND >= the bitwise XOR
                - the search tree is of height k*n (all bits) and each node has 2 children
            - however, since the location of the bits (distributed across array elements) at each bit position
            does not matter (for example, for bit i, having 3 1s at the left and rest 0s does not differ in
            terms of AND or XOR from having 3 1s at the right and the rest 0s), we can reduce the search tree
            to size (n+1)^k
                - in short, we categorize many elements of the original search space, and so have fewer things
                (categories) to look over
                - why not iterate over the array elements themselves? there's no easy way to optimize looking
                over all the 2^k choices for each array element. if we look over bits, we can optimize looking
                over all the ways to distribute the bits over array elements by using counts of 1s
            - second optimization: instead of having all those n*k DP states, we can further categorize the n
            states at each bit position into 3 categories: number of ways to have AND>XOR for bits so far,
            AND=XOR, and AND<XOR
                - the search space is still 3^k, but this can be optimized using DP to take O(3*k) time
            - now we just need to know how many ways the bits for a single bit position across elements can be
            arranged so that the AND>XOR, AND=XOR, and AND<XOR. that, we can do by looking at cases (even/odd)
            and using combinatorics to count arrangements
        - what indicates that we should do DP? what is the brute-force solution?
            - as mentioned above, the slowest brute-force solution that is still correct would be to try either
            0 or 1 for every single bit, where there are (n numbers) * (k bits per number) = n*k bits. that's
            a huge decision tree.
            - the thing that hints at using DP is that the brute-force solution involves looking over a decision
            tree. DP lets you take a whole subtree and represent it using just one property (e.g., compress all
            coin combinations by simply counting the number of ways each sum can be made), so it is particularly
            well-fit for problems like these
        - don't allow my desire to make the code clean let me just guess at what the correct state transitions
        should be; write it correctly, even if ugly, then make it clean after. i've said this in various
        contexts so many times
        - why do we go from LSB to MSB? the core idea is that if numbers A and B differ at bit position i, then:
            - no amount of accounting for that in other bit positions can make the two numbers equal
            - the maximum sum from all LOWER bit positions still sums to less than a single digit change at that
            bit position
        and so, when going from LSB to MSB, the MSB generates the largest change. (this is true in any numeral
        system, such as base-10.) this same idea can actually be applied in reverse--namely, once the AND goes
        lower than the XOR, then we cannot salvage it anymore--which is what the editorial solution does. so,
        both ways are valid.
    */

    // reads in input
    int n, k;
    cin >> n >> k;
    if (k == 0) {
        cout << "1\n";
        return;
    }

    // precomputes factorials
    vector<ll> factorial(n+1, 1);
    for (int i = 1; i <= n; ++i) {
        factorial[i] = (factorial[i-1] * i) % MOD;
    }
    auto nCr = [&](int n, int r) {
        ll num = factorial[n];
        ll denom = factorial[r] * factorial[n-r] % MOD;
        return mod_div(num, denom);
    };

    // precomputes number of ways to get from one DP state to another
    ll ways_less = 0, ways_equal = 0, ways_greater = 0;
    if (n % 2) {
        ways_equal = 1;
    } else {
        ways_greater = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (i % 2) {
            ways_less = (ways_less + nCr(n, i)) % MOD;
        } else {
            ways_equal = (ways_equal + nCr(n, i)) % MOD;
        }
    }

    // computes DP value for each DP state
    // mem[i][j] = number of ways for the bits so far, at the bit corresponding to 2^(i-1), to be
    // such that:
    // - AND < XOR, if j == 0
    // - AND = XOR, if j == 1
    // - AND > XOR, if j == 2
    vector<vector<ll>> mem(k+1, vector<ll>(3, 0));
    mem[0][1] = 1;
    for (int i = 1; i <= k; ++i) {
        // everything so far will be less if either:
        // (1) things are less at this bit
        // (2) things are equal at this bit, but it was already less
        for (int j = 0; j < 3; ++j) {
            mem[i][0] = (mem[i][0] + (ways_less * mem[i-1][j] % MOD)) % MOD;  // AND IT WAS COPIED FROM HERE, YET I MISSED THAT :D
        }
        mem[i][0] = (mem[i][0] + (ways_equal * mem[i-1][0] % MOD)) % MOD;

        // everything so far will be equal if all previous stuff was equal and current position is equal
        mem[i][1] = (mem[i][1] + (ways_equal * mem[i-1][1] % MOD)) % MOD;

        // everything so far will be greater if either:
        // (1) things are greater at this bit
        // (2) things are equal at this bit, but it was already greater
        for (int j = 0; j < 3; ++j) {
            mem[i][2] = (mem[i][2] + (ways_greater * mem[i-1][j] % MOD)) % MOD;  // genuinely spent 20 minutes to realize that i was doing "* MOD" instead of "% MOD"
        }
        mem[i][2] = (mem[i][2] + (ways_equal * mem[i-1][2] % MOD)) % MOD;
    }
    cout << (mem[k][1] + mem[k][2]) % MOD << endl;
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
