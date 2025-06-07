#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAXN = 200005;
int a[MAXN];

struct Lazy {
    int n;
    vector<ll> t;
    vector<vector<ll>> lz;

    void build(int vertex, int l, int r, vector<int> &a) {
        if (l == r) {
            t[vertex] = a[l];
        } else {
            int m = (l + r) / 2;
            build(2*vertex, l, m, a);
            build(2*vertex+1, m+1, r, a);
            t[vertex] = t[2*vertex] + t[2*vertex+1];
            // cout << "setting t["<<vertex<<"], which controls "<<l<<" to "<<r<<", to "<<t[vertex]<<'\n';
        }
    }

    // is more worth being its own method when multiple types of range updates are done
    void apply(int v, int len, ll type, ll val) {
        if (type == 1) {
            // cout << "v = " << v << "\n";
            lz[v][0] = type;
            lz[v][1] = val;
            t[v] = val * len;
        }
        // if type == 0, then there's no operation to do
    }

    void push_down(int v, int l, int r) {
        int m = (l + r) / 2;
        apply(2*v, m-l+1, lz[v][0], lz[v][1]);
        apply(2*v+1, r-m, lz[v][0], lz[v][1]);
        lz[v][0] = 0;
        lz[v][1] = 0;
    }

    void range_set(int ul, int ur, ll val, int v, int l, int r) {
        if (ur < l || ul > r) return;
        if (ul <= l && r <= ur) {
            int type = 1; // for setting
            apply(v, r-l+1, type, val);
            return;
        }

        push_down(v, l, r);
        int m = (l + r) / 2;
        range_set(ul, ur, val, 2*v, l, m);
        range_set(ul, ur, val, 2*v+1, m+1, r);
        t[v] = t[2*v] + t[2*v+1];
    }

    void range_set(int update_left, int update_right, ll val) {
        range_set(update_left, update_right, val, 1, 0, n-1);
    }

    ll range_sum(int ql, int qr, int v, int l, int r) {
        if (qr < l || ql > r) return 0;
        if (ql <= l && r <= qr) return t[v];

        push_down(v, l, r);
        int m = (l + r) / 2;
        return range_sum(ql, qr, 2*v, l, m) + range_sum(ql, qr, 2*v+1, m+1, r);
    }

    ll range_sum(int query_left, int query_right) {
        return range_sum(query_left, query_right, 1, 0, n-1);
    }

    Lazy(vector<int> &a) {
        n = a.size();
        // cout << "SIZE OF INPUT ARRAY = " << n << "\n";
        t = vector<ll>(4*n, 0);
        lz = vector<vector<ll>>(4*n, vector<ll>(2, 0));
        build(1, 0, n-1, a);
    }
};

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] -= i; // just does the update right here
    }

    unordered_map<int, int> diffs_multiset;
    map<int, int> freqs_multiset;
    for (int i = 0; i < k; ++i) {
        // if (diffs_multiset.find(a[i]) == diffs_multiset.end()) {
        //     diffs_multiset[a[i]] = 0;
        // }
        ++diffs_multiset[a[i]];
    }
    for (const auto &p : diffs_multiset) {
        // if (freqs_multiset.find(p.second) == freqs_multiset.end()) {
        //     freqs_multiset[p.second] = 0;
        // }
        ++freqs_multiset[p.second];
    }
    // for (int i = 0; i < n; ++i) {
    //     cout << "a[" << i << "] = " << a[i] << '\n';
    // }
    // cout << "starting freqs = " << '\n';
    // for (const auto &p : freqs_multiset) {
    //     cout << p.first << ": " << p.second << '\n';
    // }
    
    int best[n];
    // fill(best, best+n, 0);
    best[0] = k - (*freqs_multiset.rbegin()).first;
    for (int i = 1; i <= n-k; ++i) {
        int removing = a[i-1], adding = a[i+k-1];

        int f = diffs_multiset[removing];
        --freqs_multiset[f];  if (freqs_multiset[f] == 0) freqs_multiset.erase(f);
        --diffs_multiset[removing]; if (diffs_multiset[removing] == 0) diffs_multiset.erase(removing);
        if (f-1 > 0) ++freqs_multiset[f-1];

        f = diffs_multiset[adding];
        if (freqs_multiset[f] > 0) --freqs_multiset[f]; // if (freqs_multiset[f] == 0) freqs_multiset.erase(f);
        ++diffs_multiset[adding];
        ++freqs_multiset[f+1];

        best[i] = k - (*freqs_multiset.rbegin()).first;
    }
    // for (int i =0 ; i < n; ++i) {
    //     cout << "best[" << i << "] = " << best[i] << '\n';
    // }

    vector<vector<ll>> queries(q, vector<ll>(4, 0));
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        queries[i][0] = l;
        queries[i][1] = r;
        queries[i][2] = i;
    }
    sort(queries.begin(), queries.end(), [](vector<ll> &a, vector<ll> &b){return a[0] < b[0];});

    stack<int> s;
    int rightBounds[n];
    // fill(rightBounds, rightBounds+n, 0);
    for (int i = 0; i <= n-k+1; ++i) {
        int curr_val = i == n-k+1 ? -1 : best[i];
        while (!s.empty() && best[s.top()] > curr_val) {
            int popping = s.top();
            s.pop();
            rightBounds[popping] = i-1;
        }
        s.push(i);
    }

    int last = n-k+1;
    vector<int> as_vec(best, best+n);
    // cout << "as vec: ";
    // for (int i =0 ; i < n; ++i) cout << as_vec[i] << " ";
    // cout << '\n';
    Lazy segtree(as_vec);
    for (int i = q-1; i >= 0; --i) {
        int l = queries[i][0], r = queries[i][1];
        for (int j = last-1; j >= l; --j) {
            segtree.range_set(j, rightBounds[j], best[j]);
        }
        queries[i][3] = segtree.range_sum(l, r-k+1);
        last = l;
    }
    sort(queries.begin(), queries.end(), [](vector<ll> a, vector<ll> b){return a[2] < b[2];});

    for (int i = 0; i < q; ++i) {
        cout << queries[i][3] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}