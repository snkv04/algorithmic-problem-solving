#include <bits/stdc++.h>

struct LCA {
    // assumes that adj is a tree
    LCA(const std::vector<std::vector<int>> &adj, int root) :
            n(adj.size()),
            MAX_POW(1 + std::ceil(std::log2(n))),
            root(root),
            adj(adj),
            depth(n, 0), 
            ancestor(MAX_POW + 1, std::vector<int>(n, -1)) {
        dfs(root, -1);
    }

    void dfs(int node, int parent) {
        ancestor[0][node] = parent;
        for (int i = 1; i <= MAX_POW; ++i) {
            int halfway = ancestor[i-1][node];
            if (halfway != -1) {
                ancestor[i][node] = ancestor[i-1][halfway];
            }
        }

        for (int next : adj[node]) {
            if (next == parent) continue;

            depth[next] = depth[node] + 1;
            dfs(next, node);
        }
    }

    int jump(int node, int height) {
        if (height > depth[node]) return -1;

        for (int i = 0; i <= MAX_POW; ++i) {
            if ((1 << i) & height) {
                node = ancestor[i][node];
            }
        }
        return node;
    }

    int lca(int a, int b) {
        if (depth[a] > depth[b]) std::swap(a, b);
        int diff = depth[b] - depth[a];
        b = jump(b, diff);
        if (a == b) return a;

        for (int i = MAX_POW; i >= 0; --i) {
            if (ancestor[i][a] != ancestor[i][b]) {
                a = ancestor[i][a];
                b = ancestor[i][b];
            }
        }
        return ancestor[0][a];
    }

private:
    int n, root;
    const int MAX_POW;
    const std::vector<std::vector<int>> &adj;
    std::vector<int> depth;
    std::vector<std::vector<int>> ancestor;
};
