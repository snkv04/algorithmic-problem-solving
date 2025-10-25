#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; 
    cin >> n >> m;
    vector<int> len(n, 0);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        len[i] = k;
    }
    vector<int> dep(n, n);
    vector<bool> isdep(n, false);
    for (int i = 0; i < m; i++) {
        int k, l;
        cin >> k >> l;
        k--;
        l--;
        dep[l] = k;
        isdep[k] = true;
    }
    priority_queue<pair<int,int>> pq;
    for (int i = 0; i < n; i++) {
        if (!isdep[i])
            pq.push({0, i});
    }

    vector<int> visited(n+1, 0);
    vector<int> dists(n+1, 0);
    while (pq.size()) {
        pair<int, int> p = pq.top();
        pq.pop();
        
        int d = p.first;
        int v = p.second;
        //cout << d << " " << v << endl;
        if (visited[v] == 2) {
            continue;
        }
        dists[v] += d;
        visited[v]++;

        if (v != n)
            pq.push({d - len[v], dep[v]});
    }

    for  (int i = 0; i <= n; i++) {
        if (visited[i] == 2)
            pq.push({dists[i], i});
    }
    while (pq.size()) {
        pair<int, int> p = pq.top();
        pq.pop();
        
        int d = p.first;
        int v = p.second;
        //cout << d << " " << v << endl;
        if (n == v) {
            cout << -d << endl;
            return;
        }

        if (visited[v] == 3) continue;

        visited[v]++;

        pq.push({d - len[v], dep[v]});
    }
}

int main() {
    solve();
    return 0;
}
