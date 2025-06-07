#include <bits/stdc++.h>
using namespace std;

struct DSU {
  private:
    vector<int> parent, sz;

  public:
    DSU(int length) {
        parent = vector<int>(length, -1);
        sz = vector<int>(length, 1);
        for (int i = 0; i < length; ++i) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) {
            return node;
        } else {
            parent[node] = find(parent[node]);
            return parent[node];
        }
    }

    void u(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            parent[d] = c;
            int newsize = sz[c] + sz[d];
            sz[c] = newsize;
            sz[d] = newsize;
        }
    }

    int size(int node) {
        return sz[find(node)];
    }
};

bool cmp(pair<pair<int, int>, int> &a, pair<pair<int, int>, int> &b) {
    return a.second < b.second;
}

bool cmp2(array<int, 3> &a, array<int, 3> &b) {
    return a[1] >= b[1];
}

void solve() {
    ifstream fin("mootube.in");
    ofstream fout("mootube.out");

    int n, q;
    fin >> n >> q;
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < n-1; ++i) {
        int pi, qi, ri;
        fin >> pi >> qi >> ri;
        --pi; --qi;
        edges.push_back(make_pair(make_pair(pi, qi), ri));
    }
    sort(edges.begin(), edges.end(), cmp);

    // so it looks like the main culprit of the memory limit exceeded error
    // was either making a 100,000x4 vector or sorting it; with this approach,
    // we make a 100,000x3 vector and make another length-100,000 vector for
    // holding the answers
    vector<array<int, 3>> queries;
    for (int i = 0; i < q; ++i) {
        int k, v;
        fin >> k >> v;
        array<int, 3> query;
        query[0] = i; query[1] = k; query[2] = --v;
        queries.push_back(query);
    }
    sort(queries.begin(), queries.end(), cmp2);

    int j = n-2;
    DSU dsu(n);
    vector<int> ans(q, -1);
    for (int i = 0; i < q; ++i) {
        int k = queries[i][1], v = queries[i][2];
        while (j >= 0 && edges[j].second >= k) {
            dsu.u(edges[j].first.first, edges[j].first.second);
            --j;
        }
        ans[queries[i][0]] = dsu.size(v) - 1;
    }

    for (int i = 0; i < q; ++i) {
        fout << ans[i];
        if (i == q-1) {
            fout << endl;
        } else {
            fout << '\n';
        }
    }

    fin.close();
    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();

    return 0;
}
