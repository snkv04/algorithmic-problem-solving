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

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (auto &elem : v) is >> elem;
    return is;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;

public:
    SegmentTree(int n) : n(n), t(4 * n, 0) {}

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
        - we have two arrays, filled with distinct integers
        - in a single operation, we pick some distance, and swap two elements in a with that distance (measured
        by index, not by value, lol) and swap two elements in b with that distance
        - is it possible to make the arrays the same?
    - solution:
        - first, we reduce the problem by dealing with simpler operations
            - observe that we can perform any operation by using only primitive operations of swapping adjacent
            elements, so we can reduce the problem by treating all operations as if they're the primitive ones
        - then, we reduce the problem into checking that the inversion parity of A and B are the same
            - why? A doesn't need to change, so the number of swaps we perform on it should be even (so we can
            just "swap" the same 2 adjacent elements repeatedly)
            - since the number of swaps we perform on B needs to be even, the final inversion parity needs to
            be equal to A, so the initial inversion parity needs to be equal to that of A
    - details:
        - in essence, checking that the inversion parity of the two arrays is the same comes down to applying an
        index mapping on one array that makes the inversion parity even (specifically, 0, by sorting A), applying
        the same index mapping on the other array, then ensuring that the inversion parity of the second array is
        also even
    */

    // reads in input
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    // sorts A and B together by A, so we get a new modified B that we need to transform into a sorted B
    // (instead of transforming B into A)
    vector<pair<int, int>> together;
    for (int i = 0; i < n; ++i) together.push_back({a[i], b[i]});
    sort(together.begin(), together.end());

    // given this modified B, we find the indices in increasing order of array value, solely for finding
    // inversion count using segment tree
    vector<pair<int, int>> sorted_by_b;
    for (int i = 0; i < n; ++i) sorted_by_b.push_back({together[i].second, i});
    sort(sorted_by_b.begin(), sorted_by_b.end());

    // finds inversion count using segment tree
    ll inversions = 0;
    SegmentTree st(n);
    for (int i = 0; i < n; ++i) {
        int idx = sorted_by_b[i].second;
        inversions += st.query(idx, n - 1);
        st.update(idx, 1);
    }

    // just checks that A and B hold the same elements
    bool same_multiset = true;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (int i = 0; i < n; ++i) if (a[i] != b[i]) { same_multiset = false; break; }

    // outputs final answer
    cout << ((same_multiset && !(inversions % 2)) ? "YES" : "NO") << endl;
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
