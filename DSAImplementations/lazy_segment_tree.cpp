#include <bits/stdc++.h>

struct Lazy {
    Lazy(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        pending.resize(4 * n);
        std::fill(pending.begin(), pending.end(), 0);
    }

    Lazy(const std::vector<int> &arr) : arr(arr), n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        pending.resize(4 * n);
        std::fill(pending.begin(), pending.end(), 0);
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

    void push_down(int vertex, int left, int right) {
        if (pending[vertex] != 0) {
            tree[vertex] += pending[vertex] * (right - left + 1);

            if (left != right) {
                pending[2 * vertex] += pending[vertex];
                pending[2 * vertex + 1] += pending[vertex];
            }

            pending[vertex] = 0;
        }
    }

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        push_down(vertex, left, right);

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

    void _update(int vertex, int left, int right, int query_left, int query_right, long long val) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            pending[vertex] += val;
            push_down(vertex, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        _update(2 * vertex, left, mid, query_left, query_right, val);
        _update(2 * vertex + 1, mid + 1, right, query_left, query_right, val);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    void update(int left, int right, long long val) {
        _update(1, 0, n - 1, left, right, val);
    }

private:
    int n;
    std::vector<long long> tree, pending;
    std::vector<int> arr;
};
