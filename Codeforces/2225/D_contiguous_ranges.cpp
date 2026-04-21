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

ll xor_prefix(ll x) {
    ll rem = x % 4;
    switch (rem) {
        case 0:
            return x;
        case 1:
            return 1;
        case 2:
            return x + 1;
        case 3:
            return 0;
    }
}

ll xor_range(ll l, ll r) {
    return xor_prefix(r) ^ ((l > 0) ? xor_prefix(l - 1) : 0);
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

// counts n such that n mod 4 = 3 and l <= n <= r
ll count_3s(ll l, ll r) {
    if (r < 3) return 0;

    ll mx = (r - 3) / 4;
    ll mn = l / 4;
    return max(0LL, mx - mn + 1);
}

// counts n such that n mod 4 = 1 and l <= n <= r
ll count_1s(ll l, ll r) {
    if (r < 5) return 0;

    ll mx = (r - 1) / 4;
    ll mn = (l + 2) / 4;
    return max(0LL, mx - mn + 1);
}

ll gauss(ll x) {
    return mod_div((x % MOD) * ((x + 1) % MOD) % MOD, 2);
}

ll ans_range(ll left, ll right) {
    ll ans = 0;

    ll num3 = count_3s(left, right);
    if (left % 4 != 0) --num3;
    if (num3 > 0)
        ans = gauss(num3);  // number of (l, r) pairs where l <= r, l mod 4 = 0, and r mod 4 = 3

    ll num1 = count_1s(left, right);
    if (left % 4 != 2) --num1;
    if (num1 > 0)
        ans = (ans + gauss(num1)) % MOD;  // number of (l, r) where l <= r, l mod 4 = 2, and r mod 4 = 1

    return ans;
}

void solve() {
    /*
    - solution:
        - we basically want to find the number of (l, r) where l <= r and l + 3 == r (mod 4), with the
        constraint that l <= x and x <= r
        - we can either:
            - take count(1, n), and subtract count(1, x - 1) + count(x + 1, n), where count(L, R) counts
            the number of such (l, r) in [L, R] where there's no constraint like x
            - count the number of (l, r) where (l = 0, r = 3, l <= x, r >= x) and add that to the number
            of (l = 2, r = 1, l <= x, r >= x)
    - useful ideas:
        - when checking for "number of multiples of x such that x <= r and x == rem (mod m)",
        always check to make sure that r >= rem
        - if we need the number of segments containing some index i satisfying some property,
        the intuitive way is that we count the number of l <= i and the number of r >= i, but
        we can also find the total number of segments and then subtract the segments fully to
        the left of i (r < i) and the segments fully to the right of i (i < l)
    */

    ll n, x;
    cin >> n >> x;

    auto brute_force_range = [](ll left, ll right) {
        vector<pair<ll, ll>> ans;
        for (int l = max(left, 1LL); l <= right; ++l) {
            for (int r = l; r <= right; ++r) {
                if (xor_range(l, r) == 0) {
                    ans.push_back({l, r});
                }
            }
        }
        cout << "left = " << left << ", right = " << right << endl;
        cout << "ans.size() = " << ans.size() << endl;
        cout << "ans = " << ans << endl;
        return ans.size();
    };
    auto brute_force = [&](ll n, ll x) {
        return brute_force_range(0, n) - brute_force_range(0, x - 1) - brute_force_range(x + 1, n);
    };
    // cout << brute_force(n, x) << endl;

    ll ans = ans_range(0, n);
    ans = (ans - ans_range(0, x - 1) + MOD) % MOD;
    ans = (ans - ans_range(x + 1, n) + MOD) % MOD;
    cout << ans << endl;
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
