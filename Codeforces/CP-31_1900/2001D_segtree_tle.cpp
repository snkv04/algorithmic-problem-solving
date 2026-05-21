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

struct SegmentTree {
    SegmentTree(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
    }

    SegmentTree(const std::vector<int> &arr) : arr(arr), n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int vertex, int left, int right) {
        if (left == right) {
            tree[vertex] = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid);
        build(2 * vertex + 1, mid + 1, right);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        if (right < query_left || query_right < left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return _query(2 * vertex, left, mid, query_left, query_right) +
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right);
    }

    int query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int idx, long long val) {
        if (left == right) {
            tree[vertex] = val;
            return;
        }

        int mid = left + (right - left) / 2;
        if (idx <= mid) {
            _update(2 * vertex, left, mid, idx, val);
        } else {
            _update(2 * vertex + 1, mid + 1, right, idx, val);
        }
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<int> arr;
};

struct Entry {
    int idx, val, distinct_to_right;
};

struct MxComp {
    bool operator()(const Entry &a, const Entry &b) {
        if (a.distinct_to_right != b.distinct_to_right) {
            return a.distinct_to_right < b.distinct_to_right;
        } else if (a.val != b.val) {
            return a.val < b.val;
        } else {
            return a.idx > b.idx;
        }
    }
};

struct MnComp {
    bool operator()(const Entry &a, const Entry &b) {
        if (a.distinct_to_right != b.distinct_to_right) {
            return a.distinct_to_right < b.distinct_to_right;
        } else if (a.val != b.val) {
            return a.val > b.val;
        } else {
            return a.idx > b.idx;
        }
    }
};

void solve() {
    /*
    - this solution gets TLE
    - the main algorithm is:
        - find the positions of every value of a[i], and "activate" (turn to 1, keeping everything else 0)
        all of the rightmost positions in a segment tree
            - the segtree is used for efficiently querying, "for a given index, how many distinct values are
            to the right of the index"?
        - iterate through each element of the subsequence we want to build, and for each:
            - pick either the max-leftmost or min-leftmost (based on index) element, using a priority queue
                - if the value has been used already, skip it (since we want our subsequence to only have
                distinct values)
                - if the index is <= the maximum index that we've already chosen, then move over to the minimum
                index for that same value that is > than the maximum index that we've already chosen (so that
                our subsequence moves from left to right)
                - if the number of distinct values to the right is outdated, which we measure in O(log n) using
                the segment tree, then update it and place it back into the priority queues
                - otherwise, everything is fine
            - then, we use that as part of our subsequence, and deactivate the rightmost index of that value
            in our segment tree
    - this solution is slow, because we might end up just repeatedly moving down the distinct-to-right value all
    the way from its original value to 1. to optimize this, we should realize that we don't actually care about
    a SINGLE index whose distinct-to-right value is less than the maximum, so we don't really have to keep track
    of the distinct-to-right values explicitly; we only look at indices which have sufficiently many distinct
    values to the right, which we can enforce using a set (see other solution for details).
        - for example, suppose for simplicity that we don't want an alternating subsequence, but we just want one
        with distinct elements and is lexicographically minimum, period.
        - then, an array like [5,4,3,2,1,5,4,3,2,1,5,4,3,2,1,5,4,3,2,1,5,4,3,2,1] would process every single element,
        leading to a complexity of (i think) O(n ^ log^2(n)).
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    
    map<int, set<int>> positions;
    for (int i = 0; i < n; ++i) {
        positions[a[i]].insert(i);
    }
    SegmentTree st(n);
    for (auto [k, v] : positions) st.update(*v.rbegin(), 1);

    priority_queue<Entry, vector<Entry>, MxComp> mx;
    priority_queue<Entry, vector<Entry>, MnComp> mn;
    set<int> processed_leftmost;
    for (int i = 0; i < n; ++i) {
        if (processed_leftmost.count(a[i]) == 0) {
            Entry e = {i, a[i], st.query(i, n - 1)};
            mx.push(e);
            mn.push(e);
            processed_leftmost.insert(a[i]);
        }
    }

    int k = positions.size();
    set<int> used;
    int max_idx = -1;
    vector<int> ans;
    for (int i = 1; i <= k; ++i) {
        int j, a_j;
        while (true) {
            Entry e;
            if (i % 2) {
                e = mx.top();
                mx.pop();
            } else {
                e = mn.top();
                mn.pop();
            }

            if (used.count(e.val)) {
                // continue;
            } else if (e.idx <= max_idx) {
                int idx = e.idx;
                while (idx <= max_idx) {
                    idx = *positions[e.val].upper_bound(idx);
                }

                Entry new_e = {idx, e.val, st.query(idx, n - 1)};
                mx.push(new_e);
                mn.push(new_e);
            } else if (e.distinct_to_right != st.query(e.idx, n - 1)) {
                Entry new_e = {e.idx, e.val, st.query(e.idx, n - 1)};
                mx.push(new_e);
                mn.push(new_e);
            } else {
                j = e.idx;
                a_j = e.val;
                break;
            }
        }

        max_idx = j;
        used.insert(a_j);
        ans.push_back(a_j);
        st.update(*positions[a_j].rbegin(), 0);
    }
    
    cout << ans.size() << "\n";
    for (int num : ans) cout << num << " ";
    cout << "\n";
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
