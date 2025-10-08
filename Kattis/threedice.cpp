#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

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

vector<int> color_counts(3);

bool dfs(int node, vector<vector<int>> &adj, vector<int> &color) {
    vector<bool> possible(3, true);
    for (int next : adj[node]) {
        if (color[next] != -1) {
            // cout << "color[next] = " << color[next] << "\n";
            possible[color[next]] = false;
        }
    }
    if (possible[0] + possible[1] + possible[2] == 0) {
        return false;
    }

    for (int trying = 0; trying < 3; ++trying) {
        if (!possible[trying]) continue;
        if (color_counts[trying] == 6) continue;

        color[node] = trying;
        color_counts[trying] += 1;
        bool works = true;
        for (int next : adj[node]) {
            if (color[next] == -1 && !dfs(next, adj, color)) {
                works = false;
                break;
            }
        }

        if (works) {
            return true;
        } else {
            color[node] = -1;
            color_counts[trying] -= 1;
        }
    }
    return false;
}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(26);
    unordered_set<int> used;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if (s[0] == s[1] || s[1] == s[2] || s[0] == s[2]) {
            cout << "0\n";
            return;
        }

        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (j != k) {
                    int a = s[j] - 'a', b = s[k] - 'a';
                    used.insert(a);
                    adj[a].push_back(b);
                }
            }
        }
    }
    // for (int i = 0; i < 26; ++i) {
    //     print_container(adj[i], "adj[" + to_string(i) + "] = ");
    // }
    // print_container(used, "used = ");

    vector<int> color(26, -1);
    for (int i = 0; i < 26; ++i) {
        if (used.find(i) != used.end() && color[i] == -1) {
            if (!dfs(i, adj, color)) {
                cout << "0\n";
                return;
            }
        }
    }
    // print_container(color, "color = ");

    vector<vector<char>> dice(3);
    for (int i = 0; i < 26; ++i) {
        if (color[i] != -1) {
            dice[color[i]].push_back((char) ('a' + i));
        }
    }
    // cout << "before using new chars:\n";
    // for (int i = 0; i < 3; ++i) {
    //     print_container(dice[i], "dice[" + to_string(i) + "] = ");
    // }


    for (int i = 0; i < 3; ++i) {
        while (dice[i].size() < 6) {
            for (int j = 0; j < 26; ++j) {
                if (used.find(j) == used.end()) {
                    used.insert(j);
                    dice[i].push_back((char) ('a' + j));
                    break;
                }
            }
            // cout << "dice[i].size() = " << dice[i].size() << "\n";
            // print_container(used, "used = ");
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (char c : dice[i]) cout << c;
        cout << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
