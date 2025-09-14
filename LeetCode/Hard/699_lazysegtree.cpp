struct LazySegmentTree {
private:
    int n;
    vector<int> tree;
    vector<int> lazy;

    void _pushDown(int v, int vl, int vr) {
        if (lazy[v]) {
            // performs the update on the current node
            tree[v] = lazy[v];

            // marks a pending update on the child nodes if they exist
            if (vl != vr) {
                lazy[2*v] = lazy[v];
                lazy[2*v+1] = lazy[v];
            }

            // marks that there's no longer a pending update on the node
            lazy[v] = 0;
        }
    }

    void _update(int v, int vl, int vr, int l, int r, int val) {
        _pushDown(v, vl, vr);

        if (vr < l || vl > r) {
            return;
        }
        if (l <= vl && vr <= r) {
            lazy[v] = val;
            _pushDown(v, vl, vr);
            return;
        }

        int vm = vl + (vr - vl) / 2;
        _update(2*v, vl, vm, l, r, val);
        _update(2*v+1, vm+1, vr, l, r, val);
        tree[v] = max(tree[2*v], tree[2*v+1]);
    }

    int _query(int v, int vl, int vr, int l, int r) {
        _pushDown(v, vl, vr);

        if (vr < l || vl > r) return -1e9;
        if (l <= vl && vr <= r) return tree[v];

        int vm = vl + (vr - vl) / 2;
        return max(
            _query(2*v, vl, vm, l, r),
            _query(2*v+1, vm+1, vr, l, r)
        );
    }

public:
    LazySegmentTree(int n) {
        this->n = n;
        tree.resize(4 * n);
        fill(tree.begin(), tree.end(), 0);
        lazy.resize(4 * n);
        fill(lazy.begin(), lazy.end(), 0);
    }

    void update(int update_left, int update_right, int val) {
        _update(1, 0, n-1, update_left, update_right, val);
    }

    int query(int query_left, int query_right) {
        return _query(1, 0, n-1, query_left, query_right);
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>> &positions) {
        set<int> distinct;
        for (vector<int> &position : positions) {
            distinct.insert(position[0]);
            distinct.insert(position[0] + position[1] - 1);
        }

        map<int, int> to_compressed;
        int idx = 0;
        for (int orig_coord : distinct) {
            to_compressed[orig_coord] = idx++;
        }

        vector<int> answers;
        int len = to_compressed.size();
        LazySegmentTree tree(len);
        for (vector<int> &position : positions) {
            int l = to_compressed[position[0]];
            int r = to_compressed[position[0] + position[1] - 1];
            int h = position[1];

            int max_height = tree.query(l, r);
            max_height += h;
            tree.update(l, r, max_height);

            answers.push_back(
                max(
                    max_height,
                    answers.size() ? answers[answers.size()-1] : 0
                )
            );
        }
        return answers;
    }
};
