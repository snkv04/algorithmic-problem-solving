#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

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
    observations:
    - there are unmarked leaves (UL), marked leaves (0L or 1L),
    the root (marked or unmarked, so UR, 1R, or 2R), and unmarked 
    non-leaf nodes (stalling nodes); the marked non-leaf nodes are
    irrelevant
    - if root is marked:
        - get as many leaves as possible, so the answer is ceil(UL/2) + non-matching leaves to root
    - if root is unmarked:
        - if UL is even:
            - just mark root and then take half of unmarked leaves
        - if UL is odd:
            - we wuold normally get floor(UL/2), so to optimize for this, do a little
            more thinking
            - if 0L != 1L, then we stand to gain from immediately marking the root,
            and then taking leaves in an alternating pattern
            - if 0L == 1L, then we stand to gain from stalling marking the root
            - if stalling nodes are even, then they're useless
            - if they're odd, then we can force the other player to either mark the root
            so we get a head start on the leaves or mark a leaf and then we can mark the
            root as the opposite so we just get a free point, and then the remaining leaf
            count is even
            - side note: the other player wouldn't randomly start marking unmarked non-leaf
            nodes while there are still leaf nodes unmarked because leaf nodes provide a
            greater advantage, UNLESS it's to stall marking the root, but they don't have
            that speed advantage of the first move anyway so they never would stall
    */

    int n;
    cin >> n;
    vector<int> adj[n];
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    string s; cin >> s;

    if (s[0] != '?') {
        int ans = 0, unk = 0;
        for (int i = 1; i < n; ++i) {
            if (adj[i].size() == 1) {
                if (s[i] == '?') ++unk;
                else ans += (s[i] != s[0]);
            }
        }
        ans += (unk+1)/2;
        cout << ans << "\n";
    } else {
        int unk = 0, cnt0 = 0, cnt1 = 0, stalling = 0;
        for (int i = 1; i < n; ++i) {
            if (adj[i].size() == 1) {
                if (s[i] == '?') ++unk;
                else if (s[i] == '0') ++cnt0;
                else ++cnt1;
            } else if (s[i] == '?') {
                ++stalling;
            }
        }

        if (cnt0 != cnt1) {
            cout << (max(cnt0, cnt1) + (unk/2)) << "\n";
            return;
        }

        int fromunknown;
        if (stalling % 2) fromunknown = (unk+1)/2;
        else fromunknown = unk/2;
        cout << (fromunknown + cnt0) << "\n";
    }
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
