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
    ll s, k;
    cin >> s >> k;
    if (s % 10 == 5 || s % 10 == 0) {
        cout << max(s * k, (s + (s % 10)) * (k - 1)) << endl;
        return;
    }

    vector<int> cycle = {2, 4, 8, 6};
    ll ans = 0;
    if (std::find(cycle.begin(), cycle.end(), s % 10) == cycle.end()) {
        ans = s * k;
        s += s % 10;
        k -= 1;
    }

    if (k < 4) {
        while (k) {
            ans = max(ans, s * k);
            s += s % 10;
            k -= 1;
        }
        cout << ans << endl;
        return;
    }

    while (cycle[0] != s % 10) {
        std::rotate(cycle.begin(), cycle.begin() + 1, cycle.end());
    }
    auto val = [&](ll ops) {
        ll news = s;
        for (int i = 0; i < ops % 4; ++i) news += news % 10;
        news += 20 * (ops / 4);

        ll discounts = k - ops;
        return news * discounts;
    };
    for (int start = 0; start < 4; ++start) {
        ll lidx = 0, ridx = (k - 1 - start) / 4;
        while (ridx - lidx >= 3) {
            ll m1 = lidx + (ridx - lidx) / 3, m2 = ridx - (ridx - lidx) / 3;
            ll ops1 = m1 * 4 + start, ops2 = m2 * 4 + start;
            if (val(ops1) <= val(ops2)) {
                lidx = m1;
            } else {
                ridx = m2;
            }
        }

        for (ll i = lidx; i <= ridx; ++i) {
            ll ops = start + i * 4;
            ans = max(ans, val(ops));
        }
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
