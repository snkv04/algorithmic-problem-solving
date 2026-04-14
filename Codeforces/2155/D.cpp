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
    - problem:
        - we have n batteries. a of them work.
        - in a single query, we can ask about 2 batteries, and we will be told if both of them work or at least
        one of them doesn't.
        - find a pair of working batteries in at most floor(n^2 / a) queries.
    - solution:
        - there are (n - a) dead batteries. we can distribute them into the "gaps" between adjacent pairs of working
        batteries (which we can think of as wrapping around in a circle). then, by the pigeonhole principle,
        there exists at least one pair of batteries whose distance is at most
        (n - a) / a + 1 = n / a - 1 + 1 = n / a. since the distance is an integer, it is in fact at most
        floor(n / a). that bound is exact.
        - therefore, we can iterate through distances, and for each, check all pairs that are that distance away.
        that will take at most n * floor(n / a) queries, which is <= floor(n^2 / a) queries, as desired.
    - notes:
        - in a query, we are only told if both work. if it fails, we don't know if one of them work or neither of
        them work. we only know FOR CERTAIN that a battery doesn't work if we test it against all other batteries
        and all queries return false, but that brute-force would require too many queries, because in the worst
        case, the only 2 working batteries are the 2 last ones and we'd time out (of queries). so, we can't
        brute-force over each battery that could show up as the first in a pair. instead, we brute-force over
        distances, which is fine due to the distance bound explained above.
    */

    int n;
    cin >> n;

    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 1; j <= n; ++j) {
            int k = (j + i - 1) % n + 1;
            cout << j << " " << k << endl;
            int result;
            cin >> result;
            if (result == 1) {
                return;
            } else if (result == -1) {
                std::exit(1);
            }
        }
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
