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

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<ll> suf(n, 0);
    for (int i = n-2; i >= 0; --i) {
        suf[i] = suf[i+1] - a[i+1];
    }
    // cout << "suf = " << suf << endl;

    vector<ll> pref(n, 0);
    for (int i = 1; i < n; ++i) {
        pref[i] = pref[i-1] + abs(a[i-1]);
    }
    // cout << "pref = " << pref << endl;

    ll ans = -1e15;
    for (int i = 0; i < n; ++i) {
        ll curr = pref[i] + suf[i];
        if (i) {
            // if (i == 1) {
                if (a[0] < 0) curr += 2 * a[0];
            // } else {
            //     if (a[0] < 0) curr += 2 * a[0];
            //     if (a[i-1] < 0) curr += 2 * a[i-1];
            // }
        }
        ans = max(ans, curr);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
