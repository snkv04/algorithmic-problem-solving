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
    int n, m;
    cin >> n >> m;
    vector<ll> a(n), k(m);
    cin >> a >> k;
    vector<ll> inva(n);
    for (int i = 0; i < n; ++i) {
        inva[i] = mod_inv(a[i]);
    }

    // get term 1 (sum of all subarrays)
    ll term1 = 0;
    for (int i = 0; i < n; ++i) {
        term1 += inva[i] * (i + 1) % MOD * (n - i) % MOD;
        term1 %= MOD;
    }

    // prep for term 2
    vector<int> left(n), right(n);
    stack<int> stk;
    for (int i = n - 1; i >= -1; --i) {
        int val = i == -1 ? 0 : a[i];
        while (stk.size() && a[stk.top()] >= val) {
            left[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    stk.pop();
    for (int i = 0; i <= n; ++i) {
        int val = i == n ? 0 : a[i];
        while (stk.size() && val < a[stk.top()]) {
            right[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }

    // get term 2 (sum of all negations of terms times their counts)
    vector<ll> cnt(n, 0);
    ll term2 = 0;
    for (int i = 0; i < n; ++i) {
        cnt[i] = (ll) (i - left[i]) * (right[i] - i) % MOD;
        term2 += (MOD - inva[i]) % MOD * cnt[i] % MOD;
        term2 %= MOD;
    }

    // prep for term 3 (sort all b's, then get prefix and suffix values)
    vector<array<ll, 3>> sorted;
    for (int i = 0; i < n; ++i) {
        sorted.push_back({a[i], inva[i], cnt[i]});
    }
    sort(sorted.begin(), sorted.end());
    vector<ll> cnt_pref(n, 0), negb_pref(n, 0);
    for (int i = 0; i < n; ++i) {
        ll last = i == 0 ? 0 : cnt_pref[i - 1];
        cnt_pref[i] = (last + sorted[i][2]) % MOD;
        last = i == 0 ? 0 : negb_pref[i - 1];
        negb_pref[i] = (last + (MOD - sorted[i][0]) % MOD * sorted[i][2] % MOD) % MOD;
    }
    vector<ll> frac_suf(n, 0);
    for (int i = n - 1; i >= 0; --i) {
        ll last = (i == n - 1) ? 0 : frac_suf[i + 1];
        frac_suf[i] = (last + sorted[i][1] * sorted[i][2] % MOD) % MOD;
    }

    // get term 3 for each k
    for (int i = 0; i < m; ++i) {
        // binary search to find min b_i (when they're sorted) that's >= k + 1
        int k_i = k[i];
        int l = 0, r = n - 1, idx = n;
        while (l <= r) {
            int m = (l + r) / 2;
            if (sorted[m][0] >= k_i + 1) {
                idx = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        // one-shot both the prefix (where all 1/b_i interact in the same way with k) and the
        // suffix (where all 1/b_i interact in the same way with k)
        ll term3 = 0;
        if (idx != 0) {
            int end = idx - 1;
            term3 += (k_i + 2) * cnt_pref[end] % MOD + negb_pref[end];
            term3 %= MOD;
        }
        if (idx != n) {
            int start = idx;
            term3 += (k_i + 1) * frac_suf[start] % MOD;
            term3 %= MOD;
        }
        ll ans = (term1 + term2 + term3) % MOD;
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
