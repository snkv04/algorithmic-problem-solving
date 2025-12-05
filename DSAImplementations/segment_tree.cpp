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
