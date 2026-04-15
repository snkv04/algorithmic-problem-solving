#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

struct LazySegmentTree {
    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = (l + r) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    LazySegmentTree(vector<int> &a) : a(a), n(a.size()), t(4 * n, 0), p(4 * n, -1) {
        build(1, 0, n - 1);
    }

    void push_down(int v, int l, int r) {
        if (p[v] != -1) {
            t[v] = p[v] * (r - l + 1);

            if (l != r) {
                p[2 * v] = p[2 * v + 1] = p[v];
            }

            p[v] = -1;
        }
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        // as soon as we look at this node, make sure that anything pending for this node has been processed
        push_down(v, l, r);

        if (r < ql || qr < l) return 0;
        if (ql <= l && r <= qr) return t[v];

        int m = (l + r) / 2;
        return _query(2 * v, l, m, ql, qr) + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int l, int r) {
        return _query(1, 0, n - 1, l, r);
    }

    void _update(int v, int l, int r, int ql, int qr, int val) {
        // as soon as we look at this node, make sure that anything pending for this node has been processed
        push_down(v, l, r);

        if (r < ql || qr < l) return;
        if (ql <= l && r <= qr) {
            // on a lazy data structure, never directly update the tree; only schedule a pending update,
            // and let push_down handle all of the updating of the tree.
            p[v] = val;
            push_down(v, l, r);
            return;
        }

        int m = (l + r) / 2;
        _update(2 * v, l, m, ql, qr, val);
        _update(2 * v + 1, m + 1, r, ql, qr, val);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int l, int r, int val) {
        _update(1, 0, n - 1, l, r, val);
    }

private:
    vector<int> a;
    int n;
    vector<ll> t, p;  // "tree", "pending"
};

void add(int x, map<int, int> &elems, map<int, int> &freqs) {
    int old_freq = elems.count(x) ? elems[x] : 0;
    if (old_freq) {
        freqs[old_freq] -= 1;
        if (!freqs[old_freq]) {
            freqs.erase(old_freq);
        }
    }

    int new_freq = old_freq + 1;
    elems[x] = new_freq;

    freqs[new_freq] += 1;
}

void remove(int x, map<int, int> &elems, map<int, int> &freqs) {
    int old_freq = elems[x];
    freqs[old_freq] -= 1;
    if (!freqs[old_freq]) {
        freqs.erase(old_freq);
    }

    int new_freq = old_freq - 1;
    if (new_freq) {
        elems[x] = new_freq;
    } else {
        elems.erase(x);
    }

    if (new_freq) {
        freqs[new_freq] += 1;
    }
}

vector<int> get_window_answers(vector<int> &a, int k) {
    map<int, int> elems, freqs;
    for (int i = 0; i < k; ++i) {
        elems[a[i]] += 1;
    }
    for (auto [k, v] : elems) {
        freqs[v] += 1;
    }

    int n = a.size();
    vector<int> wa(n, 1e9);
    wa[k - 1] = k - freqs.rbegin()->first;
    for (int i = k; i < n; ++i) {
        int adding = a[i], removing = a[i - k];
        add(adding, elems, freqs);
        remove(removing, elems, freqs);
        wa[i] = k - freqs.rbegin()->first;
    }
    return wa;
}

