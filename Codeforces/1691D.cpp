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

    SegmentTree(const std::vector<long long> &arr) : arr(arr), n(arr.size()) {
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
        tree[vertex] = max(tree[2 * vertex], tree[2 * vertex + 1]);
    }

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        if (right < query_left || query_right < left) {
            return -1e15;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return max(
            _query(2 * vertex, left, mid, query_left, query_right),
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right)
        );
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
        tree[vertex] = max(tree[2 * vertex], tree[2 * vertex + 1]);
    }

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<long long> arr;
};

void solve() {
    /*
    - problem:
        - we are given an array, and we want to check if, for all subarrays [l, r], we have that
        max(l, r) >= sum(l, r)
    - solution:
        - first off, we can limit the pairs (l, r) that we look at from ALL pairs (l, r) to only pairs
        (l, r) such that a[l] and a[r] are both positive
            - why? suppose we have a "problematic" subarray (l, r), meaning that the sum is > the max.
            if all elements in [l, r] are negative, then this is impossible.
            if there are positive elements but there are negative elements on the ends, then we can always
            strip off the negative elements on the ends and still have a problematic subarray,
            because the max won't increase but the sum will. so, we only need to search subarrays such that
            the first and last element are positive.
        - then, we can limit the pairs that we look at to only the pairs (l, r) such that
        max(a[l], a[l+1], ..., a[r]) is at the left or right end of the interval
            - why? suppose we have a "problematic" subarray (l, r) where max(a[l], a[l+1], ..., a[r]) lies
            strictly between l and r, by index. then, let d=sum(l,r)-max(l,r). we know that
            d=sum(l, max_idx-1)+sum(max_idx+1, r), and since d > 0, at least one of those 2 sides is positive.
            so, we can drop the other side, and since the positive side plus the max will be > the max, we
            still have a problematic subarray. therefore, we only need to search subarrays with the max element
            on (at least) one of the sides.
        - as a result, we can iterate through all possible maximum values in the array (every positive
        element, though every single element would also work), and for each, look at all the subarrays
        where that element is the max element and is either on the left or right end
            - for ensuring we don't have a greater element, we can find the index bounds for each element
            using monotonic stacks
            - for efficiently finding the maximum subarray sum where index i is our left bound, we can
            take prefix sums and find the maximum prefix sum in the interval [i, next(i)) using a segment tree;
            we can apply similar logic to the case where index i is our right bound
    - core idea:
        - plop a segment tree down on top of the array of prefix sums, in order to find the max in a certain range
        - why only in a certain range? because:
            - we’re using prefix sums to find subarray sums
            - the left bound of the subarray is fixed
            - the rightmost index for the right bound of the subarray is also fixed
            (due to wanting to ensure that the current element is the max element in the subarray)
    - details:
        - when using a monotonic stack, consider if we want to count equal elements as the “next greater” or not.
            - if we don’t, then [i, next(i)) can include indices j > i such that a[i] == a[j].
            - if we do, then such a thing won’t happen, and all indices j > i in that interval will have a[j] < a[i].
        in this problem, we don’t want to, because we DO want to check subarrays that start and end with the
        same value (e.g., [5, -1, -1, -1, -1, 5])

    */

    // reads in input, and removes 0s (though that second step is probably unnecessary)
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    a.erase(std::remove(a.begin(), a.end(), 0), a.end());
    if (a.empty()) {
        cout << "YES\n";
        return;
    }

    // finds next greater and previous greater element for each index
    n = a.size();
    vector<int> next(n), prev(n);
    stack<int> s;
    for (int i = 0; i <= n; ++i) {
        int val = i == n ? 2e9 : a[i];
        while (s.size() && a[s.top()] < val) {
            next[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    s = stack<int>();
    for (int i = n - 1; i >= -1; --i) {
        int val = i == -1 ? 2e9 : a[i];
        while (s.size() && a[s.top()] < val) {
            prev[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }

    // computes prefix and suffix sums
    vector<ll> pref(n, 0), suf(n, 0);
    for (int i = 0; i < n; ++i) pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
    for (int i = n - 1; i >= 0; --i) suf[i] = (i == n - 1 ? 0 : suf[i + 1]) + a[i];

    // makes segment tree out of prefix and suffix sums,
    // and finds max subarray sum for each element
    // assuming that that element is the subarray's max element AND
    // that it's on one of the sides
    SegmentTree pref_st(pref), suf_st(suf);
    for (int i = 0; i < n; ++i) {
        if (a[i] > 0) {
            ll max_if_start = pref_st.query(i, next[i] - 1) - (i == 0 ? 0 : pref[i - 1]);
            ll max_if_end = suf_st.query(prev[i] + 1, i) - (i == n - 1 ? 0 : suf[i + 1]);
            if (max_if_start > a[i] || max_if_end > a[i]) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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
