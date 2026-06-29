#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<bool> is_prime;
vector<set<int>> prime_divs;

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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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
    vector<int> a(n), b(n);
    cin >> a >> b;
    // if (n > 20000) {
    //     cout << "0\n";
    //     return;
    // }

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        for (int p : prime_divs[a[i]]) {
            if (seen.count(p)) {
                cout << "0\n";
                return;
            }
            seen.insert(p);
        }
    }

    if (seen.count(2)) {
        ll ans = 1e18;
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2) {
                ans = min(ans, (ll) b[i]);
            }
        }
        
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2 == 0) {  // doesn't even matter if even-valued a[i] doesn't have min b[i], there's only one so check it anyway
                int minlen = 1e9;
                for (int p : seen) {
                    if (prime_divs[a[i]].count(p)) continue;

                    int rem = a[i] % p;
                    assert(rem != 0);
                    minlen = min(minlen, p - rem);
                }
                ans = min(ans, (ll) minlen * b[i]);
                break;
            }
        }
        cout << ans << endl;
    } else {
        int minb = 1e9, minb2 = 1e9;
        for (int i = 0; i < n; ++i) {
            if (b[i] <= minb) {
                minb2 = minb;
                minb = b[i];
            } else if (b[i] < minb2) {
                minb2 = b[i];
            }
        }

        ll ans = minb + minb2;
        for (int i = 0; i < n; ++i) {  // can just iterate through all i instead of only through i where b[i] != minb
            int newval = a[i] + 1;
            for (int p : prime_divs[newval]) {
                if (seen.count(p)) {
                    ans = min(ans, (ll) b[i]);
                    break;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (b[i] == minb) {  // if there are multiple i with b[i] = minb, then doesn't matter, we can take any
                int minlen = 1e9;
                for (int p : seen) {
                    if (prime_divs[a[i]].count(p)) continue;

                    int rem = a[i] % p;
                    assert(rem != 0);
                    minlen = min(minlen, p - rem);
                }
                ans = min(ans, (ll) minlen * b[i]);
                break;
            }
        }
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    is_prime = vector<bool>(3e5 + 1, true);
    for (int d = 2; d <= 3e5; ++d) {
        for (int m = 2 * d; m <= 3e5; m += d) {
            is_prime[m] = false;
        }
    }

    prime_divs.resize(3e5 + 1);
    for (int p = 2; p <= 3e5; ++p) {
        if (!is_prime[p]) continue;

        for (int m = p; m <= 3e5; m += p) {
            prime_divs[m].insert(p);
        }
    }
    // for (int i = 1; i <= 20; ++i) {
    //     cout << "prime_divs[" << i << "] = " << prime_divs[i] << endl;
    // }
    
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
