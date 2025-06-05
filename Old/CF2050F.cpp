#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

int gcd(int a, int b) {
    int A = max(a, b), B = min(a, b);
    while (B != 0) {
        int r = A % B;
        A = B;
        B = r;
    }
    return A;
}

struct SegmentTree {
private:
    vector<int> a, t;
    int n;

public:
    void build(int l, int r, int v) {
        if (l == r) {
            t[v] = this->a[l];
            return;
        }

        int m = (l + r) / 2;
        build(l, m, 2*v);
        build(m+1, r, 2*v+1);
        t[v] = gcd(t[2*v], t[2*v+1]);
    }

    int _query(int l, int r, int v, int ql, int qr) {
        if (r < ql || l > qr) {
            return 0;
        }
        if (l >= ql && r <= qr) {
            return t[v];
        }

        int m = (l + r) / 2;
        return gcd(
            _query(l, m, 2*v, ql, qr),
            _query(m+1, r, 2*v+1, ql, qr)
        );
    }

    int query(int ql, int qr) {
        return _query(0, n-1, 1, ql, qr);
    }

    SegmentTree(vector<int> &a) {
        this->a = a;
        n = a.size();
        t.resize(4 * n);
        build(0, n-1, 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    int last = -1;
    vector<int> diffs;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        if (last != -1) {
            diffs.push_back((int) abs((ll) ai - last));
        }
        last = ai;
    }
    // cout << "diffs: ";
    // for (int diff : diffs) cout << diff << " ";
    // cout << endl;

    if (diffs.size()) {
        SegmentTree st(diffs);
        while (q--) {
            int l, r;
            cin >> l >> r;
            --l; r -= 2;
            if (r < l) {
                cout << "0 ";
            } else {
                cout << st.query(l, r) << ' ';
            }
        }
    } else {
        while (q--) {
            int l, r;
            cin >> l >> r;
            cout << "0 ";
        }
    }
    cout << endl;
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
