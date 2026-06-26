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
    // assume that everything will work, and build the permutation under the assumption that it will.
    // then, at the end, check if the permutation is valid. if not, then ans is obv no. if yes, then
    // permutation is optimal.

    // reads in input
    int n;
    cin >> n;
    vector<int> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= 2 * n; ++i) {
        if (i <= n) cin >> a[i];
        else cin >> b[i - n];
    }

    // gets cycles
    vector<bool> visited(n + 1, false);
    vector<vector<int>> cycles;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int curr = i;
            vector<int> cycle;
            while (!visited[curr]) {
                cycle.push_back(curr);
                visited[curr] = true;
                curr = a[curr];
            }
            cycles.push_back(cycle);
        }
    }

    // ties each value to the size of its cycle
    vector<int> to_sz(n + 1);
    vector<set<int>> from_sz(n + 1);
    for (auto cycle : cycles) {
        for (auto node : cycle) {
            to_sz[node] = cycle.size();
            from_sz[cycle.size()].insert(node);
        }
    }

    // propagates existing values
    auto propagate = [&](int i) -> bool {
        int start = i;
        do {
            int bi = b[i];
            int ai = a[i];
            int abi = a[bi];
            if (b[ai] != -1 && b[ai] != abi) {
                return false;
            } else {
                b[ai] = abi;
                from_sz[to_sz[bi]].erase(bi);
                i = ai;
            }
        } while (i != start);
        return true;
    };
    for (int i = 1; i <= n; ++i) {
        if (b[i] != -1 && from_sz[to_sz[b[i]]].count(b[i])) {
            if (!propagate(i)) {
                cout << "NO\n";
                return;
            }
        }
    }

    // for each missing value, fill in the best one, then propagate it
    for (int i = 1; i <= n; ++i) {
        if (b[i] == -1) {
            int sz = to_sz[a[i]];
            if (from_sz[sz].empty()) {
                cout << "NO\n";
                return;
            }

            int val = *from_sz[sz].begin();
            b[i] = val;
            if (!propagate(i)) {
                cout << "NO\n";
                return;
            }
        }
    }

    // check if final built permutation is optimal
    for (int i = 1; i <= n; ++i) {
        if (a[b[i]] != b[a[i]]) {
            cout << "NO\n";
            return;
        }
    }

    // output built permutation
    cout << "YES\n";
    for (int i = 1; i <= n; ++i) cout << b[i] << " ";
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
