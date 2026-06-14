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
    int n, q;
    cin >> n >> q;
    vector<int> h(n);
    cin >> h;

    vector<vector<array<int, 3>>> queries(n);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        queries[l].push_back({l, r, i});
    }

    vector<int> next(n);
    stack<int> stk;
    for (int i = 0; i <= n; ++i) {
        int val = i == n ? 2e9 : h[i];
        while (stk.size() && val > h[stk.top()]) {
            next[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }

    vector<int> ans(q);
    vector<pair<int, int>> blocks;  // imagine the vector going backwards and also being a stack :)
    for (int i = n - 1; i >= 0; --i) {
        int r = next[i] - 1;
        while (blocks.size() && r >= blocks.back().first) {
            blocks.pop_back();
        }
        blocks.push_back({i, r});

        // now we just count blocks for each query
        for (auto [l, r, qi] : queries[i]) {
            int lo = 0, hi = blocks.size() - 1, idx = -1;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (r >= blocks[mid].first) {
                    idx = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            ans[qi] = blocks.size() - idx;
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
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
