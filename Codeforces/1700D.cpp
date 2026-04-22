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

void solve() {
    /*
    - useful ideas:
        - assuming we are fixing k pipes to be open, putting all k of our open pipes on the left
        will either not change the amount of time at all or strictly improve it
        - for a given prefix, where the number of open pipes is <= the prefix size, the amount of time it takes
        to fill the prefix is the intuitive, expected time (total volume of prefix over number of open pipes)
        UNLESS something to the left is bottlenecking us
    */

    int n;
    cin >> n;
    vector<ll> v(n);
    cin >> v;
    v.insert(v.begin(), 0);

    vector<ll> pref_volume(n + 1, 0), pref_time(n + 1, 0), total_time(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pref_volume[i] = pref_volume[i - 1] + v[i];
    }
    for (int i = 1; i <= n; ++i) {
        pref_time[i] = max((pref_volume[i] + i - 1) / i, i == 1 ? 0 : pref_time[i - 1]);
        total_time[i] = max((pref_volume[n] + i - 1) / i, pref_time[i]);
    }

    int q;
    cin >> q;
    while (q--) {
        ll t;
        cin >> t;
        if (t < total_time[n]) {
            cout << -1 << endl;
        } else {
            int l = 1, r = n, ans = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (total_time[m] <= t) {
                    ans = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            cout << ans << endl;
        }
    }
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
