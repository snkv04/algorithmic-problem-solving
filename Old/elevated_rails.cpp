#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int rep[MAXN];
int depth[MAXN];
int farthest_in_tree[MAXN];

int dfs(int node, int parent) {
    int max_child_depth = 0;
    for (int next : adj[node]) {
        if (next == parent) continue;
        max_child_depth = max(max_child_depth, dfs(next, node));
    }
    depth[node] = max_child_depth + 1;
    return depth[node];
}

void dfs2(int node, int parent) {
    multiset<int> child_depths;
    int max_child_depth = 0;
    for (int next : adj[node]) {
        child_depths.insert(depth[next]);
        max_child_depth = max(max_child_depth, depth[next]);
    }

    int old_node_depth = max_child_depth + 1;
    farthest_in_tree[node] = old_node_depth;
    for (int child : adj[node]) {
        if (child == parent) continue;
        int old_child_depth = depth[child];
        child_depths.erase(child_depths.find(old_child_depth));
        int new_node_depth = child_depths.empty() ? 1 : *child_depths.rbegin() + 1;
        depth[node] = new_node_depth;

        dfs2(child, node);

        child_depths.insert(old_child_depth);
    }
    depth[node] = old_node_depth;
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n-3; ++i) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    bool visited[n];
    fill(visited, visited + n, false);
    bool visited2[n];
    fill(visited2, visited2 + n, false);
    unordered_map<int, int> diameters;
    vector<int> representatives;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            representatives.push_back(i);

            queue<int> queue;
            queue.push(i);
            vector<int> searched;
            int dists[n];
            fill(dists, dists+n, 0);
            while (!queue.empty()) {
                int node = queue.front();
                queue.pop();
                rep[node] = i;
                visited[node] = true;
                searched.push_back(node);
                for (int &next : adj[node]) {
                    if (!visited[next]) {
                        dists[next] = dists[node] + 1;
                        queue.push(next);
                    }
                }
            }

            int farthestFromI = i;
            for (int found : searched) {
                if (dists[found] > dists[farthestFromI]) {
                    farthestFromI = found;
                }
            }

            assert(queue.empty());
            queue.push(farthestFromI);
            // fill(&dists[0], &dists[n], 0);
            fill(dists, dists+n, 0);
            int diameter = 0;
            while (!queue.empty()) {
                int node = queue.front();
                queue.pop();
                visited2[node] = true;
                diameter = max(diameter, dists[node] + 1);
                for (int next : adj[node]) {
                    if (!visited2[next]) {
                        dists[next] = dists[node] + 1;
                        queue.push(next);
                    }
                }
            }
            diameters[i] = diameter;
        }
    }
    
    for (int r : representatives) {
        dfs(r, -1);
    }

    for (int r : representatives) {
        dfs2(r, -1);
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int ans = farthest_in_tree[a] + farthest_in_tree[b];
        for (int r : representatives) {
            if (r != rep[a] && r != rep[b]) {
                ans += diameters[r];
                break;
            }
        }
        cout << to_string(ans) + '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }
}
