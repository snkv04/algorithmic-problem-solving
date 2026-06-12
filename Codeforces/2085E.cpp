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
    vector<ll> a(n), b(n);
    cin >> a >> b;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    bool same = true;
    for (int i = 0; i < n; ++i) if (a[i] != b[i]) same = false;
    if (same) {
        cout << a[n - 1] + 1 << endl;
        return;
    }
    if (b[n - 1] >= a[n - 1]) {
        cout << -1 << endl;
        return;
    }

    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        sum -= b[i];
    }
    if (sum <= 0) {
        cout << -1 << endl;
        return;
    }

    vector<int> candidates;
    ll rt = sqrt(sum);
    for (int i = 1; i <= rt; ++i) {
        if (sum % i == 0) {
            if (i > b[n - 1] && i <= a[n - 1]) candidates.push_back(i);
            if (!(rt * rt == sum && i == rt) && sum / i > b[n - 1] && sum / i <= a[n - 1]) candidates.push_back(sum / i);
        }
    }

    map<int, int> bms;
    for (int i = 0; i < n; ++i) bms[b[i]] += 1;
    auto check = [&](map<int, int> &ams) -> bool {
        if (ams.size() != bms.size()) return false;

        auto ita = ams.begin(), itb = bms.begin();
        while (ita != ams.end() && itb != bms.end()) {
            if (ita->first != itb->first || ita->second != itb->second) return false;
            ++ita;
            ++itb;
        }
        return true;
    };
    for (int k : candidates) {
        map<int, int> rems;
        for (int i = 0; i < n; ++i) {
            rems[a[i] % k] += 1;
        }

        if (check(rems)) {
            cout << k << endl;
            return;
        }
    }
    cout << -1 << endl;
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
