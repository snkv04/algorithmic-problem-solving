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
        t.resize(4*n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n-1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2*v, l, m);
        build(2*v + 1, m+1, r);
        t[v] = t[2*v] + t[2*v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) {
            return 0;
        }
        if (l >= ql && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2*v, l, m, ql, qr)
            + _query(2*v+1, m+1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n-1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2*v, l, m, idx, val);
        } else {
            _update(2*v+1, m+1, r, idx, val);
        }
        t[v] = t[2*v] + t[2*v+1];
    }

    void update(int idx, int val) {
        _update(1, 0, n-1, idx, val);
    }
};

ll count_inversions(vector<int> &v) {
    map<int, int> mp;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        mp[v[i]] = i;
    }

    vector<int> sorted = v;
    sort(sorted.begin(), sorted.end());
    SegmentTree st(vector<int>(n, 0));
    ll inversions = 0;
    for (int i = 0; i < n; ++i) {
        int idx = mp[sorted[i]];
        st.update(idx, 1);
        if (idx < n-1) 
            inversions += st.query(idx+1, n-1);
    }
    return inversions;
}

void solve() {
    /*
    notes:
    - since all the elements are distinct, swapping any two elements that are
    adjacent will change the number of inversions by exactly 1. so, swapping
    any two adjacent pairs of adjacent elements will change the number of inversions
    by 0, 2, or 4, meaning that the parity of inversions stays invariant.

    generalizable rules?
    - sorting and inversions are closely related topics. aside from thinking
    of sorting as making every pair of adjacent elements such that the left
    is leq the right, it can also be thought of as eliminating inversions.
    so, when dealing with problems that involve sorting, take a moment to think
    about if it connects to inversions
    - i came up with a way to count the number of inversions in an array with
    distinct elements in O(n log n), and i'm not sure if this idea has been done
    before (though something similar surely has). basically, map each element
    to its index, and then iterate through the elements in ascending order.
    for each element, we know the amount of elements that we've already iterated
    through, and those elements are all less than the current element, meaning
    that they SHOULD be to the left of the current element if they aren't
    inversions. so, for each element, first "activate" it (find its index and
    set its value from 0 to 1 in a separate segment tree), and then use the
    segment tree to find the number of activated elements to the right of it.
    this way, we find the number of inversions in the form of pairs (i, j)
    where j is the current element and i is an element less than the current
    element, and this avoids double counting.
    */

    int n;
    cin >> n;
    vector<int> even, odd, before(n, 0);
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        before[i] = ai;
        if (i % 2) {
            odd.push_back(ai);
        } else {
            even.push_back(ai);
        }
    }
    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());

    vector<int> result;
    for (int i = 0; i < n; ++i) {
        int lowest;
        if (i % 2) {
            lowest = odd[i/2];
        } else {
            lowest = even[i/2];
        }
        result.push_back(lowest);
    }

    ll inversionsbefore = count_inversions(before),
        inversionsafter = count_inversions(result);
    if (inversionsbefore % 2 != inversionsafter % 2) {
        swap(result[n-1], result[n-3]);
    }

    for (int i = 0; i < n; ++i) {
        cout << result[i] << " ";
    }
    cout << "\n";
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
