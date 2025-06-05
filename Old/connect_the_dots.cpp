#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

struct DSU {
    int n;
    vector<int> parent;

    DSU(int n) {
        this->n = n;
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        else {
            parent[x] = find(parent[x]);
            return parent[x];
        }
    }

    void unite(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            parent[d] = c;
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> endpoints(n, vector<int>(11, 0));
    while (m--) {
        int a, d, k;
        cin >> a >> d >> k;
        --a;
        ++endpoints[a][d];
        --endpoints[a+d*k][d];
    }

    DSU dsu(n);
    for (int step = 1; step <= 10; ++step) {
        for (int mod = 0; mod < step; ++mod) {
            int curr = 0;
            for (int i = mod; i < n; i += step) {
                curr += endpoints[i][step];
                if (curr) {
                    dsu.unite(i, i + step);
                }
            }
        }
    }

    unordered_set<int> unique;
    for (int i = 0; i < n; ++i) {
        unique.insert(dsu.find(i));
    }
    cout << unique.size() << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
