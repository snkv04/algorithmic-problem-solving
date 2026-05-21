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
    string s;
    cin >> s;
    vector<ll> a(n), c(n);
    cin >> a >> c;

    for (int i = 0; i < n - 1; ++i) {
        if (c[i] > c[i + 1]) {
            cout << "NO\n";
            return;
        }
    }
    if (s[0] == '1' && a[0] != c[0]) {
        cout << "NO\n";
        return;
    }
    a[0] = c[0];
    
    vector<int> bounds = {0};
    for (int i = 1; i <= n; ++i) {
        ll val = i < n ? c[i] : 1e18;
        if (val > c[i - 1]) bounds.push_back(i);
    }
    // cout << "bounds = " << bounds << endl;

    for (int i = 0; i < bounds.size() - 1; ++i) {
        int l = bounds[i] + 1, r = bounds[i + 1];
        // cout << "l = " << l << ", r = " << r << endl;
        ll sum = 0;
        vector<int> changable;
        for (int j = l; j <= min(n - 1, r); ++j) {
            if (s[j] == '0') {
                changable.push_back(j);
                if (j == r) {
                    a[j] = 1e16;
                }
            }
            sum += a[j];

            ll bound = (j == r) ? (c[r] - c[r - 1]) : 0;
            // cout << "j = " << j << ", bound = " << bound << ", stack = " << changable << endl;
            if (sum > bound) {
                if (changable.empty()) {
                    cout << "NO\n";
                    return;
                }
                int idx = changable.back();
                ll diff = sum - bound;
                sum = bound;
                a[idx] -= diff;
            }
            if (j == r) {
                if (sum < bound) {
                    // might break the segment, so have to check again
                    if (changable.empty()) {
                        cout << "NO\n";
                        return;
                    }

                    ll diff = bound - sum;
                    int idx = changable.back();
                    sum = bound;
                    a[idx] += diff;
                }
            }
        }

        sum = 0;
        for (int j = l; j <= min(n - 1, r); ++j) {
            sum += a[j];
            if (j < r) {
                if (sum > 0) {
                    cout << "NO\n";
                    return;
                }
            } else {
                assert(j == r);
                if (sum < c[j] - c[j - 1]) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
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
