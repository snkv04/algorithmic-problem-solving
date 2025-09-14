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
    if we let mem[i][j] = the minimum cost of putting dish i out at or before time j, then we should make sure
    that the dishes are sorted in such a way that computing this efficiently is easy. namely, the dishes should
    be sorted in increasing order. what benefit does this give? if dish A has its optimal time as <= dish B's
    optimal time, then dish A should always be put out before dish B (if the times are equal, then this provides
    no disadvantage, and if they're different, then this is optimal by reducing overlap). now, what benefit does
    knowing that give? if we want to compute mem[i][j], we know that the previous dish's time to be put out was
    before this dish's time, so we can compute the better option between putting this current dish out at some
    time before this current time and putting it out at the current time and assuming that the previous dish
    was put out some time before this current time. by the way, the reason that mem[i][j] represents the minimum
    cost of putting dish i out at or before time j, and not just putting it out at time j, is because this makes
    it easy to get information from the results of putting out the previous dish at different times. if we
    didn't do this, then to get mem[i][j], we'd have to look at the possibilities of putting out the previous
    dish at all times before j (namely, we'd have to look at mem[i-1][1], mem[i-1][2], ..., mem[i-1][j-1]).
    */

    int n;
    cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) cin >> t[i];
    sort(t.begin(), t.end());
    // cout << "t = "; for (int num : t) cout << num << " "; cout << "\n";

    vector<vector<int>> mem(n+1, vector<int>(2 * n + 1, 1e9));
    fill(mem[0].begin(), mem[0].end(), 0);
    for (int i = 1; i <= n; ++i) {
        int time = t[i-1];
        for (int j = 1; j <= 2 * n; ++j) {
            mem[i][j] = min(mem[i][j-1], mem[i-1][j-1] + abs(j - time));
        }
    }
    // for (int i = 0; i <= n; ++i) {
    //     cout << "i="<<i<<":\t";
    //     for (int j = 0; j <= 2*n; ++j) {
    //         cout << mem[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    cout << mem[n][2*n] << "\n";
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
