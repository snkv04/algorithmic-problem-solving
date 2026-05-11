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

void solve() {
    // flattens input array
    int n;
    cin >> n;
    vector<vector<int>> a(2, vector<int>(n));
    cin >> a;
    vector<int> b(2 * n);
    for (int i = 0; i < 2 * n; ++i) b[i] = a[i >= n][i % n] - 1;

    // gets set of indices for each value, and checks that its cardinality is even
    vector<set<int>> indices(n);
    for (int i = 0; i < n; ++i) {
        if (b[i] != b[i + n]) {
            indices[b[i]].insert(i);
            indices[b[i + n]].insert(i + n);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (indices[i].size() & 1) {
            cout << "-1\n";
            return;
        }
    }

    // breaks graphs into cycles, and colors each cycle
    vector<int> color(2 * n, -1);
    for (int i = 0; i < n; ++i) {
        if (b[i] == b[i + n]) continue;
        if (color[i] != -1) continue;  // have visited this cell

        // builds cycle, making each cycle only have 2 instances of each value,
        // and colors it along the way
        set<int> seen;  // seen values
        int node = i;
        while (true) {
            // only puts the first of the two nodes' values into the seen set
            seen.insert(b[node]);

            // processes these two nodes
            int other = (node >= n) ? (node - n) : (node + n);
            int otherval = b[other];
            indices[b[node]].erase(node);
            indices[otherval].erase(other);
            color[node] = 0;
            color[other] = 1;

            // terminates the cycle if the second node closes the loop
            if (seen.count(otherval)) {
                break;
            } else {
                int next = *indices[otherval].begin();
                node = next;
            }
        }
    }

    // finds all nodes in [0, n) whose color requires the corresponding node pair (top_i, bottom_i) to be flipped
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (b[i] == b[i + n]) continue;
        if (color[i] != 0) ans.push_back(i + 1);
    }
    if (ans.empty()) {
        // why not?
        cout << n << "\n";
        for (int i = 1; i <= n; ++i) cout << i << " ";
        cout << "\n";
    } else {
        cout << ans.size() << "\n";
        for (int idx : ans) cout << idx << " ";
        cout << "\n";
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
