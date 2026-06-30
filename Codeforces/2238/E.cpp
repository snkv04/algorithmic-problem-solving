#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
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
    string s;
    cin >> s;

    vector<vector<int>> mem(n + 1, vector<int>(n + 1, 1e9));
    mem[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> nmem(n + 1, vector<int>(n + 1, 1e9));
        for (int prev_suf_sum = 0; prev_suf_sum <= n; ++prev_suf_sum) {
            for (int cnt_f = 0; cnt_f <= n; ++cnt_f) {
                if (s[i] != 'F') {
                    // we have T here
                    int suf_sum = max(0, prev_suf_sum - 1);
                    int new_cnt_f = cnt_f;
                    int max_sub_sum = max(mem[prev_suf_sum][cnt_f], suf_sum);
                    nmem[suf_sum][new_cnt_f] = min(nmem[suf_sum][new_cnt_f], max_sub_sum);
                }
                if (s[i] != 'T' && prev_suf_sum < n && cnt_f < n) {
                    // we have F here
                    int suf_sum = prev_suf_sum + 1;
                    int new_cnt_f = cnt_f + 1;
                    int max_sub_sum = max(mem[prev_suf_sum][cnt_f], suf_sum);
                    nmem[suf_sum][new_cnt_f] = min(nmem[suf_sum][new_cnt_f], max_sub_sum);
                }
            }
        }
        mem = std::move(nmem);
    }

    int ans = -1e9;
    for (int suf_sum = 0; suf_sum <= n; ++suf_sum) {
        for (int cnt_f = 0; cnt_f <= n; ++cnt_f) {
            ans = max(ans, cnt_f - mem[suf_sum][cnt_f]);
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
