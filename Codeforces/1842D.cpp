#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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

bool reachable(int node, int target, vector<vector<pair<int, int>>> &adj, vector<bool> &visited) {
    if (node == target) return true;

    visited[node] = true;
    for (auto [next, weight] : adj[node]) {
        if (!visited[next]) {
            if (reachable(next, target, adj, visited)) {
                return true;
            }
        }
    }
    return false;
}

struct Comparator {
    bool operator()(const pair<int, ll> &a, const pair<int, ll> &b) {
        return a.second > b.second;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;
        --i; --j;
        adj[i].push_back(make_pair(j, k));
        adj[j].push_back(make_pair(i, k));
    }

    vector<bool> visited(n, false);
    if (!reachable(0, n - 1, adj, visited)) {
        cout << "inf\n";
        return;
    }

    ll time = 0;
    vector<pair<string, ll>> games;
    set<int> curr;
    curr.insert(0);
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, Comparator> constraints;
    for (auto [next, weight] : adj[0]) constraints.push(make_pair(next, weight));
    while (!curr.count(n - 1)) {
        auto [next_player, next_time] = constraints.top();
        constraints.pop();

        if (next_time > time) {
            ll length = next_time - time;
            string game(n, '0');
            for (int i : curr) game[i] = '1';
            games.push_back(make_pair(game, length));
        }

        time = next_time;
        curr.insert(next_player);
        for (auto [next, weight] : adj[next_player]) {
            if (!curr.count(next)) {
                constraints.push(make_pair(next, weight + time));
            }
        }
    }

    cout << time << ' ' << games.size() << '\n';
    for (auto [game, length] : games) cout << game << ' ' << length << '\n';
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
