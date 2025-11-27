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

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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

struct RollingHash {
private:
    vector<ll> P = {998244353, 999999937};
    vector<ll> MOD = {1000000007, 1000000009};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling;
    string s;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[i][t] = (rolling[i - 1][t] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

    void _build_powers() {
        PPOW = vector<vector<ll>>(n + 1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                PPOW[i][t] = (PPOW[i - 1][t] * P[t]) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
        _build_powers();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        array<ll, 2> result;
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

struct DSU {
private:
    int n;
    vector<int> parent, size;

public:
    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        size = vector<int>(n, 1);
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            if (size[c] >= size[d]) {
                parent[d] = c;
                size[c] += size[d];
            } else {
                parent[c] = d;
                size[d] += size[c];
            }
        }
    }
};

void solve() {
    int n;
    while (cin >> n) {
        vector<int> a(n);
        cin >> a;

        // the standard LIS in O(n log n) algorithm doesn't work for the final LIS (only the size),
        // since we might replace an element with another element to maximize the possibility that
        // these replacements propagate to the back, the back element gets smaller, and we can then
        // increase the length of the LIS (which is all fine), except then the actual LIS after the
        // replacement doesn't have all of its indices in order. instead, we can keep track of the
        // full history of replacements for every element of the LIS, and when constructing the
        // final LIS, we greedily get the latest possible replacement (for each element of the LIS)
        // from the back to the front such that all the indices are valid.
        // - why don't we do greedy from the left to the right of the LIS, taking the leftmost valid
        // index from each element of the 2D LIS? that doesn't take advantage of the replacements.
        // instead we go from right to left, taking the maximum possible (valid, meaning less than
        // all already-picked indices) index from each element of the 2D LIS, and this places as
        // little restriction on later-picked (so more to the left) elements from the LIS while also
        // taking advantage of the replacements.
        vector<vector<pair<int, int>>> lis;
        for (int i = 0; i < n; ++i) {
            int val = a[i];
            if (lis.empty() || lis.back().back().second < val) {
                lis.push_back(vector<pair<int, int>>({make_pair(i, val)}));
            } else {
                int l = 0, r = lis.size() - 1, idx = -1;
                while (l <= r) {
                    int m = l + (r - l) / 2;
                    if (lis[m].back().second >= val) {
                        idx = m;
                        r = m - 1;
                    } else {
                        l = m + 1;
                    }
                }
                lis[idx].push_back(make_pair(i, val));
            }
        }

        stack<int> indices;
        int minindex = 1e9;
        for (int i = lis.size() - 1; i >= 0; --i) {
            for (int j = lis[i].size() - 1; j >= 0; --j) {
                int idx = lis[i][j].first, val = lis[i][j].second;
                if (idx < minindex) {
                    indices.push(idx);
                    minindex = idx;
                    break;
                }
            }
        }

        cout << indices.size() << "\n";
        while (indices.size()) {
            cout << indices.top() << " ";
            indices.pop();
        }
        cout << "\n";
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
