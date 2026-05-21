#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int idx = 0;
map<string, int> to_idx;

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

int get_idx(string &s) {
    if (!to_idx.count(s)) {
        to_idx[s] = idx++;
    }
    return to_idx[s];
}

void solve() {
    /*
    - problem:
        - literally just longest simple path in graph. that's it. that is the entire problem.
    - useful ideas:
        - instead of looking through all possible paths, which would be something along the lines of O(n! * n),
        we can look through all possible subsets of nodes alongside the last node used in the path, which is
        O(2^n * n^2).
            - typically DP is used to reduce from subsets to size of subset, but the core idea is still the same
            here: we're reducing the search space by reusing results from subproblems. it just so happens to be
            the case that we're reducing from permutations to subsets, which is still a meaningful speedup.
    */

    // reads in inputs
    int n;
    cin >> n;
    vector<vector<int>> gw(n, vector<int>(2, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            string s;
            cin >> s;
            gw[i][j] = get_idx(s);
        }
    }

    // makes graph (probably unnecessary, but simplifies code later for checking adjacent nodes)
    vector<set<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (gw[i][0] == gw[j][0] || gw[i][1] == gw[j][1]) {
                adj[i].insert(j);
                adj[j].insert(i);
            }
        }
    }

    // runs DP on (subset, last node picked) states
    vector<vector<bool>> mem(1 << n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) mem[1 << i][i] = true;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) < 2) continue;

        for (int last = 0; last < n; ++last) {
            if ((mask >> last) & 1) {
                for (int second_last = 0; second_last < n; ++second_last) {
                    if (adj[last].count(second_last) && ((mask >> second_last) & 1)) {
                        mem[mask][last] = mem[mask][last] || mem[mask ^ (1 << last)][second_last];
                    }
                }
            }
        }
    }
    // for (int mask = 0; mask < (1 << n); ++mask) {
    //     cout << "mem[" << std::bitset<8>(mask).to_string() << "] = " << mem[mask] << endl;
    // }

    // finds max size of constructable subset
    int ans = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int last = 0; last < n; ++last) {
            if (mem[mask][last]) ans = max(ans, __builtin_popcount(mask));
        }
    }
    cout << n - ans << endl;
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
