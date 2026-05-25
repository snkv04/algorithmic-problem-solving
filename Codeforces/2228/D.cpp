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
    vector<pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].first >> points[i].second;
    }

    sort(points.begin(), points.end(), [&](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });
    vector<int> idx(n + 1);
    int timer = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || points[i].second != points[i - 1].second) {
            idx[points[i].second] = timer++;
        }
    }
    sort(points.begin(), points.end());

    vector<int> prefminy(n), prefmaxy(n), sufminy(n), sufmaxy(n);
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            prefminy[i] = prefmaxy[i] = points[i].second;
        } else {
            prefminy[i] = min(prefminy[i - 1], points[i].second);
            prefmaxy[i] = max(prefmaxy[i - 1], points[i].second);
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
            sufminy[i] = sufmaxy[i] = points[i].second;
        } else {
            sufminy[i] = min(sufminy[i + 1], points[i].second);
            sufmaxy[i] = max(sufmaxy[i + 1], points[i].second);
        }
    }

    ll ans = 0;
    for (int i = 1; i < n - 2; ++i) {
        if (points[i].first == points[i + 1].first) continue;

        int miny = max(prefminy[i], sufminy[i + 1]);
        int maxy = min(prefmaxy[i], sufmaxy[i + 1]);
        if (miny >= maxy) continue;

        int r = idx[maxy], l = idx[miny];
        int between = r - l - 1;
        ans += between + 1;
    }
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
