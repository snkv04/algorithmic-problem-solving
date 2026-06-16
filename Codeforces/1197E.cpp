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
    vector<array<int, 3>> dolls(n);
    for (int i = 0; i < n; ++i) {
        dolls[i][0] = i;
        cin >> dolls[i][2] >> dolls[i][1];
    }

    auto by_in = dolls, by_out = dolls;
    sort(by_in.begin(), by_in.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[1] < b[1];
    });
    sort(by_out.begin(), by_out.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[2] < b[2];
    });

    int l = 0, r = 0;
    vector<ll> min_space(n, 1e9), num_ways(n, 0);
    map<ll, ll> key_to_ways, key_to_cnt;
    auto deactivate = [&](int idx) {
        // cout << "deactivating " << dolls[idx] << endl;
        ll key = min_space[idx] - dolls[idx][2];
        key_to_ways[key] += MOD - num_ways[idx];
        key_to_ways[key] %= MOD;
        key_to_cnt[key] += 1;

        if (key_to_cnt[key] == 0) {
            key_to_cnt.erase(key);
            key_to_ways.erase(key);
        }
    };
    auto activate = [&](int idx) {
        // cout << "activating " << dolls[idx] << endl;
        ll key = min_space[idx] - dolls[idx][2];
        key_to_ways[key] += num_ways[idx];
        key_to_ways[key] %= MOD;
        key_to_cnt[key] += 1;

        while (by_out[l][2] <= dolls[idx][1]) {
            deactivate(by_out[l++][0]);
        }
    };
    for (int i = 0; i < n; ++i) {
        auto [idx, in, out] = by_in[i];
        // cout << "currently on " << by_in[i] << endl;
        while (by_out[r][2] <= in) {
            activate(by_out[r++][0]);
        }

        if (key_to_ways.empty()) {
            min_space[idx] = in;
            num_ways[idx] = 1;
        } else {
            min_space[idx] = in + key_to_ways.begin()->first;
            num_ways[idx] = key_to_ways.begin()->second;
        }
        // cout << "min space = " << min_space[idx] << ", num ways = " << num_ways[idx] << endl;
    }

    ll final_min_space = 1e9;
    for (int i = 0; i < n; ++i) {
        if (dolls[i][2] > by_in[n - 1][1]) {
            final_min_space = min(final_min_space, min_space[i]);
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (dolls[i][2] > by_in[n - 1][1] && min_space[i] == final_min_space) {
            ans += num_ways[i];
            ans %= MOD;
        }
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
