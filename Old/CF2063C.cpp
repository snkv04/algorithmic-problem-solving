#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;

    vector<int> adj[n];
    int maxdeg = 0;
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        maxdeg = max(maxdeg, (int) max(adj[a].size(), adj[b].size()));
    }

    unordered_set<int> seen;
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (adj[i].size() == maxdeg) {
            if (seen.empty()) {
                seen.insert(i);
            } else {
                bool works = true;
                for (int neighbor : adj[i]) {
                    if (seen.find(neighbor) != seen.end()) {
                        works = false;
                        break;
                    }
                }

                if (works) {
                    cout << 2 * maxdeg - 1 << '\n';
                    return;
                } else {
                    seen.insert(i);
                }
            }
            last = i;
        }
    }

    // removes the last seen vertex with degree = maxdeg
    for (int neighbor : adj[last]) {
        adj[neighbor].erase(std::remove(adj[neighbor].begin(), adj[neighbor].end(), last));
    }
    adj[last].clear();

    // finds next highest degree
    int second = 0;
    for (int i = 0; i < n; ++i) second = max(second, (int) adj[i].size());
    cout << maxdeg + second - 1 << '\n';
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
