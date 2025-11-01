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

public:
    SegmentTree(int n) : n(n) {
        t = vector<ll>(4*n, 0);
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

int torowmajor(int i, int j, int c) {
    return c * i + j;
}

int tocolmajor(int i, int j, int r) {
    return r * j + i;
}

// int get_sum(vector<vector<int>> &binary, int u, int d, int l, int r) {
//     int ans = 0;
//     for (int i = u; i <= d; ++i) {
//         for (int j = l; j <= r; ++j) {
//             if (binary[i][j]) ++ans;
//         }
//     }
//     return ans;
// }

ll count_hops(
    int r,
    int c,
    vector<vector<int>> &grid,
    int maxdist,
    const unordered_map<int, vector<pair<int, int>>> &positions
) {
    ll hops = 0;
    for (const auto entry : positions) {
        // // just to test out the brute-force logic
        // vector<pair<int, int>> cells = entry.second;
        // vector<vector<int>> present(r, vector<int>(c, 0));
        // for (pair<int, int> cell : cells) {
        //     present[cell.first][cell.second] = 1;
        // }
        // for (pair<int, int> cell : cells) {
        //     int i = cell.first, j = cell.second;
        //     int up = max(0, i - maxdist);
        //     int down = min(r-1, i+maxdist);
        //     int left = max(0, j - maxdist);
        //     int right = min(c - 1, j + maxdist);

        //     int numsame = get_sum(present, up, down, left, right);
        //     hops += (ll) (down - up + 1) * (right - left + 1) - numsame;
        // }
        
        const vector<pair<int, int>> &cellsbyrowmajor = entry.second;
        int n = cellsbyrowmajor.size();
        vector<pair<int, int>> cellsbycolmajor = cellsbyrowmajor;
        sort(cellsbycolmajor.begin(), cellsbycolmajor.end(), [&r] (pair<int, int> &p1, pair<int, int> &p2) {
            return tocolmajor(p1.first, p1.second, r) < tocolmajor(p2.first, p2.second, r);
        });
        // print_container(cellsbyrowmajor, "by row major: ");
        // print_container(cellsbycolmajor, "by col major: ");
        unordered_map<int, int> colidx_to_idx; // used to convert indices from row-based to column-based
        for (int i = 0; i < cellsbycolmajor.size(); ++i) {
            colidx_to_idx[tocolmajor(cellsbycolmajor[i].first, cellsbycolmajor[i].second, r)] = i;
        }
        SegmentTree st(n); // operates on column-major ordering

        // sliding window across row-major order
        int wl = 0, wr = 0;
        for (pair<int, int> cell : cellsbyrowmajor) {
            int i = cell.first, j = cell.second;

            // submatrix bounds
            int up = max(0, i - maxdist);
            int down = min(r-1, i+maxdist);
            int left = max(0, j - maxdist);
            int right = min(c - 1, j + maxdist);

            // row-major window bounds
            int lb = torowmajor(up, left, c);
            int rb = torowmajor(down, right, c);

            while (
                wr < cellsbyrowmajor.size() &&
                torowmajor(cellsbyrowmajor.at(wr).first, cellsbyrowmajor.at(wr).second, c) <= rb
            ) {
                int idx = colidx_to_idx[tocolmajor(cellsbyrowmajor.at(wr).first, cellsbyrowmajor.at(wr).second, r)];
                st.update(idx, 1);
                ++wr;
            }
            while (
                wl < cellsbyrowmajor.size() &&
                torowmajor(cellsbyrowmajor.at(wl).first, cellsbyrowmajor.at(wl).second, c) < lb
            ) {
                int idx = colidx_to_idx[tocolmajor(cellsbyrowmajor.at(wl).first, cellsbyrowmajor.at(wl).second, r)];
                st.update(idx, 0);
                ++wl;
            }

            // get an accurate count in the submatrix using the segtree to exclude stuff outside
            // the submatrix
            // also, the window will always be non-empty, so both wl and (wr-1) are valid indices
            // for the cells vector
            int numsame = wr - wl;
            int lo = 0, hi = cellsbycolmajor.size() - 1, idx_exclude_left = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (
                    tocolmajor(cellsbycolmajor[mid].first, cellsbycolmajor[mid].second, r) <
                    tocolmajor(up, left, r)
                ) {
                    idx_exclude_left = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (idx_exclude_left >= 0) {
                numsame -= st.query(0, idx_exclude_left);
            }
            lo = 0; hi = cellsbycolmajor.size() - 1; int idx_exclude_right = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (
                    tocolmajor(cellsbycolmajor[mid].first, cellsbycolmajor[mid].second, r) >
                    tocolmajor(down, right, r)
                ) {
                    idx_exclude_right = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            if (idx_exclude_right != -1) {
                numsame -= st.query(idx_exclude_right, cellsbycolmajor.size() - 1);
            }

            // invert to get num of hops in window
            hops += (ll) (down - up + 1) * (right - left + 1) - numsame;
        }
    }
    return hops;
}

void solve() {
    int r, c;
    ll k;
    cin >> r >> c >> k;
    vector<vector<int>> grid(r, vector<int>(c));
    unordered_map<int, vector<pair<int, int>>> positions;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int val;
            cin >> val;
            grid[i][j] = val;
            positions[val].push_back({i, j});
        }
    }

    // O(log(r+c) * r * c * log(rc))
    int left = 1, right = max(r, c) - 1, ans = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        // cout << "testing maxdist " << mid << endl;
        if (count_hops(r, c, grid, mid, positions) >= k) {
            // cout << "worked\n";
            ans = mid;
            right = mid - 1;
        } else {
            // cout << "didn't work\n";
            left = mid + 1;
        }
    }
    cout << ans << endl;
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
