#include <iostream>
#include <queue>
#include <stack>

using namespace std;

using ll = long long;

int MOD = 998244353;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> adj[n];
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int dist[n];
    bool visited[n];
    fill(dist, dist+n, 0);
    fill(visited, visited+n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                if (!visited[node]) {
                    visited[node] = true;
                    for (int next : adj[node]) {
                        if (!visited[next]) {
                            dist[next] = dist[node] + 1;
                            q.push(next);
                        } else {
                            if (dist[next] % 2 == dist[node] % 2) {
                                cout << 0 << '\n';
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    // for (int i =0 ;i < n; ++i) {
    //     cout << "dist[" << i << "] = " << dist[i] << '\n';
    // }

    fill(visited, visited+n, false);
    ll ans = 1;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int odd = 0, even = 0;
            stack<int> s;
            s.push(i);
            while (!s.empty()) {
                int node = s.top();
                s.pop();
                if (!visited[node]) {
                    if (dist[node] % 2 == 0) {
                        // cout << "even, dist[" << node << "] = " << dist[node] << '\n';
                        ++even;
                    } else {
                        // cout << "odd, dist[" << node << "] = " << dist[node] << '\n';
                        ++odd;
                    }
                    visited[node] = true;

                    for (int next : adj[node]) {
                        if (!visited[next]) {
                            s.push(next);
                        }
                    }
                }
            }
            if (odd + even > 1) {
                ll comp = 0;
                // cout << "odd = " << odd << ", even = " << even << '\n';
                if (odd) {
                    ll adding = 1;
                    while (odd--) { adding *= 2; adding %= MOD; }
                    // cout << "adding from odd = " << adding << '\n';
                    comp += adding; comp %= MOD;
                }
                if (even) {
                    ll adding = 1;
                    while (even--) { adding *= 2; adding %= MOD; }
                    // cout << "adding from even = " << adding << '\n';
                    comp += adding; comp %= MOD;
                }
                ans *= comp;
            } else {
                ans *= 3;
            }
            ans %= MOD;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}