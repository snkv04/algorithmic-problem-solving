#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<ll> fac;

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

ll nCr(ll n, ll r) {
    ll num = fac[n];
    ll denom = fac[r] * fac[n - r] % MOD;
    return mod_div(num, denom);
}

void solve() {
    // reads in input
    int n;
    cin >> n;
    vector<ll> b(n);
    cin >> b;
    b.insert(b.begin(), 0);

    // finds the number of times each bit appears
    vector<int> ans(29, 0);
    for (int i = n; i >= 1; --i) {
        // removes the contribution of all bits that appear more than k (i) times
        for (int bit = 0; bit < 29; ++bit) {
            ll num_times = ans[bit];
            if (num_times > i) {
                ll subseqs = nCr(num_times, i);
                ll contribution = subseqs * (1 << bit) % MOD;
                b[i] -= contribution;
                b[i] = (b[i] + MOD) % MOD;
            }
        }

        // finds all bits that appear EXACTLY i times, and mark them down
        if (b[i] > 0) {
            for (int bit = 0; bit < 29; ++bit) {
                if ((b[i] >> bit) & 1) {
                    ans[bit] = i;
                }
            }
        }
    }

    // given the count of each bit, constructs the array
    vector<int> a(n, 0);
    for (int bit = 0; bit < 29; ++bit) {
        for (int i = 0; i < ans[bit]; ++i) {
            a[i] += 1 << bit;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fac.resize(1e5 + 1);
    fill(fac.begin(), fac.end(), 1);
    for (int i = 1; i <= 1e5; ++i) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
