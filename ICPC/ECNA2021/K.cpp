#include <bits/stdc++.h>
using namespace std;

void solve() {
    int h, w;
    cin >> h >> w;
    vector<vector<int>> grid(h, vector<int>(w, 0));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> grid[i][j];
            --grid[i][j];
        }
    }

    vector<unordered_set<int>> adj(h*w+1);
    for (int i = 0; i < h-1; ++i) {
        for (int j = 0; j < w; ++j) {
            if (grid[i+1][j] != grid[i][j]) {
                adj[grid[i][j]].insert(grid[i+1][j]);
            }
        }
    }
    for (int j = 0; j < w; ++j) {
        adj[grid[h-1][j]].insert(h*w);
    }
    // for (int i = 0; i <= h*w; ++i) {
    //     cout << "adj["<<i<<"] = [";
    //     for (int num : adj[i]) cout << num << " ";
    //     cout << "]\n";
    // }

    int a = grid[0][0], b = -1;
    for (int j = 0; j < w; ++j) {
        if (grid[0][j] != a) {
            b = grid[0][j];
            break;
        }
    }
    int g = h*w;
    // cout << "a = " << a << ", b = " << b << ", g = " << g << "\n";
    
    vector<int> reachA(h*w+1, -1); 
    queue<pair<int, int>> q;
    q.push({0, a});
    unordered_set<int> visited;
    while (q.size()) {
        pair<int, int> p = q.front();
        q.pop();
        int d = p.first;
        int v = p.second;

        if (visited.find(v) != visited.end()) {
            continue;
        }

        visited.insert(v);
        reachA[v] = d;

        for (auto &a : adj[v]) {
            q.push({d + 1, a});
        }
    }

    /*for (int i = 0; i < reachA.size(); i++) {
        cout << reachA[i] << " ";
    }
    cout << endl;*/
    if (b == -1) {
        cout << reachA[h * w] << endl;
        return;
    }
    
    vector<int> reachB(h*w+1, -1); 
    q.push({0, b});
    visited = {};
    while (q.size()) {
        pair<int, int> p = q.front();
        q.pop();
        int d = p.first;
        int v = p.second;

        if (visited.find(v) != visited.end()) {
            continue;
        }

        visited.insert(v);
        reachB[v] = d;

        for (auto &a : adj[v]) {
            q.push({d + 1, a});
        }
    }

    /*for (int i = 0; i < reachB.size(); i++) {
        cout << reachB[i] << " ";
    }
    cout << endl;*/

    priority_queue<pair<int, int>> pq;
    visited = {};
    for (int i = 0; i < h*w+1; i++) {
        if (reachA[i] >= 0 && reachB[i] >= 0) {
            pq.push({-(reachA[i]+reachB[i]), i});
            //cout << reachA[i]+reachB[i] << " " << i << endl;
        }
    }

    /*for (auto &a : pq) {
        cout << (*a).first << " " << (*a).second << endl;
    }*/
    //cout << "start" << endl;
    while (pq.size()) {
        pair<int, int> p = pq.top();
        pq.pop();
        
        int d = p.first;
        int v = p.second;
        //cout << d << " " << v << endl;
        if (g == v) {
            cout << -d << endl;
            return;
        }

        if (visited.find(v) != visited.end()) {
            continue;
        }

        visited.insert(v);

        for (auto &a : adj[v]) {
            pq.push({d - 1, a});
        }
    }
    cout << "did not reach end uh oh" << endl;
}

int main() {
    solve();
    return 0;
}
