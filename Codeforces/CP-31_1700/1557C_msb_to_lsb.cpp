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
    - details:
        - at bit position i, the possible states are "the AND of the n array elements for the i bit positions
        so far is > the XOR", "AND = XOR", and "AND < XOR". in this problem, our final goal is to only get the
        first 2. it is possible and not wrong to keep track of all 3, but it just so happens to turn out that
        we only need to keep track of the first 2, because if we are moving from MSB to LSB, then as soon as we
        drop below (AND becomes < than XOR), then we cannot become equal or greater again. as a result, we don't
        need to keep track of the AND < XOR state.
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
    ll ways_equal = 0, ways_greater = 0, ways_all = mod_pow(2, n);
    if (n % 2) {
        ways_equal = 1;
    } else {
        ways_greater = 1;
    }
    for (int i = 0; i < n; i += 2) {
        ways_equal = (ways_equal + nCr(n, i)) % MOD;
    }

    // computes DP value for each DP state
    // mem[i][j] = number of ways for the bits in the interval [i, k - 1] (where bit b is the coefficient
    // of 2^b) to be such that:
    // - AND = XOR, if j == 0
    // - AND > XOR, if j == 1
    vector<vector<ll>> mem(k+1, vector<ll>(3, 0));
    mem[k][0] = 1;
    for (int i = k - 1; i >= 0; --i) {
        // everything so far will be equal if we were already equal and we are equal again
        mem[i][0] = ways_equal * mem[i+1][0] % MOD;

        // everything so far will be greater if:
        // (1) it was already greater, because everything from here on out will be an order of magnitude less significant
        // (2) it was already equal, and at this bit, we become greater
        mem[i][1] = ways_all * mem[i+1][1] % MOD;
        mem[i][1] = (mem[i][1] + (ways_greater * mem[i+1][0] % MOD)) % MOD;
    }
    cout << (mem[0][0] + mem[0][1]) % MOD << endl;
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
