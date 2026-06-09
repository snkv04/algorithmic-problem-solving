#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<ll> a;
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

ll nCr(int n, int r) {
    ll num = fac[n];
    ll denom = fac[r] * fac[n - r] % MOD;
    return mod_div(num, denom);
}

ll solve(int l, int r) {
    // solves base case
    if (l == r) {
        return a[l] == 1;
    }
    if (l > r) {
        return 1;
    }

    // does main quicksort logic
    int ptr1 = l, ptr2 = r, idx = -1;
    auto works = [&](int idx) {
        return a[idx] == 1LL * (idx - l + 1) * (r - idx + 1);
    };
    while (ptr1 <= ptr2) {
        if (works(ptr1)) {
            idx = ptr1;
            break;
        }
        if (works(ptr2)) {
            idx = ptr2;
            break;
        }

        ++ptr1;
        --ptr2;
    }
    // cout << "for (l, r) = " << make_pair(l, r) << ", idx = " << idx << endl;

    // recurses
    if (idx == -1) {
        return 0;
    } else {
        ll ans = nCr(r - l, r - idx);
        ans = ans * solve(l, idx - 1) % MOD;
        ans = ans * solve(idx + 1, r) % MOD;
        return ans;
    }
}

void solve() {
    int n;
    cin >> n;
    a = vector<ll>(n);
    cin >> a;

    fac = vector<ll>(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fac[i] = (fac[i - 1] * i) % MOD;
    }

    cout << solve(0, n - 1) << endl;
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
