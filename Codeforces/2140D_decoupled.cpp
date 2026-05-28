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

void solve() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> segments(n);
    for (int i = 0; i < n; ++i) {
        cin >> segments[i].first >> segments[i].second;
    }
    sort(segments.begin(), segments.end(), [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
        return a.first + a.second < b.first + b.second;
    });
    if (n == 1) {
        cout << segments[0].second - segments[0].first << "\n";
        return;
    }

    vector<ll> suf_l_plus_r(n, 0);
    ll sum_l = 0;
    for (int i = n - 1; i >= 0; --i) {
        suf_l_plus_r[i] = (i == n - 1 ? 0 : suf_l_plus_r[i + 1]) + segments[i].first + segments[i].second;
        sum_l += segments[i].first;
    }

    ll ans = 0; for (int i = 0; i < n; ++i) ans += segments[i].second - segments[i].first;
    ll added = 0;
    if (n & 1) {
        for (int i = 0; i < n; ++i) {  // brute-forcing the excluded element
            // - in either case, sum_l will subtract the l-value of the excluded segment (segment i)
            // - but if segment i is from the original set of best l+r segments,
            // then we push down our set of best l+r segments by one,
            // and subtract segment i's value of l+r
            ll if_excluding;
            if (i >= (n + 1) / 2) {
                if_excluding = (suf_l_plus_r[n / 2] - (segments[i].first + segments[i].second)) - (sum_l - segments[i].first);
            } else {
                if_excluding = suf_l_plus_r[(n + 1) / 2] - (sum_l - segments[i].first);
            }
            added = max(added, if_excluding);
        }
    } else {
        added = suf_l_plus_r[n / 2] - sum_l;
    }
    ans += added;
    cout << ans << "\n";
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
