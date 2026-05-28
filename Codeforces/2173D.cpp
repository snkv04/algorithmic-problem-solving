#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
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

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
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

ll lowest_bit(ll x) {
    assert(x > 0);
    ll b = 0;
    while (!((x >> b) & 1)) ++b;
    return b;
}

ll seg_len(ll x, ll b) {
    ll len = 0;
    while ((x >> b) & 1) {
        ++len;
        ++b;
    }
    return len;
}

void solve() {
    // solve base cases
    ll n, k;
    cin >> n >> k;
    if (!k) {
        cout << "0\n";
        return;
    }
    if (k >= 30) {
        ll ans = 0;
        while (__builtin_popcountll(n) > 1) {
            ll lowest = lowest_bit(n);
            ans += seg_len(n, lowest);
            n += (1 << lowest);
            --k;
        }
        ans += k;
        cout << ans << "\n";
        return;
    }

    // precompute segment lengths
    vector<int> segment(31, 0);
    for (int i = 29; i >= 0; --i) {
        if ((n >> i) & 1) {
            segment[i] = segment[i + 1] + 1;
        }
    }

    /*
    - mem[i][j][k] = maximum number of carries over bits [i, 30] if we do j operations and the i'th bit is equal
    to k
    - important but unintentional subtlety: this is assuming that the i'th bit is equal to k and we are going to
    do j operations, not that we've already done j operations
        - in some problems, we definitely do assume that mem[i][j] = max (some value) at index i after doing
        j operations, but here, it's the opposite, in that the current index i is at the given state k before doing
        the j operations
        - only reason why i did it this way is that if we perform a carry from index i, then we know that after
        the carry, the new index's bit value will be 1 before any new operations/carries are done, so the implementation
        is easy: we know what state we'll move to
    - here, we fill out the base cases
    */
    int mem[31][k + 1][2];
    for (int i = 0; i <= 30; ++i) for (int j = 0; j <= k; ++j) fill(mem[i][j], mem[i][j] + 2, -1e9);  // all states start as unreachable
    mem[30][0][0] = 0;  // if we've done no operations, we get no carries
    for (int j = 0; j <= k; ++j) mem[30][j][1] = j;  // if we're at bit 30 and still have j operations left to do, we get 1 carry from each of them
    for (int i = 0; i <= 30; ++i) for (int k = 0; k < 2; ++k) mem[i][0][k] = 0;  // if we've done no operations, we get no carries

    // - here, we fill out the non-base cases
    for (int i = 29; i >= 0; --i) {
        for (int j = 1; j <= k; ++j) {
            // assuming bit is 0, we don't want to do any operations
            mem[i][j][0] = mem[i + 1][j][(n >> (i + 1)) & 1];

            // assuming bit is 1, we choose between doing an operation and not doing one
            int len = segment[i + 1] + 1;
            mem[i][j][1] = max(
                mem[i + 1][j][(n >> (i + 1)) & 1],
                len + mem[i + len][j - 1][1]
            );
        }
    }
    cout << mem[0][k][n & 1] << "\n";
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
