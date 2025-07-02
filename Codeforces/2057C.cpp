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

bool in_bounds(int x, int l, int r) {
    return x >= l && x <= r;
}

void solve() {
    /*
    - some bits are guaranteed to be the same across the numbers
        - the bound, at which all to the left are forced to be the same
        and all to the right can be different, can vary across the whole
        range of bits and isn't restricted to be the leftmost one or something
        (though it's worth checking if restrictions like that are true, generally)

    - if integers lie in a range of values, there is a location in the bit representation
    (and something similar in the decimal representation, of course) to the left of which
    no change can be made while sticking within that interval and to the right of which the
    values can be changed; be careful, though, because not all combinations of those right-side
    values will stay within the bounds (for example, between 274 and 426, all possible values
    of the ones and tens place occur, but that doesn't mean that 453 is within the interval)
        - for the most significant bit that changes at some point, even if it's not true that
        any combination of that value with any combination of the values to the right are
        within the interval, it is true that (just like with binary search on monotonic functions)
        there exists some number in the interval at which that bit changes. intuitively, imagine
        the case where between 376 and 422, we move from 399 to 400
    - this is already known, but just to emphasize it, for a power of k, all of the digits
    differ (outside of the ones to the left) if you subtract it by 1
    */

    int l, r;
    cin >> l >> r;
    int a = 0;
    int i;
    for (i = 29; i >= 0; --i) {
        if ((l & (1 << i)) != (r & (1 << i))) {
            break;
        } else {
            a += (l & (1 << i));
        }
    }

    int b = a;
    a += (1 << i);
    b += (1 << i) - 1;
    int c;
    for (c = l; c <= r; ++c) {
        if (c != a && c != b) {
            break;
        }
    }

    cout << a << " " << b << " " << c << "\n";
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
