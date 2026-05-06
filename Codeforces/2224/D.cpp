#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
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

struct Frac {
    Frac() : num(1), denom(1) {}

    Frac(long long n, long long d) : num(n), denom(d) {
        reduce();
    }

    Frac(long long x) : num(x), denom(1) {}

    bool operator<(const Frac &other) const {
        long long new_denom = lcm(denom, other.denom);
        long long num1 = num * (new_denom / denom), num2 = other.num * (new_denom / other.denom);
        return num1 < num2;
    }

    bool operator==(const Frac &other) const {
        Frac frac1 = *this, frac2 = other;
        frac1.reduce(); frac2.reduce();
        return frac1.num == frac2.num && frac1.denom == frac2.denom;
    }

    bool operator!=(const Frac &other) const {
        return !(operator==(other));
    }

    bool operator<=(const Frac &other) const {
        return operator<(other) || operator==(other);
    }

    void reduce() {
        long long g = gcd(num, denom);
        num /= g;
        denom /= g;
        if (denom < 0) {
            num = -num;
            denom = -denom;
        }
    }

    Frac operator+(const Frac &other) {
        long long new_denom = lcm(denom, other.denom);
        long long num1 = num * (new_denom / denom), num2 = other.num * (new_denom / other.denom);
        Frac result(num1 + num2, new_denom);
        result.reduce();
        return result;
    }

    Frac operator-(const Frac &other) {
        return operator+(Frac(-1) * other);
    }

    Frac operator*(const Frac &other) {
        Frac result(num * other.num, denom * other.denom);
        result.reduce();
        return result;
    }

    Frac operator/(const Frac &other) {
        return operator*({other.denom, other.num});
    }

    long long sign() {
        reduce();
        if (num == 0) return 0;
        else if (num > 0) return 1;
        else return -1;
    }

    friend std::ostream& operator<<(std::ostream &os, const Frac &fraction) {
        os << fraction.num << "/" << fraction.denom;
        return os;
    }

    long double to_ld() {
        assert(denom != 0);
        return static_cast<long double>(num) / static_cast<long double>(denom);
    }

private:
    long long num, denom;
};

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

    vector<ld> ratios(n * (n - 1));
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            ratios[idx++] = (ld) b[i] / b[j];
        }
    }
    sort(ratios.begin(), ratios.end());
    // cout << ratios << endl;

    vector<ll> fac(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ld ratio = (ld) a[j] / a[i];
            int l = 0, r = n * (n - 1) - 1, idx = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (ratio < ratios[m]) {
                    idx = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }

            if (idx != -1) {
                ll cnt = n * (n - 1) - idx;
                cnt *= fac[n - 2];
                cnt %= MOD;
                ans += cnt;
                ans %= MOD;
            }
        }
    }
    ans = mod_div(ans, fac[n]);
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
