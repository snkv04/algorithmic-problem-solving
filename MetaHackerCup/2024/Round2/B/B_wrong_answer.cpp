#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
vector<vector<pair<int, int>>> dirs = {
    {
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 3}
    },
    {
        {0, 0},
        {1, 1},
        {2, 2},
        {3, 3}
    },
    {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0}
    },
    {
        {0, 0},
        {1, -1},
        {2, -2},
        {3, -3}
    },
};

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
        vector<ll> result(2);
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

int toidx(int i, int j, int d) {
    return 4 * (7 * i + j) + d;
}

array<int, 3> fromidx(int idx) {
    int d = idx % 4;
    idx /= 4;
    int j = idx % 7, i = idx / 7;
    return {i, j, d};
}

bool in_bounds(int i, int j) {
    return i >= 0 && i < 6 && j >= 0 && j < 7;
}

bool strictly_below(int a, int b) {
    array<int, 3> res1 = fromidx(a), res2 = fromidx(b);
    int i1 = res1[0], j1 = res1[1], d1 = res1[2];
    int i2 = res2[0], j2 = res2[1], d2 = res2[2];
    vector<pair<int, int>> cells1, cells2;
    for (int c = 0; c < 4; ++c) {
        cells1.push_back(make_pair(i1 + dirs[d1][c].first, j1 + dirs[d1][c].second));
        cells2.push_back(make_pair(i2 + dirs[d2][c].first, j2 + dirs[d2][c].second));
    }

    vector<int> colmax(7, 1e9);
    for (pair<int, int> cell : cells2) {
        if (colmax[cell.second] == 1e9) {
            colmax[cell.second] = cell.first;
        } else {
            colmax[cell.second] = max(colmax[cell.second], cell.first);
        }
    }

    for (pair<int, int> cell : cells1) {
        if (cell.first <= colmax[cell.second]) {
            return false;
        }
    }
    return true;
}

void solve() {
    /*
    - the reason why this solution is wrong is that it doesn't consider the possibility that a
    state is not reachable through a valid sequence of moves (C then F then C then F etc.).
    */

    vector<string> grid(6);
    for (int i = 0; i < 6; ++i) {
        cin >> grid[i];
    }
    // cout << "grid is:\n";
    // for (int i = 0; i < 6; ++i) {
    //     cout << grid[i] << endl;
    // }

    vector<char> winstates(168, ' ');
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int dir = 0; dir < 4; ++dir) {
                int idx = toidx(i, j, dir);
                vector<pair<int, int>> cells;
                for (int c = 0; c < 4; ++c) {
                    cells.push_back(make_pair(i + dirs[dir][c].first, j + dirs[dir][c].second));
                }
                // print_container(cells, "cells = ");

                bool in = true;
                for (int c = 0; c < 4; ++c) {
                    if (!in_bounds(cells[c].first, cells[c].second)) {
                        in = false;
                    }
                }
                // cout << "in = " << in << endl;

                if (in) {
                    char won = ' ';
                    for (pair<int, int> c : cells) {
                        char here = grid[c.first][c.second];
                        if (won == ' ') {
                            won = here;
                        } else if (here != won) {
                            won = '.';
                        }
                    }

                    if (won != '.') { // char is same across 4 cells
                        winstates[idx] = won;
                        // cout << "for i="<<i<<", j="<<j<<", d="<<dir<<", won="<<won<<endl;
                    }
                }
            }
        }
    }
    bool none = true;
    for (int i = 0; i < 168; ++i) {
        if (winstates[i] != ' ') {
            none = false;
            break;
        }
    }
    if (none) {
        cout << "0\n";
        return;
    }

    vector<int> indeg(168, 0);
    for (int a = 0; a < 168; ++a) {
        for (int b = 0; b < 168; ++b) {
            if (a == b) continue;
            if (winstates[a] == ' ' || winstates[b] == ' ') continue;

            if (strictly_below(a, b)) {
                indeg[b] += 1;
            }
        }
    }
    // print_container(winstates, "winstates = ");
    // print_container(indeg, "indeg = ");

    char winner = ' ';
    for (int i = 0; i < 168; ++i) {
        int won = winstates[i];
        if (won != ' ' && indeg[i] == 0) {
            if (winner == ' ') {
                winner = won;
            } else if (winner != ' ' && winner != won) {
                winner = '.';
                break;
            }
        }
    }
    
    if (
        winner == ' ' // none have indegree 0
        || winner == '.' // different winners have indegree 0
    ) {
        cout << "?\n";
    } else {
        cout << winner << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
