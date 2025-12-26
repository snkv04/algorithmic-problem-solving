#include <bits/stdc++.h>

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

void solve() {
    /*
    - basically the exact same idea as the slow solution, except we count the number of trees in an interval
    efficiently (using a segment tree, keyed on compressed coordinates), and we use repeated flooring on an
    ordered set to get the rightmost trees in an interval
    */

    int n, k;
    std::cin >> n >> k;
    std::map<int, int> compressed;
    std::set<int> x;
    for (int i = 0; i < n; ++i) { int xi; std::cin >> xi; x.insert(xi); compressed[xi] = -1; }
    std::vector<std::array<int, 3>> intervals(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cin >> intervals[i][j];
        }
        compressed[intervals[i][0]] = compressed[intervals[i][1]] = -1;
    }
    sort(intervals.begin(), intervals.end(), [](const std::array<int, 3> &first, const std::array<int, 3> &second) {
        return first[1] < second[1]; // sort by right endpoint
    });

    int i = 0;
    for (auto &e : compressed) {
        e.second = i++;
    }
    // for (auto e : compressed) {
    //     std::cout << "compressed[" << e.first << "] = " << e.second << std::endl;
    // }

    SegmentTree st(compressed.size());
    int ans = n;
    for (auto interval : intervals) {
        int l = interval[0], r = interval[1], t = interval[2];
        int req = std::max(0LL, t - st.query(compressed[l], compressed[r]));

        ans -= req;
        if (req) while (req--) {
            auto it = x.upper_bound(r);
            --it;
            // std::cout << "floor of " << r << " is " << *it << std::endl;
            st.update(compressed[*it], 1);
            x.erase(it);
        }
    }
    std::cout << ans << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
