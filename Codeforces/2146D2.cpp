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

ll highest(ll l, ll r) {
    ll b = 30;
    while ((l & (1LL << b)) == (r & (1LL << b))) --b;
    return b;
}

ll above(ll num, ll b) {
    ll ans = 0;
    for (ll i = b + 1; i <= 30; ++i) {
        ans += num & (1LL << i);
    }
    return ans;
}

void solve() {
    ll initl, initr;
    cin >> initl >> initr;
    ll l = initl, r = initr;

    map<ll, ll> mp;
    while (true) {
        if (l == r) {
            mp[l] = r;
            break;
        }

        ll h = highest(l, r);
        ll same = above(l, h);
        ll flipper = (1LL << (h + 1)) - 1;
        // cout << "l = " << l << ", r = " << r << ", h = " << h << ", same = " << same << ", flipper = " << flipper << endl;

        ll curr = same + (1LL << h);
        ll other = curr - 1;
        while (curr <= r && other >= l) {
            mp[curr] = other;
            mp[other] = curr;
            ++curr;
            --other;
        }

        if (curr > r && other < l) {
            break;
        } else if (curr > r) {
            r = other;
        } else {
            l = curr;
        }
    }

    ll ans = 0;
    for (auto [k, v] : mp) ans += k | v;
    cout << ans << "\n";
    for (auto [k, v] : mp) cout << v << " ";
    cout << "\n";
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
