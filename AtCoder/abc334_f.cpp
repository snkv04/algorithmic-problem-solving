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

ld dist(pair<ll, ll> p1, pair<ll, ll> p2) {
    auto [x1, y1] = p1;
    auto [x2, y2] = p2;
    return sqrt((ld) ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void solve() {
    int n, k;
    cin >> n >> k;
    pair<ll, ll> s;
    vector<pair<ll, ll>> coords = {{0, 0}};
    cin >> s.first >> s.second;
    for (int i = 1; i <= n; ++i) {
        ll x, y;
        cin >> x >> y;
        coords.push_back({x, y});
    }
    // cout << "coords = " << coords << endl;

    vector<ld> pref(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        pref[i] = pref[i - 1] + dist(coords[i - 1], coords[i]);
    }
    // cout << setprecision(12) << pref << endl;

    vector<ld> mem(n + 1, 0);
    vector<ld> val(n + 1, 0);
    val[0] = -pref[1] + dist(s, coords[1]);
    multiset<ld> vals;
    vals.insert(val[0]);
    for (int i = 1; i <= n; ++i) {
        int removing = i - k - 1;
        if (removing >= 0) {
            vals.erase(vals.find(val[removing]));
        }

        mem[i] = dist(coords[i], s) + pref[i] + *vals.begin();
        if (i < n) {
            val[i] = mem[i] - pref[i + 1] + dist(s, coords[i + 1]);
            vals.insert(val[i]);
        }
    }
    cout << fixed << setprecision(12) << mem[n] << endl;
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
