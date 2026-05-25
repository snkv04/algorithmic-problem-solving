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

vector<vector<int>> build(string &s) {
    int n = s.size();
    stack<int> stk;
    int idx = 0;
    vector<vector<int>> adj(n / 2);
    for (char c : s) {
        if (c == '(') {
            if (stk.size())
                adj[stk.top()].push_back(idx);
            stk.push(idx++);
        } else {
            stk.pop();
        }
    }
    return adj;
}

int dfs(int node, vector<vector<int>> &adj) {
    int val = adj[node].size() == 0;
    for (int next : adj[node]) val += dfs(next, adj);
    return val;
}

int get_leaves(vector<vector<int>> &adj) {
    return dfs(0, adj);
}

int get_highest(vector<vector<int>> &adj) {
    int node = 0;
    while (adj[node].size() == 1) node = adj[node][0];
    return node;
}

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    n += 2; s = '(' + s + ')'; t = '(' + t + ')';

    vector<vector<int>> adj = build(s), adj2 = build(t);
    int leaves1 = get_leaves(adj), leaves2 = get_leaves(adj2);
    int highest1 = get_highest(adj), highest2 = get_highest(adj2);
    cout << ((leaves1 == leaves2 && highest1 == highest2) ? "YES" : "NO") << endl;
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
