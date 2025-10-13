#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> adj;
unordered_set<int> used;
vector<int> preorder, low, scc;
vector<bool> visited, on_stack;
stack<int> stk;
int counter;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

void dfs(int node) {
    visited[node] = true;
    preorder[node] = low[node] = counter++;
    stk.push(node);
    on_stack[node] = true;

    for (int next : adj[node]) {
        if (!visited[next]) {
            dfs(next);
        }

        if (on_stack[next]) {
            low[node] = min(low[node], low[next]);
        }
    }

    if (preorder[node] == low[node]) {
        while (true) {
            int top = stk.top();
            stk.pop();
            on_stack[top] = false;
            scc[top] = node;
            if (top == node) {
                break;
            }
        }
    }
}

void solve(int n) {
    adj = vector<vector<int>>(26);
    used.clear();
    for (int i = 0; i < n; ++i) {
        vector<int> letters;
        for (int j = 0; j < 6; ++j) {
            char letter;
            cin >> letter;
            letters.push_back(letter - 'A');
            used.insert(letter - 'A');
        }

        for (int j = 0; j < 5; ++j) {
            if (letters[j] != letters[5]) {
                adj[letters[5]].push_back(letters[j]);
            }
        }
    }

    preorder = vector<int>(26, -1);
    low = vector<int>(26, -1);
    on_stack = vector<bool>(26, false);
    visited = vector<bool>(26, false);
    counter = 0;
    scc = vector<int>(26, -1);
    for (int i = 0; i < 26; ++i) {
        if (used.find(i) != used.end() && !visited[i]) {
            dfs(i);
        }
    }

    unordered_map<int, set<int>> sccs;
    for (int i = 0; i < 26; ++i) {
        if (used.find(i) != used.end()) {
            sccs[scc[i]].insert(i);
        }
    }

    map<int, set<int>> sorted_sccs;
    for (const auto entry : sccs) {
        sorted_sccs[*entry.second.begin()] = entry.second;
    }

    for (const auto entry : sorted_sccs) {
        for (int i : entry.second) {
            char as_letter = 'A' + i;
            cout << as_letter << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }

        solve(n);
    }

    return 0;
}
