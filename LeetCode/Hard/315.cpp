struct SegmentTree {
private:
    int n;
    vector<int> t;

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

    int _query(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return t[v];
        }
        if (r < ql || qr < l) {
            return 0;
        }

        int m = l + (r - l) / 2;
        return (
            _query(2*v, l, m, ql, qr)
            + _query(2*v+1, m+1, r, ql, qr)
        );
    }

public:
    SegmentTree(int n) {
        this->n = n;
        t.resize(4*n);
        fill(t.begin(), t.end(), 0);
    }

    void update(int idx, int val) {
        _update(1, 0, n-1, idx, val);
    }

    int query(int ql, int qr) {
        return _query(1, 0, n-1, ql, qr);
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int>> sorted;
        for (int i = 0; i < n; ++i) sorted.push_back(make_pair(i, nums[i]));
        sort(
            sorted.begin(),
            sorted.end(),
            [](const pair<int, int> &p1, const pair<int, int> &p2) {
                if (p1.second != p2.second) {
                    return p1.second < p2.second;
                } else {
                    return p1.first < p2.first;
                }
            }
        );

        SegmentTree st(n);
        vector<int> ans(n, 0);
        for (const pair<int, int> p : sorted) {
            int idx = p.first;
            ans[idx] = st.query(idx, n-1);
            st.update(idx, 1);
        }
        return ans;
    }
};
