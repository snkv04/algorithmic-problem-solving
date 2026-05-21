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
    generalizable ideas:
    - when doing this kind of "num of operations DP" (or "segment DP"), how do we ensure that the very first
    index where each operation is done has that triangular form? (basically, the first operation can't be
    done before the first index, the second operation can't be done before the second index, etc.) the way we
    can ensure that is by making mem[i][j] first draw from mem[i-1][j] so that it's the best across all indices
    up to and including i when j operations have been done (and to make this not go out of bounds, we can either
    make the mem array 1-indexed or make it 0-indexed but have a special case for i=0), and then we can make
    mem[i][j] draw from mem[i-1][j-1]. if we properly initialize the values of the mem array (like in this
    case, the initial values are -1e9), then the triangle is satisfied automatically, because both mem[i-1][j]
    and mem[i-1][j-1] will be a default value (like -1e9) if (i, j) is in the triangle where states are invalid.
    also, to make mem[i-1][j-1] not go out of bounds, we can make the second dimension also 1-indexed, but we
    should make sure that the default values of mem[i][0] are set properly.
        - smth that will probably be generally true: if doing the 1-indexing on the second dimension,
        mem[i][0] should probably always be 0, because it means the best (something) after performing
        0 operations. also, if doing the 1-indexing on the first dimension, then mem[0][j] should probably
        be the sentinel/uncomputed value (like -1e9), because 0 isn't a valid index in the array regardless
        of the number of operations since the valid indices fall in the closed interval [1, n].
        - to ensure this in all cases (as this problem might just be a special case where this doesn't matter
        because all operations add a positive number whereas in other problems we might add a negative number
        but we shouldn't be allowed to avoid this negative operation), we can also just add a check, like
        "if mem[i-1][j-1] == -1e9, then don't use the value at all, otherwise, do (mem[i-1][j-1] + smth)".
    */

    int n;
    cin >> n;
    vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];

    vector<vector<int>> mem(n+1, vector<int>(4, -1));
    for (int i = 0; i <= n; ++i) mem[i][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= 3; ++j) {
            mem[i][j] = mem[i-1][j];
            if (j == 1) {
                mem[i][j] = max(mem[i][j], mem[i-1][j-1] == -1 ? -1 : mem[i-1][j-1] + b[i-1] + i-1);  // works bc mem[i][0] is 0 for all i
            } else if (j == 2) {
                mem[i][j] = max(mem[i][j], mem[i-1][j-1] == -1 ? -1 : mem[i-1][j-1] + b[i-1]);
            } else {
                mem[i][j] = max(mem[i][j], mem[i-1][j-1] == -1 ? -1 : mem[i-1][j-1] + b[i-1] - (i-1));
            }
        }
    }
    // for (int j = 0; j <= 3; ++j) {
    //     for (int i = 0; i <= n; ++i) cout << mem[i][j] << " ";
    //     cout << endl;
    // }
    cout << mem[n][3] << '\n';
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
