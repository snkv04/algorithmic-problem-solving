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

void solve() {
    int n, h;
    cin >> n >> h;
    vector<int> a(n);
    cin >> a;

    // gets the amount of water consumed by a single sink placed on top of the dirt on column i
    vector<ll> cnt(n, 0);
    for (int i = 0; i < n; ++i) {
        cnt[i] = h - a[i];
        int mx = a[i];
        for (int j = i - 1; j >= 0; --j) {
            mx = max(mx, a[j]);
            cnt[i] += h - mx;
        }
        mx = a[i];
        for (int j = i + 1; j < n; ++j) {
            mx = max(mx, a[j]);
            cnt[i] += h - mx;
        }
    }

    // we brute-force over all pairs of sinks, and for each, we get the total amount of water consumed by
    // one OR the other by adding up the water for each and subtracting the shared amount; the shared amount
    // is obtained by picking some column with maximum height between them and getting the water consumed by
    // a sink placed on top of it
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int k = i;
        for (int j = i; j < n; ++j) {
            if (a[j] > a[k]) {
                k = j;
            }
            ans = max(ans, cnt[i] + cnt[j] - cnt[k]);
        }
    }
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
