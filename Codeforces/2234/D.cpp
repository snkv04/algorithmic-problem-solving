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

string string_xor(string &a, string &b) {
    int n = a.size();
    string c(n, ' ');
    for (int i = 0; i < n; ++i) {
        c[i] = (a[i] == b[i]) ? '0' : '1';
    }
    return c;
}

void solve() {
    int n, k;
    cin >> n >> k;
    string a, b;
    cin >> a >> b;
    string x = string_xor(a, b);

    auto bruteforce = [&]() {
        map<int, string> mp;
        mp[1] = a;
        mp[(1 << k) + 1] = b;
        for (int i = 1; i <= k; ++i) {
            map<int, string> newmp = mp;
            for (auto it = mp.begin(); ; ++it) {
                auto nextit = it;
                ++nextit;
                if (nextit == mp.end()) break;

                newmp[(it->first + nextit->first) / 2] = string_xor(it->second, nextit->second);
            }
            mp = std::move(newmp);
        }

        int acnt = 0, bcnt = 0, xcnt = 0;
        for (auto [k, v] : mp) {
            cout << v << "\n";
            if (v == a) {
                ++acnt;
            } else if (v == b) {
                ++bcnt;
            } else if (v == x) {
                ++xcnt;
            } else {
                throw std::runtime_error("huh?");
            }
        }
        cout << acnt << " " << bcnt << " " << xcnt << endl;
    };
    // bruteforce();

    ll pa = 0, pb = 0, px = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == '1') ++pa;
        if (b[i] == '1') ++pb;
        if (x[i] == '1') ++px;
    }
    pa *= (n - pa);
    pb *= (n - pb);
    px *= (n - px);

    ll len = (1LL << k) + 1;
    if (k % 2) {
        assert(len % 3 == 0);
        pa *= (len / 3);
        pb *= (len / 3);
        px *= (len / 3);
    } else {
        ++len;
        pa *= (len / 3);
        pb *= (len / 3);
        px *= (len / 3 - 1);
    }
    cout << pa + pb + px << "\n";
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
