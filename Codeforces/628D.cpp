#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int m, d;
ll mem[2000][2][2000][2];

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

ll dfs(int idx, bool step, int rem, int loose, string &str) {
    if (idx == str.size()) {
        return rem == 0;
    }
    if (mem[idx][step][rem][loose] != -1) {
        return mem[idx][step][rem][loose];
    }

    int curr_digit = str[idx] - '0';
    array<int, 10> next; for (int i = 0; i < 10; ++i) next[i] = -1;
    if (step) {
        if (!loose && d > curr_digit) {
            return mem[idx][step][rem][loose] = 0;
        }
        next[0] = d;
    } else {
        int mx = 9;
        if (!loose) mx = curr_digit;

        int ptr = 0;
        for (int i = 0; i <= mx; ++i) {
            if (i != d) next[ptr++] = i;
        }
    }

    ll result = 0;
    for (int digit : next) {
        if (digit == -1) break;

        result += dfs(idx + 1, !step, (rem * 10 + digit) % m, loose || digit < curr_digit, str);
        result %= MOD;
    }
    return mem[idx][step][rem][loose] = result;
}

ll solve(string str) {
    for (int i = 0; i < 2000; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2000; ++k) {
                fill(mem[i][j][k], mem[i][j][k] + 2, -1);
            }
        }
    }
    return dfs(0, 0, 0, 0, str);
}

void solve() {
    cin >> m >> d;
    string a, b;
    cin >> a >> b;

    ll ans = (solve(b) - solve(a) + MOD) % MOD;
    auto check = [&]() {
        for (int i = 0; i < a.size(); ++i) {
            int digit = a[i] - '0';
            if ((i % 2 && digit != d) || (i % 2 == 0 && digit == d)) return false;
        }

        ll rem = 0, multiplier = 1;
        for (int i = a.size() - 1; i >= 0; --i) {
            rem += (a[i] - '0') * multiplier;
            rem %= m;  // need to make sure to use the right mod given the context here
            multiplier *= 10;
            multiplier %= m;  // and here
        }
        return rem == 0;
    };
    if (check()) {
        ans = (ans + 1) % MOD;
    }
    cout << ans << endl;
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
