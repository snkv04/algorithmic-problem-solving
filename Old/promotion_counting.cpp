#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

struct SegmentTree {
    int n;
    vector<int> t;

    SegmentTree(int n) {
        this->n = n;
        t = vector<int>(4*n, 0);
    }

    void update(int qidx, int v, int l, int r) {
        if (l == r) {
            t[v] = 1;
            return;
        }

        int m = (l + r) / 2;
        if (qidx <= m) {
            update(qidx, 2*v, l, m);
        } else {
            update(qidx, 2*v+1, m+1, r);
        }
        t[v] = t[2*v] + t[2*v+1];
    }

    void update(int qidx) {
        update(qidx, 1, 0, n-1);
    }

    int query(int ql, int qr, int v, int l, int r) {
        if (l > qr || r < ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = (l + r) / 2;
        return query(ql, qr, 2*v, l, m) + query(ql, qr, 2*v+1, m+1, r);
    }

    int query(int ql, int qr) {
        return query(ql, qr, 1, 0, n-1);
    }
};

const int MAXN = 100005;
vector<int> adj[MAXN];
int idx = 0, ti[MAXN], tf[MAXN];

void dfs(int node) {
    ti[node] = idx++;
    for (int next : adj[node]) {
        dfs(next);
    }
    tf[node] = idx++;
}

void solve() {
    /**
     * we want to find out information about each subtree. generally, when we need information
     * about a node's subtree before processing that node, it likely means that it will have
     * something to do with post-order traversal (and the opposite means pre-order traversal),
     * but in this case we can use both pre-order and post-order in the form of an Euler tour.
     * using that technique, by marking the start and end times of visiting each node, we have
     * a new array of length 2*n in which each node corresponds to two elements, and the entirety
     * of any given node's subtree is contained within the interval bounded by those two indices.
     * knowing this, we don't have to do the entire problem in one pre-order or post-order
     * traversal. we can first obtain those start and end time values with the Euler tour, and
     * then visit the nodes in the order of descending p values (so that we might be jumping
     * around the tree), "activating" each node as we go and then querying the segment tree
     * for only each node's given range when we encounter it. this way, for any given node,
     * we correctly only look at the nodes within its subtree, and we also only collect the
     * nodes whose proficiency values are greater than that node's.
     */

    ifstream cin("promote.in");
    ofstream cout("promote.out");

    int n;
    cin >> n;
    pair<int, int> p[n];
    int ans[n];
    for (int i = 0; i < n; ++i) {
        int pi;
        cin >> pi;
        p[i] = pair<int, int>(i, pi);
    }
    sort(p, p+n, [](auto &p1, auto &p2) {
        return p1.second < p2.second;
    });
    
    for (int i = 1; i < n; ++i) {
        int parent; cin >> parent; --parent;
        adj[parent].push_back(i);
    }
    dfs(0);

    SegmentTree st(2*n);
    for (int i = n-1; i >= 0; --i) {
        int node = p[i].first;
        ans[node] = st.query(ti[node], tf[node]);
        st.update(ti[node]);
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
