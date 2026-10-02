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
    int n, m, k, d, s, t;
    cin >> n >> m >> k >> d >> s >> t;
    vector<vector<pair<int, int>>> adj(n + 1);
    while (m--) {
        int a, b, l;
        cin >> a >> b >> l;
        adj[a].push_back({b, l});
        adj[b].push_back({a, l});
    }
    vector<map<int, set<int>>> stretches(n + 1);
    while (k--) {
        int a, b, c;
        cin >> a >> b >> c;
        stretches[b][a].insert(c);
        // cout << "read in stretch " << a << "-" << b << "-" << c << endl;
    }

    vector<vector<vector<int>>> dist(n + 1, vector<vector<int>>(n + 1, vector<int>(101, 1e9)));
    // int dist[n + 1][n + 1][d + 1];
    // for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) fill(dist[i][j], dist[i][j] + d + 1, 1e9);
    dist[s][0][0] = 0;
    priority_queue<array<int, 4>> pq;
    pq.push({0, s, 0, 0});
    while (pq.size()) {
        auto [distance, curr, prev, len] = pq.top();
        pq.pop();
        distance *= -1;
        if (distance > dist[curr][prev][len]) continue;

        for (auto [next, weight] : adj[curr]) {
            if (next == prev) continue;
            
            int new_distance = distance + weight;
            int new_curr = next, new_prev = curr, new_len;
            if (stretches[curr].count(prev) && stretches[curr][prev].count(next)) {
                if (len + weight > d) {
                    continue;
                } else {
                    new_len = len + weight;
                }
            } else if (stretches[next].count(curr)) {
                new_len = weight;
            } else {
                new_len = 0;
            }

            if (new_distance < dist[new_curr][new_prev][new_len]) {
                dist[new_curr][new_prev][new_len] = new_distance;
                pq.push({-new_distance, new_curr, new_prev, new_len});
            }
        }
    }

    int ans = 1e9;
    for (int p = 0; p <= n; ++p) for (int len = 0; len <= 100; ++len) ans = min(ans, dist[t][p][len]);
    cout << (ans == 1e9 ? "impossible" : to_string(ans)) << endl;
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
