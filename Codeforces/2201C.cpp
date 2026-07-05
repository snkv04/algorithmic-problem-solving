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

    vector<int> balance(n, 0);
    int b = 0;
    for (int i = 0; i < n; ++i) {
        b += (s[i] == '(') ? 1 : -1;
        balance[i] = b;
    }

    /*
    - let mem[i] = # of subsequences S with index i as the last element, such that if S was rotated, the whole
    string would remain an RBS
    - let mem2[i] = # of subsequences S with index i as the last element, such that if the subsequence had a ")"
    appended to it from the right and was only then rotated, the whole string would remain an RBS
        - keep in mind that, if everything at i or to the left is safe, then nothing to the right would become
        unsafe, because a ")" can only go up or stay the same
    - then, mem[i] = 2^(i - 1) if s[i] == '(' and mem2[i] if s[i] == ')'
    - and answer = sum(mem)
    */
    vector<ll> mem2(n, 0), pref_close(n, 0), pref_open(n, 0);
    ll ans = 0;
    int bound = 0;
    for (int r = 0; r < n; ++r) {
        // preprocessing for this index
        if (r) {
            pref_close[r] = pref_close[r - 1];
            pref_open[r] = pref_open[r - 1];
        }

        // subsequence including only this element
        mem2[r] = 1;

        // subsequence with last element at r and having second-to-last element be a ')' is always fine
        // for (int l = r - 1; l >= 0; --l) {
        //     if (s[l] == ')') {
        //         mem2[r] += mem2[l];
        //         mem2[r] %= MOD;
        //     }
        // }
        mem2[r] += pref_close[r];
        mem2[r] %= MOD;

        // subsequence with last element at r and second-to-last at '(' must maintain that property of
        // the balance being >= 2 after that '('
        // for (int l = r - 1; l >= 0; --l) {
        //     if (balance[l] < 2) break;

        //     if (s[l] == '(') {
        //         mem2[r] += mem2[l];
        //         mem2[r] %= MOD;
        //     }
        // }
        mem2[r] += pref_open[r] - pref_open[bound] + MOD;
        mem2[r] %= MOD;

        // increments answer
        if (s[r] == ')') {
            ans += mem2[r];
        } else {
            ans += mod_pow(2, r);
        }
        ans %= MOD;

        // post-processing for this index
        if (s[r] == ')') {
            pref_close[r] += mem2[r];
            pref_close[r] %= MOD;
        } else {
            pref_open[r] += mem2[r];
            pref_open[r] %= MOD;
        }
        if (balance[r] < 2) bound = r;
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
