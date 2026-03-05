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
    int bestpref, bestprefR;
    int bestsuf, bestsufL;
    int bestsum, bestsumL, bestsumR;
    int sum;

    Segment(int idx, int sum) : sum(sum) {
        if (sum >= 0) {
            bestsum = bestpref = bestsuf = sum;
            bestsumL = bestsumR = bestprefR = bestsufL = idx;
        } else {
            bestsum = bestpref = bestsuf = 0;
            bestsumL = bestsufL = idx + 1;  // suffix starts after the segment
            bestsumR = bestprefR = idx - 1;  // prefix ends before the segment
        }
    }

    Segment() : Segment(-1, 0) {}

    Segment(int bp, int bpr, int bs, int bsl, int bsm, int bsml, int bsmr, int s) :
        bestpref(bp), bestprefR(bpr),
        bestsuf(bs), bestsufL(bsl),
        bestsum(bsm), bestsumL(bsml), bestsumR(bsmr),
        sum(s) {}

    friend Segment merge(Segment left, Segment right) {
        int ressum = left.sum + right.sum;

        int resbestpref = left.bestpref;
        int resbestprefR = left.bestprefR;
        if (left.sum + right.bestpref > resbestpref) {
            resbestpref = left.sum + right.bestpref;
            resbestprefR = right.bestprefR;
        }

        int resbestsuf = right.bestsuf;
        int resbestsufL = right.bestsufL;
        if (right.sum + left.bestsuf > resbestsuf) {
            resbestsuf = right.sum + left.bestsuf;
            resbestsufL = left.bestsufL;
        }

        int resbestsum = left.bestsuf + right.bestpref;
        int resbestsumL = left.bestsufL;
        int resbestsumR = right.bestprefR;
        if (left.bestsum > resbestsum) {
            resbestsum = left.bestsum;
            resbestsumL = left.bestsumL;
            resbestsumR = left.bestsumR;
        }
        if (right.bestsum > resbestsum) {
            resbestsum = right.bestsum;
            resbestsumL = right.bestsumL;
            resbestsumR = right.bestsumR;
        }

        Segment result{
            resbestpref,
            resbestprefR,
            resbestsuf,
            resbestsufL,
            resbestsum,
            resbestsumL,
            resbestsumR,
            ressum
        };
        return result;
    }
};

struct SegmentTree {
    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = Segment(l, a[l]);
            return;
        }

        int m = (l + r) / 2;
        build(2*v, l, m);
        build(2*v+1, m+1, r);
        t[v] = merge(t[2*v], t[2*v+1]);
    }

    SegmentTree(int n, int x) : n(n), a(n, x) {
        t.resize(4*n);
        build(1, 0, n-1);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = Segment(l, val);
            return;
        }

        int m = (l + r) / 2;
        if (idx <= m) {
            _update(2*v, l, m, idx, val);
        } else {
            _update(2*v+1, m+1, r, idx, val);
        }
        t[v] = merge(t[2*v], t[2*v+1]);
    }

    void update(int idx, int val) {
        _update(1, 0, n-1, idx, val);
    }

    Segment _query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) {
            return Segment();
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = (l + r) / 2;
        return merge(
            _query(2*v, l, m, ql, qr),
            _query(2*v+1, m+1, r, ql, qr)
        );
    }

    Segment query(int ql, int qr) {
        return _query(1, 0, n-1, ql, qr);
    }

private:
    int n;
    vector<int> a;
    vector<Segment> t;
};

void solve() {
    /*
    - problem:
        - given an array, pick a subarray and an element such that the difference between (frequency of that
        element in subarray) and (frequency of anything else in subarray) is maximized
    - solution:
        - the basic idea is: we can iterate through each value in the array, transform the array so that all
        instances of it are 1 and all others are -1, and find the maximum subarray sum
        - to do this efficiently, we actually initialize the entire array to -1s and maintain a segment tree
        to find the best subarray (based on subarray sum), then for each value, we activate its indices to 1,
        query the segtree a single time, and deactivate its indices back to -1
    - details:
        - how tf did this implementation actually work on the first try?
            - update: this was true of my original implementation; my re-implementation was a little bit broken
            with both compiler and logical errors
        - regarding constructors of classes/structs:
            - if we define class A where one of the attributes contains (or simply IS) another class B that we define,
            then check to see if there are any implicit calls to class B's default constructor (such as in the creation
            of a non-empty vector containing class B), and if so, then make sure to define class B's constructor
            - in general, when implementing some code, start with the logic, then come up with any record-keeping
            variables, functions, or constructors that are needed to codify that logic
            - to call another constructor from one constructor, you basically just use initializer list syntax
        - when implementing a segment tree with explicit segments as objects, just make the query() function return
        an explicit segment and not a value; the relevant value can be extracted from the segment object
    */

    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;
    map<int, set<int>> indices;
    for (int i = 0; i < n; ++i) indices[x[i]].insert(i);

    SegmentTree st(n, -1);
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
