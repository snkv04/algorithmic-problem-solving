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

void solve() {
    // STEP 1: READ INPUT
    // gets the start and end
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    int s, t;
    cin >> s >> t;
    if (s == t) {
        cout << "1\n" << s << "\n";
        return;
    }
    constexpr int MAXAI = 3e5;
    s += MAXAI; t += MAXAI;

    // STEP 2: MAKE THE NEW GRAPH
    // step 2.1: find all prime numbers
    // marks each number as prime or composite
    vector<bool> prime(MAXAI + 1, true);
    prime[0] = prime[1] = false;
    for (int d = 2; d <= MAXAI; ++d) {
        for (int num = 2 * d; num <= MAXAI; num += d) {
            prime[num] = false;
        }
    }

    // step 2.2: find all prime divisors for each number
    // instead of finding all divisors for each number, we only find the prime divisors by checking
    // which numbers are prime beforehand; this saves both space ("Memory limit exceeded on test 130"!!!)
    // and time
    vector<vector<int>> prime_divisors(MAXAI + 1);
    for (int d = 2; d <= MAXAI; ++d) {
        if (!prime[d]) continue;
        
        for (int num = d; num <= MAXAI; num += d) {
            prime_divisors[num].push_back(d);
        }
    }

    // step 2.3: join each node in the original graph with its prime divisors
    // instead of connecting all pairs of spiders to each other, connect them to their divisors, which
    // will act as "central" nodes for all spiders divisible by them
    vector<vector<int>> adj(MAXAI + 1 + n);
    for (int i = 0; i < n; ++i) {
        for (int d : prime_divisors[a[i]]) {
            adj[i+MAXAI+1].push_back(d);
            adj[d].push_back(i+MAXAI+1);
        }
    }

    // STEP 3: FIND SHORTEST PATH (WITH PATH/PREV TRACKING)
    // step 3.1: run the BFS
    // run a BFS on the graph with the original AND divisor nodes
    vector<int> dist(MAXAI+1+n, 1e9), prev(MAXAI+1+n, -1);
    dist[s] = 0;
    prev[s] = -1;
    queue<pair<int, int>> q;
    q.push(make_pair(s, 0));
    while (q.size() && prev[t] == -1) {
        auto [node, dist_node] = q.front();
        q.pop();
        if (dist_node > dist[node]) continue;

        for (auto next : adj[node]) {
            if (dist_node + 1 < dist[next]) {
                dist[next] = dist_node + 1;
                prev[next] = node;
                q.push(make_pair(next, dist[next]));
            }
        }
    }
    if (prev[t] == -1) {
        cout << "-1\n";
        return;
    }

    // step 3.2: extract the path from s to t
    int nodes = dist[t] / 2 + 1;
    vector<int> path;
    int curr = t;
    while (true) {
        path.push_back(curr - MAXAI);
        if (prev[curr] == -1) break;
        else curr = prev[prev[curr]];
    }
    reverse(path.begin(), path.end());
    cout << nodes << '\n';
    for (int node : path) cout << node << ' ';
    cout << '\n';
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
