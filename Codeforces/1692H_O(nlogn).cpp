#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

struct Segment {
    ll bestpref, bestsuf, sum, bestsum, bestprefR, bestsufL, bestsumL, bestsumR;

    Segment() {
        Segment(0, -1e9);
    }

    Segment(ll val, int idx) {
        bestpref = max(0LL, val);
        bestsuf = max(0LL, val);
        sum = val;
        bestsum = max(0LL, val);
        if (val >= 0) {
            bestprefR = bestsufL = bestsumL = bestsumR = idx;
        } else {
            bestsufL = bestsumL = idx+1;
            bestprefR = bestsumR = idx-1;
        }
    }

    Segment(ll p, ll s, ll sum, ll bs, ll prefR, ll sufL, ll sumL, ll sumR) :
        bestpref(p),
        bestsuf(s),
        sum(sum),
        bestsum(bs),
        bestprefR(prefR),
        bestsufL(sufL),
        bestsumL(sumL),
        bestsumR(sumR) {}

    Segment merge(const Segment &other) {
        ll out_best_pref = bestpref;
        ll out_best_suf = other.bestsuf;
        ll out_sum = sum + other.sum;
        ll out_best_sum = bestsuf + other.bestpref;
        ll out_best_pref_R = bestprefR;
        ll out_best_suf_L = other.bestsufL;
        ll out_best_sum_L = bestsufL;
        ll out_best_sum_R = other.bestprefR;

        if (sum + other.bestpref > out_best_pref) {
            out_best_pref = sum + other.bestpref;
            out_best_pref_R = other.bestprefR;
        }

        if (other.sum + bestsuf > out_best_suf) {
            out_best_suf = other.sum + bestsuf;
            out_best_suf_L = bestsufL;
        }

        if (bestsum > out_best_sum) {
            out_best_sum = bestsum;
            out_best_sum_L = bestsumL;
            out_best_sum_R = bestsumR;
        }
        if (other.bestsum > out_best_sum) {
            out_best_sum = other.bestsum;
            out_best_sum_L = other.bestsumL;
            out_best_sum_R = other.bestsumR;
        }

        return Segment(
            out_best_pref,
            out_best_suf,
            out_sum,
            out_best_sum,
            out_best_pref_R,
            out_best_suf_L,
            out_best_sum_L,
            out_best_sum_R
        );
    }
};

struct SegmentTree {
private:
    int n;
    vector<Segment> segments;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        segments.resize(4 * n);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            segments[v] = Segment(a[l], l);
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        segments[v] = segments[2*v].merge(segments[2*v+1]);
    }

    Segment _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return Segment(0, -1);
        }
        if (ql <= l && r <= qr) {
            return segments[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr).merge(_query(2 * v + 1, m + 1, r, ql, qr));
    }

    Segment query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, ll val) {
        if (l == r) {
            segments[v] = Segment(val, l);
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        segments[v] = segments[2*v].merge(segments[2*v+1]);
    }

    void update(int idx, ll val) {
        _update(1, 0, n - 1, idx, val);
    }
};

void solve() {
    /*
    how tf did this implementation actually work on the first try?

    generalizable ideas for the future:
    - the brute-force solution would have been to update the full array to represent the +1/-1 array for each
    possible value of the selected die, and then find the subarray with the maximum sum. however, that's O(n^2).
    a quicker solution is to initialize the entire array to -1, then go through each possible value, and only change
    the value of those elements to 1 in our new array, and find the maximum subarray sum. normally, that would still
    be O(n^2) if we do Kadane's algorithm across the whole array, but we can implement a segment tree that finds the
    maximum subarray sum, so then we can perform a single O(log(n)) query for each value of the die.
    */

    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;
    map<int, set<int>> indices;
    for (int i = 0; i < n; ++i) indices[x[i]].insert(i);

    vector<int> a(n, -1);
    SegmentTree st(a);
    int bestsum = 0, ansdie = -1, ansl = -1, ansr = -1;
    for (auto entry : indices) {
        for (int idx : entry.second) {
            st.update(idx, 1);
        }

        Segment result = st.query(0, n-1);
        if (result.bestsum > bestsum) {
            bestsum = result.bestsum;
            ansdie = entry.first;
            ansl = result.bestsumL;
            ansr = result.bestsumR;
        }

        for (int idx : entry.second) {
            st.update(idx, -1);
        }
    }
    cout << ansdie << ' ' << ansl + 1 << ' ' << ansr + 1 << '\n';
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
