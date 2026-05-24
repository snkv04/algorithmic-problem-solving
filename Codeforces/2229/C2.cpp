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
    vector<ll> a(n);
    cin >> a;
    a.insert(a.begin(), 0);

    vector<ll> pref(n + 2, 0), suf(n + 2, 0);
    for (int i = 1; i <= n + 1; ++i) {
        int val = i <= n ? a[i] : 0;
        pref[i] = pref[i - 1] + abs(val);
    }
    for (int i = n; i >= 0; --i) {
        suf[i] = suf[i + 1] + a[i];
    }

    ll best = suf[1]; int bestidx = -1;
    for (int i = 1; i <= n; ++i) {
        if (a[i] > 0 && pref[i - 1] + suf[i + 1] + -a[i] > best) {
            best = -a[i] + pref[i - 1] + suf[i + 1];
            bestidx = i;
        }
    }
    if (bestidx == -1) {
        cout << "0\n\n";
        return;
    }

    vector<int> ops;
    int sufops = 0;
    for (int i = bestidx - 1; i >= 1; --i) {
        int curr = a[i] < 0;
        curr += sufops;
        if (curr % 2 == 0) {
            ++sufops;
            ops.push_back(i);
        }
    }
    sufops += 1;  // no-op
    ops.push_back(bestidx);
    
    cout << ops.size() << "\n";
    for (int idx : ops) cout << idx << " ";
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