vector<int> get_next_indices(vector<int> &v, int k) {
    int n = v.size();
    stack<int> stk;
    vector<int> next(n, -1);
    for (int i = k - 1; i <= n; ++i) {
        int val = i == n ? -1e9 : v[i];
        while (stk.size() && v[stk.top()] > val) {
            next[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    return next;
}

void solve() {
    /*
    - a few more useful ideas:
        - can reorder queries, answer them offline, and then output them in the requested order. why is this
        useful? sweep-line algorithms are the classical case: it is useful when we can efficiently answer the
        queries by doing some processing across the input and answering queries when they coincide with where
        we currently are in the input (during that processing) instead of answering queries in the given order.
        - the brute-force solution is to, for each (l, r) pair, take the corresponding prefix-minimum array
        of that subarray, and sum it. the efficient solution is to sweep an index i from n - 1 to k - 1 (don't
        have to go any more left than that), and for each i, turn the ENTIRE suffix from i to n - 1 into a
        prefix-minimum array, getting the sum from l = i to some r >= l with a segment tree. a lazy segment
        tree is particularly useful here: for turning [i, n - 1] into a prefix-minimum array, we need to do
        range-set operations (which a lazy segtree provides), and for the queries, we also need range-sum
        operations over arbitrary intervals (which a lazy segtree also provides).
            - why does the prefix-minimum array creation require range-setting? because when moving to index
            i from i + 1, the contiguous segment of indices j >= i where wa[j] >= wa[i] must all be set to wa[i].
            basically, the whole prefix that's greater than or equal to that new element is now set to that
            element, and then the definitional prefix-minimum condition is maintained.
            - why do we create prefix-minimum arrays from right to left? well, what are the alternatives?
                - suppose we want to make prefix-minimum arrays from left to right. that would require un-setting
                a bunch of elements: imagine we have the minimum element of that whole suffix on the left side;
                then moving the suffix over by 1 to the right will update a bunch of elements to new values that
                are possibly different from each other. moving from right to left requires a single "set" operation
                for each index, because all those elements are set to the same value.
                - suppose we want to use suffix minimum/maximum arrays here. in general, it's good to think
                of opposites or complements, but that doesn't make sense in this context at all. the two do not
                have any special relation, other than that pm[n - 1] == sm[0].
            - why is it okay that we modify the ENTIRE suffix starting at index i into a prefix-minimum
            array (and not just the subarray from i to a corresponding query's r value)? for a query of (l, r)
            where l == i, the prefix-minimum array we want from l to r is literally just a subarray (the prefix)
            of the prefix-minimum array from l to n - 1. in other words, the fact that the elements after r also
            happen to satisfy the prefix-minimum array condition literally does not negatively impact anything.
            so, we don't only have to turn the subarray [l, r] into the prefix-minimum array; we can also do
            that to the elements on the right, and it doesn't cause any problems.
        - this problem is one case where the answer for a full subarray is equal to a combination of the answers
        for all size-k subarrays within it. so, we calculate the answer for each window, and proceed for the rest
        of the problem with that as a given.
        - when making a prefix-minimum array, the elements that are set to a[0] are all those elements contiguously
        to the right of index 0 such with an index i such that a[i] >= a[0]. the maximum such index for index 0
        can be found with a linear scan, but the maximum such index for all indices can be found with a monotonic
        stack. basically, the elements that are updated are all those {to the left} of {the next one to the right
        that's less than the current one}.
    */

    // reads in input
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    cin >> a;

    // reads in queries and sorts them by left bound
    vector<array<ll, 4>> queries;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l += k - 2;
        r -= 1;
        queries.push_back(array<ll, 4>({i, l, r, 0}));
    }
    sort(queries.begin(), queries.end(), [](const array<ll, 4> &a, const array<ll, 4> &b) {
        return a[1] < b[1];
    });

    // gets answers for each size-k window (so indices < k - 1 are effectively unused),
    // and computes "next" indices
    for (int i = 0; i < n; ++i) a[i] -= i;
    vector<int> wa = get_window_answers(a, k);
    vector<int> next = get_next_indices(wa, k);

    // builds segtree and answers all queries
    int q_idx = q - 1;
    LazySegmentTree lz(wa);
    for (int i = n - 1; i >= k - 1; --i) {
        int next_below_idx = next[i];
        lz.update(i, next_below_idx - 1, wa[i]);
        while (q_idx != -1 && queries[q_idx][1] == i) {
            queries[q_idx][3] = lz.query(i, queries[q_idx][2]);
            q_idx -= 1;
        }
    }

    // reorders and outputs queries
    sort(queries.begin(), queries.end());
    for (int i = 0; i < q; ++i) {
        cout << queries[i][3] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
