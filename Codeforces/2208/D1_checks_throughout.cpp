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

struct DSU {
    DSU(int n) : n(n), comp_size(n, 1) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int node1, int node2) {
        int root1 = find(node1), root2 = find(node2);
        if (root1 != root2) {
            if (comp_size[root1] >= comp_size[root2]) {
                parent[root2] = root1;
                comp_size[root1] += comp_size[root2];
            } else {
                parent[root1] = root2;
                comp_size[root2] += comp_size[root1];
            }
        }
    }

    int size(int node) {
        return comp_size[find(node)];
    }

private:
    int n;
    std::vector<int> parent, comp_size;
};

void solve() {
    // reads in input
    int n;
    cin >> n;
    vector<vector<bool>> s(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        string si;
        cin >> si;
        for (int j = 0; j < n; ++j) {
            s[i][j] = si[j] == '1';
        }
    }

    // checks that each node can reach itself
    for (int i = 0; i < n; ++i) {
        if (!s[i][i]) {
            cout << "no\n";
            return;
        }
    }

    // checks that there are no cycles
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (s[i][j] && s[j][i]) {
                cout << "no\n";
                return;
            }
        }
    }

    // builds edges
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j || !s[i][j]) continue;

            // checks if there's nothing in between i and j, which would mean that i -> j is an edge
            bool nothing_between = true;
            for (int k = 0; k < n; ++k) {
                if (i == k || j == k) continue;

                // makes sure that the i -> j relation makes sense with k
                if (s[j][k]) {
                    if (!s[i][k]) {
                        cout << "no\n";
                        return;
                    }
                }
                if (!s[i][k]) {
                    if (s[j][k]) {
                        cout << "no\n";
                        return;
                    }
                }

                // actually performs the "between" check for k
                if (s[i][k] && s[k][j]) {
                    nothing_between = false;
                    break;
                }
            }
            if (nothing_between) {
                edges.push_back(make_pair(i, j));
            }
        }
    }

    // checks that the edges form a tree
    if (edges.size() != n-1) {
        cout << "no\n";
        return;
    }
    DSU dsu(n);
    for (auto [a, b] : edges) {
        dsu.join(a, b);
    }
    if (dsu.size(0) != n) {
        cout << "no\n";
        return;
    }

    // tree is valid
    cout << "yes\n";
    for (auto [a, b] : edges) {
        cout << a + 1 << ' ' << b + 1 << '\n';
    }
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
