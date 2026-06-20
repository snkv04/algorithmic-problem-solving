#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> adj;
    vector<long long> baseTime;  // can store finish time in baseTime

    void dfs(int node) {
        long long l = -1e18, e = 1e18;
        for (int next : adj[node]) {
            dfs(next);
            l = max(l, baseTime[next]);
            e = min(e, baseTime[next]);
        }

        if (l != -1e18) {
            long long duration = l - e + baseTime[node];
            baseTime[node] = l + duration;
        }
    }

public:
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime) {
        adj.resize(n);
        for (int i = 0; i < n - 1; ++i) {
            int u = edges[i][0], v = edges[i][1];
            adj[u].push_back(v);
        }

        this->baseTime.resize(n);
        for (int i = 0; i < n; ++i) this->baseTime[i] = baseTime[i];
        dfs(0);
        return this->baseTime[0];
    }
};
