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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;

    ll result = mod_pow(b, e / 2);
    result = (result * result) % MOD;
    if (e % 2) result = (result * b) % MOD;
    return result;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll num, ll denom) {
    return (num * mod_inv(denom)) % MOD;
}

void solve() {
    /*
    if the difference between the min and max level dancers was restricted at m-1 but it was possible
    for the number of dancers in a dance to be equal to k and k < m, then this would be drastically
    harder. however, since exactly m dancers must be present, this is significantly easier, since the
    levels of all of the dancers are consecutive (i.e., they look like i, i+1, i+2, ..., i+m-1).
    */

    int n, m;
    cin >> n >> m;
    unordered_map<int, int> counts;
    while (n--) {
        int ai;
        cin >> ai;
        counts[ai] += 1;
    }

    if (counts.size() < m) {
        cout << "0\n";
        return;
    }

    vector<pair<int, int>> sorted_counts;
    for (const pair<int, int> &entry : counts) sorted_counts.push_back(entry);
    sort(sorted_counts.begin(), sorted_counts.end());
    // print_container(sorted_counts, "sorted_counts = ");

    ll ans = 0, curr = 1;
    int i = 0, j = 0;
    while (j < sorted_counts.size()) {
        // cout << "about to include " << sorted_counts[j] << " in window\n";
        curr = (curr * sorted_counts[j++].second) % MOD;
        while (sorted_counts[i].first <= sorted_counts[j-1].first - m) {  // j-1 is last index of window, inclusive
            curr = mod_div(curr, sorted_counts[i++].second);
        }
        // cout << "now, curr = " << curr << "\n";

        if (j - i == m) {
            ans = (ans + curr) % MOD;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
