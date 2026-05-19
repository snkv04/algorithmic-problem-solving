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
    /*
    - if we let a = +1 and b = -1, we are trying to remove a substring (which is identical to selecting some
    prefix and non-overlapping suffix) such that the prefix and suffix have inverted sums. the alternative
    solution, which is this one, is to select a substring such that the subarray sum is equal to the difference
    we want (i.e., the difference we need in order to ensure the other a's and b's are equal). this difference
    is just equal to count(a) - count(b), because after removing a substring with such a count, the remaining
    prefix and suffix have equal counts of a and b.
    */

    int n;
    cin >> n;
    string s; cin >> s;

    int diff = 0;
    for (char c : s) {
        if (c == 'a') ++diff;
        else --diff;
    }
    if (!diff) {
        cout << "0\n";
        return;
    }

    unordered_map<int, set<int>> to_idx;
    int curr = 0, ans = 1e9;
    for (int i = -1; i < n; ++i) {
        int val = i == -1 ? 0 : (s[i] == 'a' ? 1 : -1);
        curr += val;
        if (to_idx.find(curr - diff) != to_idx.end()) {
            ans = min(ans, i - *to_idx[curr-diff].rbegin());
        }
        to_idx[curr].insert(i);
    }
    cout << (ans == n ? -1 : ans) << '\n';
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
