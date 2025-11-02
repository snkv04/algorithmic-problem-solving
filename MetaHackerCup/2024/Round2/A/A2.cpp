#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
vector<vector<int>> nondecreasing(8);
vector<ll> mountains;
vector<ll> pow10;

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

void solve() {
    // vector<vector<ll>> dp(10, vector<ll>(10, 0));
    // dp[0][0] = 1;
    // for (int i = 1; i <= 9; ++i) {
    //     for (int j = 1; j <= 9; ++j) {
    //         for (int k = 0; k <= j; ++k) {
    //             dp[i][j] += dp[i-1][k];
    //         }
    //     }
    // }
    // for (int i = 0; i < 10; ++i) {
    //     for (int j = 0; j < 10; ++j)
    //         cout << dp[i][j] << " ";
    //     cout << endl;
    // }

    ll a, b, m;
    cin >> a >> b >> m;
    int ans = 0;
    for (ll mountain : mountains) {
        if (mountain >= a && mountain <= b && mountain % m == 0) {
            ++ans;
        }
    }
    cout << ans << endl;
}

void dfs(int &num, int &idx) {
    if (idx == 8) return;

    int last = num % 10;
    num *= 10;
    for (int d = max(1, last); d <= 8; ++d) {
        num += d;
        nondecreasing[idx].push_back(num);
        ++idx;
        dfs(num, idx);
        --idx;
        num -= d;
    }
    num /= 10;
}

ll reverse(ll num) {
    string str = to_string(num);
    reverse(str.begin(), str.end());
    return stoll(str);
}

int main() {
    /*
    generalizable ideas for the future:
    - the number of nondecreasing sequences of digits of length N is drastically less than the total number of
    sequences of length N. more generally, the space of a set of objects might not be on the same order of magnitude
    as i think, due to some constraints changing it considerably. so, validate that my assumptions about search space
    sizes are correct
    - before trying to jump to DP, think about if the brute-force solution could actually work, and if not, then
    maybe try optimizing it first?
    */

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int num = 0, idx = 0;
    dfs(num, idx);

    pow10 = vector<ll>(10, 1);
    for (int i = 1; i <= 9; ++i) pow10[i] = pow10[i-1] * 10;

    for (int i = 1; i <= 9; ++i) mountains.push_back(i);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < nondecreasing[i].size(); ++j) {
            for (int k = 0; k < nondecreasing[i].size(); ++k) {
                int maxdigit = max(nondecreasing[i][j] % 10, nondecreasing[i][k] % 10);
                ll rev = reverse(nondecreasing[i][k]);
                for (int d = maxdigit + 1; d <= 9; ++d) {
                    ll m = pow10[i+2] * nondecreasing[i][j] + pow10[i+1] * d + rev;
                    mountains.push_back(m);
                }
            }
        }
    }
    // cout << "====\n";
    // for (int i = 0; i < 100; ++i) {
    //     cout << mountains[i] << endl;
    // }
    // cout << "====\n";

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
