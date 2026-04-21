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

// counts n such that n mod 4 = r and left <= n <= right
ll count_r_mod_4(ll left, ll right, ll r) {
    assert(0 <= r && r < 4);
    if (right < r) return 0;

    ll mx = (right - r) / 4;
    ll mn = (left - r + 3) / 4;
    return max(0LL, mx - mn + 1);
}

void solve() {
    /*
    - useful ideas:
        - instead of using (l, r), it might be more useful to consider (l - 1, r), especially
        if we're working with prefix sums, because then pref_{l - 1} would need to be exactly
        equal to pref_r
            - only reason i don't do it here is because i'd have to consider that -1 is a possible
            value for l - 1, which can be ugly to implement depending on the implementation
        - if we need two values to be equal in a sequence but some values don't repeat in the
        sequence, then we only need to consider the ones that repeat
    */
    
    ll n, x;
    cin >> n >> x;
    
    ll if_both_3s = (count_r_mod_4(0, x, 0) % MOD) * (count_r_mod_4(x, n, 3) % MOD) % MOD;
    ll if_both_1s = (count_r_mod_4(0, x, 2) % MOD) * (count_r_mod_4(x, n, 1) % MOD) % MOD;
    ll ans = (if_both_3s + if_both_1s) % MOD;
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
