struct DSU {
    int n;
    vector<int> parent;

    DSU(int n) {
        this->n = n;
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else {
            parent[node] = find(parent[node]);
            return parent[node];
        }
    }

    void unite(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            parent[d] = c;
        }
    }
};

class Solution {
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<vector<int>> adj(n, vector<int>());
        for (vector<int> &edge : edges) {
            int a = edge[0], b = edge[1];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        map<int, vector<int>> val_to_nodes;
        for (int i = 0; i < n; ++i) {
            val_to_nodes[vals[i]].push_back(i);
        }

        DSU dsu(n);
        unordered_set<int> activated;
        int ans = 0;
        for (auto &p : val_to_nodes) {
            int val = p.first;
            vector<int> nodes = p.second;

            for (int node : nodes) {
                activated.insert(node);
                for (int adjacent : adj[node]) {
                    if (activated.find(adjacent) != activated.end()) {
                        dsu.unite(node, adjacent);
                    }
                }
            }

            map<int, int> comp_to_cnt;
            for (int node : nodes) {
                comp_to_cnt[dsu.find(node)] += 1;
            }

            for (auto &p : comp_to_cnt) {
                int count = p.second;
                ans += (count * (count - 1)) / 2;
                ans += count;
            }
        }
        return ans;
    }
};
