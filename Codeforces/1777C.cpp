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

void solve() {
    int n, m;
    cin >> n >> m;

    map<int, unordered_set<int>> s;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        s[ai] = unordered_set<int>();
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = i; j <= s.rbegin()->first; j += i) {
            if (s.find(j) != s.end()) {
                s[j].insert(i);
            }
        }
    }

    vector<int> a; for (const auto p : s) a.push_back(p.first);
    // sort(a.begin(), a.end());
    map<int, int> freqs;
    int i = 0, j = 0;
    n = a.size();
    while (j < n && freqs.size() != m) {
        for (int d : s[a[j]]) {
            freqs[d] += 1;
        }
        j++;
    }
    if (j == n && freqs.size() != m) {
        cout << "-1\n";
        return;
    }

    int ans = 1e9;
    while (j <= n) {
        bool can_push = true;
        while (can_push) {
            for (int d : s[a[i]]) {
                if (freqs[d] == 1) {
                    can_push = false;
                    break;
                }
            }

            if (can_push) {
                for (int d : s[a[i]]) {
                    freqs[d] -= 1;
                    if (freqs[d] == 0) freqs.erase(d);
                }
                i += 1;
            }
        }
        ans = min(ans, a[j-1] - a[i]);

        if (j < n) {
            for (int d : s[a[j]]) {
                freqs[d] += 1;
            }
            j += 1;
        } else {
            break;
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
