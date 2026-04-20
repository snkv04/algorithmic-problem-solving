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

    long long query(int left, int right) {
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

struct MxComp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second != b.second) {
            return a.second < b.second;
        } else {
            return a.first > b.first;
        }
    }
};

struct MnComp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first > b.first;
        }
    }
};

void solve() {
    /*
    - problem:
        - we have an array.
        - we want to find the longest subsequence such that all elements are distinct.
        - if there are multiple, then we want to lexicographically minimize the modified subsequence, where we
        modify our subsequence by taking our subsequence and multiply every other element by -1.
    - solution:
        - finding the length of the longest subsequence is trivial: just the number of distinct elements.
        - for each element of our subsequence with index i, we require that the number of distinct values
        to the right of it is at least (k - i). so, we can keep track of the index for each value in a set;
        if there are multiple instances of that value, we use the rightmost index, so that the value counts
        as a "distinct value to the right" for as many indices as possible.
        - then, all we need to do is repeatedly pick the optimal value to the left (inclusive) of the
        leftmost-rightmost index of an unused element, and when we pick an element, we remove it from that list
        of indices. if that removal relaxes our restriction on indices, then we add all the new candidates into
        the prioqueues.
    - key observations:
        - suppose there are k distinct elements in total, and we are picking our i'th element of the subsequence.
        then, if we are to pick the element at index j, then we want (k+1-i) distinct elements at or to the right
        of index j, because otherwise, we won't be able to pick our later elements.
        - so, among all such indices j such that there are (k+1-i) distinct elements at or to the right of j,
        we can apply our greedy "min (or max) + leftmost" strategy. any such j will work.
        - then, we can keep our set of rightmost indices for all unpicked distinct elements, and any j <= the leftmost
        value in that set is fine. to pick the best one, we just use a priority queue (or, two of them, since we
        need to alternate our strategy for each element, though intuitively we can imagine just using one and taking
        the lexicographically minimum overall subsequence to understand the logic) to pick that element in O(log n),
        and throw all viable candidates into that priority queue.
        - when we pick an element, we remove its rightmost index from that set of "rightmost indices of unpicked
        values" indices. if that pushes the leftmost value in that set to the right, then we look at all indices
        that are now available, and drop them into our prioqueues.
    - useful ideas:
        - think of the "rightmosts" set as a set of values whose minimum value dictates what indices we're allowed
        to take. anything to the left of that is fine. if that minimum value gets updated, then we now have more
        candidates.
            - it's really just a set of indices of unused values, where ANYTHING to the left of ALL of them is a
            viable candidate. the only reason why there would be more than 1 value to the left of ALL of them
            is that a value can show up multiple times.
        - think of a prioqueue as something we just throw candidate values into, where the ordering that we impose
        lets us select the best one efficiently. we do, however, have to make sure to deal with "out-of-date" entries,
        which exist because we can't remove anything from a prioqueue from anywhere other than the top.
    */

    // gets inputs
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    
    // keeps track of all indices of unused elements; if multiple instances, then use rightmost index
    map<int, int> last_pos;
    for (int i = 0; i < n; ++i) {
        last_pos[a[i]] = i;
    }
    set<int> rightmosts;
    for (auto [k, v] : last_pos) rightmosts.insert(v);

    // fills in initial candidates, which are just those that are to the left (inclusive) of the leftmost
    // unused element
    priority_queue<pair<int, int>, vector<pair<int, int>>, MxComp> mx;
    priority_queue<pair<int, int>, vector<pair<int, int>>, MnComp> mn;
    for (int i = 0; i <= *rightmosts.begin(); ++i) {
        mx.push(make_pair(i, a[i]));
        mn.push(make_pair(i, a[i]));
    }

    // builds our subsequence one-by-one, by taking our best candidate with prioqueues.
    // if this expands the set of possible candidates, then add those new candidates to our prioqueues.
    int k = last_pos.size();
    set<int> used;
    int max_idx = -1;
    vector<int> ans;
    for (int i = 1; i <= k; ++i) {
        // gets best candidate
        int j, a_j;
        if (i % 2) {
            while (mx.top().first < max_idx || used.count(mx.top().second)) {
                mx.pop();
            }

            auto p = mx.top();
            j = p.first; a_j = p.second;
            mx.pop();
        } else {
            while (mn.top().first < max_idx || used.count(mn.top().second)) {
                mn.pop();
            }

            auto p = mn.top();
            j = p.first; a_j = p.second;
            mn.pop();
        }

        // processes candidate
        max_idx = j;
        used.insert(a_j);
        ans.push_back(a_j);
        rightmosts.erase(last_pos[a_j]);

        // adds new candidates, if applicable
        if (rightmosts.size() && *rightmosts.begin() > last_pos[a_j]) {
            for (int idx = last_pos[a_j] + 1; idx <= *rightmosts.begin(); ++idx) {
                mx.push(make_pair(idx, a[idx]));
                mn.push(make_pair(idx, a[idx]));
            }
        }
    }
    
    // outputs built subsequence
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
