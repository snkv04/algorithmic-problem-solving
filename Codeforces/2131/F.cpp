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
    main ideas:
    - for a given (i, j), the entire prefix subrectangle must be 0, meaning that the corresponding prefixes of
    a and b must either be all 0s or all 1s
        - why? all rows are either equal to each other or flips of each other, and same with columns. so, if there
        exists a single square that is a 1, then it's guaranteed to be the case that there will be some 1s blocking
        the path from the top left to (i, j)
    - if we have an array of objects, and some of them meet a condition and some don't, then there could be a quantitative
    key/property of each object such that all objects which meet the condition are <= some threshold and the rest are > than it.
    if there is such a key, then we can sort all the objects by that key, which is useful because now everything that meets
    the condition is to the left and everything that doesn't is to the right.
        - for example, it is a useful tool because we only have to take a single prefix and suffix sum, instead of finding
        all segments of objects in the array that meet the condition. there's only one segment: the one on the left side
        of the array.
        - in this problem, the objects are the prefix indices of the array b, and the key is (cnt1b[j] - cnt0b[j]).
        - motivation: if we are at some index i of array a, where there are 5 0s and 2 1s in the prefix, then across all
        prefixes of b, we will take [cnt0(a,i)+cnt0(b,j)] for any prefix j of b where the number of 1s is at least 4 more
        than the number of 0s, and we will take [cnt1(a,i)+cnt1(b,j)] for any prefix j of b where the number of 1s is
        <= 3 more than the number of 0s (and it can certainly be negative). always good to start from a concrete example.
    */

    // reads in inputs
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    // for simplicity, we can just precompute the number of 0s and 1s for each prefix of a and b
    vector<int> pref0a(n + 1, 0), pref1a = pref0a, pref0b = pref0a, pref1b = pref0a;
    for (int i = 1; i <= n; ++i) {
        pref0a[i] = pref0a[i - 1] + (a[i - 1] == '0');
        pref1a[i] = pref1a[i - 1] + (a[i - 1] == '1');
        pref0b[i] = pref0b[i - 1] + (b[i - 1] == '0');
        pref1b[i] = pref1b[i - 1] + (b[i - 1] == '1');
    }

    // take all prefixes of b, and sort them by cnt1[j]-cnt0[j]
    vector<array<int, 3>> bprefs;
    bprefs.push_back({(int) -1e9, 0, 0});
    for (int i = 1; i <= n; ++i) {
        bprefs.push_back({pref1b[i] - pref0b[i], pref0b[i], pref1b[i]});
    }
    sort(bprefs.begin(), bprefs.end());

    // get prefix sums of cnt0 and cnt1 from the above order, for the purpose of easily taking range sums
    vector<ll> sum0(n + 1, 0), sum1 = sum0;
    for (int i = 1; i <= n; ++i) {
        sum0[i] = sum0[i - 1] + bprefs[i][1];
        sum1[i] = sum1[i - 1] + bprefs[i][2];
    }
    
    // for each prefix of a, find the prefixes of b that we'll flip all 0s for and find the prefixes of b
    // that we'll flip all 1s for
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ll a0s = pref0a[i], a1s = pref1a[i];
        int l = 1, r = n, idx = 0;
        while (l <= r) {
            int m = (l + r) / 2;
            if (bprefs[m][0] <= a0s - a1s) {
                idx = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        // this idx and left, we're flipping the 1s
        ll froma = idx * a1s;
        ll fromb = sum1[idx];
        ans += froma + fromb;

        // to right, we're flipping 0s
        froma = (n - idx) * a0s;
        fromb = sum0[n] - sum0[idx];
        ans += froma + fromb;
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
