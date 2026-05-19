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

int sign(int x) {
    if (x) {
        if (x > 0) return 1;
        else return -1;
    } else {
        return 0;
    }
}

int intersect(int i, int j, vector<int> &a, vector<int> &b, vector<int> &c) {
    // check if they intersect in case where quadratic coefficient is same
    ll a0 = a[j] - a[i], b0 = b[j] - b[i], c0 = c[j] - c[i];
    if (a0 == 0) {
        if (b0 != 0) return 0;

        if (c[i] > c[j]) {
            return -1;
        } else {
            return 1;
        }
    }

    // check discriminant to see if they intersect in general case
    ll d = b0 * b0 - 4 * a0 * c0;
    if (d >= 0) {
        return 0;  // intersection
    }

    // if one points down and the other points up, up is above down
    if (sign(a[i]) != sign(a[j])) {
        if (sign(a[i]) > 0) {
            return -1;
        } else {
            return 1;
        }
    }

    // can't compare their vertices, since being at a different x means that the comparison is unfair.
    // instead, just pick some x, since one will be above the other for all real numbers, and compare y.
    // here, x = 0, so we can actually just compare c.
    if (c[i] > c[j]) {
        return -1;
    } else {
        return 1;
    }
}

void dfs(int node, vector<bool> &visited, queue<int> &reversetop, vector<vector<int>> &adj) {
    visited[node] = true;
    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next, visited, reversetop, adj);
        }
    }
    reversetop.push(node);
}

vector<int> get_longest(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> reversetop;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, visited, reversetop, adj);
        }
    }

    vector<int> mem(n, 1);
    while (reversetop.size()) {
        int node = reversetop.front();
        reversetop.pop();
        for (int next : adj[node]) {
            mem[node] = max(mem[node], mem[next] + 1);
        }
    }
    return mem;
}

void solve() {
    /*
    key ideas:
    - don’t have to only draw a graph where an edge goes from A to B if A covers B;
    can also make a graph of “gets covered by” edges, which is just the transpose graph
    - generally, to get overall length of segments, we add up lengths then subtract overlap;
    here, to get longest path including a point, we get longest forward path, add to longest
    backward path, then subtract 1 (which is the overlap on that single point/node)
    */

    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }

    vector<vector<int>> adj(n), adj2(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int result = intersect(i, j, a, b, c);
            if (result) {
                int above = (result == -1) ? i : j;
                int below = i ^ j ^ above;
                adj[below].push_back(above);
                adj2[above].push_back(below);
            }
        }
    }

    vector<int> mem = get_longest(adj), mem2 = get_longest(adj2);
    for (int i = 0; i < n; ++i) {
        cout << mem[i] + mem2[i] - 1 << " ";
    }
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
