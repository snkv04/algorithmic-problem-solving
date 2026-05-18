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
    int n;
    cin >> n;
    vector<ll> c(n);
    cin >> c;
    ll sum = std::accumulate(c.begin(), c.end(), 0LL);
    if (sum == n) {
        cout << 0 << endl;
        return;
    }

    if (n <= 2) {
        if (sum >= 3) {
            cout << sum << endl;
        } else {
            cout << 0 << endl;
        }
        return;
    }

    if (c[n - 2] == 1) {
        ll individual = n - 1;
        ll ans = c[n - 1] + min(individual, c[n - 1] / 2);
        cout << ans << endl;
    } else {
        ll individual = 0;
        vector<ll> blocks;
        for (int i = 0; i < n; ++i) {
            if (c[i] == 1) ++individual;
            else blocks.push_back(c[i]);
        }

        ll ans = 0;
        for (ll block : blocks) {
            ans += block;
            if (block >= 4) {
                ll taking = min(block / 2 - 1, individual);
                ans += taking;
                individual -= taking;
            }
        }
        cout << ans << endl;
    }
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
