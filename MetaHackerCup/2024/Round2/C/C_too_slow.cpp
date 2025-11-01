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

ll count_hops(
    int r,
    int c,
    vector<vector<int>> &grid,
    int maxdist,
    const unordered_map<int, unordered_map<int, vector<int>>> &positions,
    const unordered_map<int, unordered_set<int>> &rows_present
) {
    // cout << "FOR MAXDIST = " << maxdist << "\n";
    ll hops = 0;
    for (int i = 0; i < r; ++i) {
        vector<bool> visited(c, false);
        for (int j = 0; j < c; ++j) {
            if (!visited[j]) { // jump from col to col in this row, for this value
                // initialize window
                int val = grid[i][j];
                unordered_map<int, pair<int, int>> window2d; // map row to [l, r]
                for (int row : rows_present.at(val)) {
                    window2d[row] = make_pair(0, 0);
                }

                // walk through cols with this value
                int total = 0;
                for (const int col : positions.at(val).at(i)) {
                    visited[col] = true;

                    // move window for all rows that this value is present
                    for (int row : rows_present.at(val)) {
                        if (row < i - maxdist || row > i + maxdist) continue;

                        while (
                            window2d[row].second < positions.at(val).at(row).size() &&
                            positions.at(val).at(row).at(window2d[row].second) <= col + maxdist
                        ) {
                            // cout << "val is " << val << ", inc second from " << window2d[row].second << ", and val's freq in row " << i << " is " << positions.at(val).at(i).size() << "\n";
                            ++window2d[row].second;
                            ++total;
                        }
                        while (
                            window2d[row].first < positions.at(val).at(row).size() &&
                            positions.at(val).at(row).at(window2d[row].first) < col - maxdist
                        ) {
                            ++window2d[row].first;
                            --total;
                        }
                    }

                    int left = max(-1, col - maxdist - 1);
                    int right = min(c - 1, col + maxdist);
                    int up = max(-1, i - maxdist - 1);
                    int down = min(r - 1, i + maxdist);
                    hops += (ll) (down - up) * (right - left) - total;
                    // cout << "for (" << i << ", " << col << "), hops += " << ((down - up) * (right - left) - total) << endl;
                    // cout << "also, l="<<left<<", r="<<right<<", u="<<up<<", d="<<down<<"\n";
                    // cout << "at (" << i << ", " << col << "), window2d is:\n";
                    // for (const pair<int, pair<int, int>> &entry : window2d) {
                    //     cout << "\t" << entry.first << ": (" << entry.second.first << ", " << entry.second.second << ")\n";
                    // }
                }
            }
        }
    }
    return hops;
}

void solve() {
    /*
    - STOP making the mistake of treating unordered sets/maps like ordered ones. if i'm iterating
    over elements in a container like that and i make the assumption that "this element is invalid
    so future ones will be as well because they will be greater than this one", then CHECK to make
    sure that the container is actually ordered. i made this mistake with calling break after reaching
    a row greater than (i + maxdist) while iterating over the rows for each (i, col).
    */

    int r, c;
    ll k;
    cin >> r >> c >> k;
    vector<vector<int>> grid(r, vector<int>(c));
    unordered_map<int, unordered_map<int, vector<int>>> positions;
    unordered_map<int, unordered_set<int>> rows_present;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int val;
            cin >> val;
            grid[i][j] = val;
            
            if (positions[val].find(i) == positions[val].end()) {
                positions[val][i] = vector<int>();
            }
            positions[val][i].push_back(j);
            rows_present[val].insert(i);
        }
    }
    // cout << "grid:\n====\n";
    // for (int i = 0; i < r; ++i) {
    //     for (int j = 0; j < c; ++j) {
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "====" << endl;
    // cout << "positions:\n";
    // for (auto e : positions) {
    //     cout << e.first << "\n";
    //     for (auto e2 : e.second) {
    //         cout << "\t" << e2.first << ": ";
    //         for (auto pos : e2.second) cout << pos << " ";
    //         cout << "\n";
    //     }
    // }

    // O(log(r+c) * (rc^2 + cr^2))
    int left = 1, right = max(r, c) - 1, ans = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        // cout << "testing maxdist " << mid << endl;
        if (count_hops(r, c, grid, mid, positions, rows_present) >= k) {
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
