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
    /*
    - interesting bound: we basically want to pack the bits of c into the elements of a. we could go and perform the actual
    increase operations on the elements of a, and reverse them after each query, since there are at most 30 operations performed
    per query. however, observe that what this also means is that we are using at most 30 elements of a. so we can just make a
    copy of the 30 best elements of a for each query, and use that copy, without ever modifying a.
    - main algorithm: iterate through bits of c from high to low, and for each active bit, use the maximum element of a to handle
    that bit, increasing it with coins if necessary. we subtract the bit from that element of a, as that much has been "used"
    from that element.
    */

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    sort(a.begin(), a.end());

    while (q--) {
        int c;
        cin >> c;

        vector<int> b(min(30, (int) a.size()));
        std::copy(a.begin() + max(0, (int) a.size() - 30), a.end(), b.begin());
        int ans = 0;
        for (int i = 29; i >= 0; --i) {
            if ((c >> i) & 1) {
                sort(b.begin(), b.end());
                if (b.back() < (1 << i)) {
                    ans += (1 << i) - b.back();
                    b.back() = (1 << i);
                }
                b.back() -= (1 << i);
            }
        }
        cout << ans << "\n";
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
