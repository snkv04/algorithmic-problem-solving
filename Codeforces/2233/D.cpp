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
    vector<int> a(n);
    cin >> a;

    auto build_blocks = [](vector<int> &a) {
        map<int, vector<pair<int, int>>> blocks;
        for (int i = 0; i < a.size(); ++i) {
            if (blocks[a[i]].size() && blocks[a[i]].back().second == i - 1) {
                blocks[a[i]].back().second = i;
            } else {
                blocks[a[i]].push_back(make_pair(i, i));
            }
        }
        return blocks;
    };
    auto blocks = build_blocks(a);
    
    int cnt = 0, mx = 0;
    for (auto [k, v] : blocks) {
        if (v.size() > 1) ++cnt;
        mx = max(mx, (int) v.size());
    }
    if (mx >= 4 || cnt >= 3) {
        cout << "NO\n";
        return;
    }
    if (mx == 1) {
        cout << "YES\n";
        return;
    }

    // don't even need this
    // int num1 = -1, num2 = -1;
    // for (auto [k, v] : blocks) {
    //     if (v.size() >= 2) {
    //         if (num1 == -1) num1 = k;
    //         else num2 = k;
    //     }
    // }

    vector<pair<int, int>> candidates;
    for (auto [k, v] : blocks) {
        if (v.size() >= 2) {
            int moving = v.back().second;
            if (v[0].first > 0) {
                candidates.push_back({v[0].first - 1, moving});
            }
            candidates.push_back({v[0].second + 1, moving});

            moving = v[0].first;
            if (v.back().second < n - 1) {
                candidates.push_back({moving, v.back().second + 1});
            }
            candidates.push_back({moving, v.back().first - 1});
        }
    }

    auto check = [&](int l, int r) -> bool {
        swap(a[l], a[r]);

        auto b = build_blocks(a);
        for (auto [k, v] : b) {
            if (v.size() > 1) {
                swap(a[l], a[r]);
                return false;
            }
        }

        swap(a[l], a[r]);
        return true;
    };
    for (auto [l, r] : candidates) {
        if (check(l, r)) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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
