#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
vector<int> pre, low, rep;  // rep[i] is the representative node of node i's SCC
int timer;
stack<int> stk;
vector<bool> onstack;

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

void dfs(int node) {
    pre[node] = low[node] = timer++;
    stk.push(node);
    onstack[node] = true;

    for (int next : adj[node]) {
        if (pre[next] == -1) {
            dfs(next);
        }

        if (onstack[next]) {
            low[node] = min(low[node], low[next]);
        }
    }

    if (pre[node] == low[node]) {
        int top = -1;
        do {
            top = stk.top();
            stk.pop();
            onstack[top] = false;
            rep[top] = node;
        } while (top != node);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    adj = vector<vector<int>>(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
    }

    pre = vector<int>(n, -1);
    low = pre;
    rep = pre;
    timer = 0;
    onstack = vector<bool>(n, false);
    for (int i = 0; i < n; ++i) {
        if (pre[i] == -1) {
            dfs(i);
        }
    }

    bool valid = true;
    for (int i = 1; i < n; ++i) {
        if (rep[0] != rep[i]) {
            valid = false;
            break;
        }
    }

    if (valid) {
        cout << "YES\n";
    } else {
        vector<set<int>> condensed(n);
        for (int i = 0; i < n; ++i) {
            for (int j : adj[i]) {
                condensed[rep[i]].insert(rep[j]);
            }
        }

        int first = 0, second = -1;
        for (int i = 0; i < n; ++i) {
            if (rep[i] != rep[0]) {
                second = i;
                break;
            }
        }
        assert(second != -1);

        cout << "NO\n";
        if (condensed[rep[first]].count(rep[second])) {
            cout << second + 1 << " " << first + 1 << "\n";
        } else {
            cout << first + 1 << " " << second + 1 << "\n";
        }
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
