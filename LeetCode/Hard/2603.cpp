class Solution {
private:
    void print_graph(vector<unordered_set<int>> &adj, int n) {
        cout << "graph:\n";
        for (int i = 0; i < n; ++i) {
            cout << "adj[" << i << "] = [";
            for (const int &j : adj[i]) {
                cout << j << " ";
            }
            cout << "]\n";
        }
    }

public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        // build the adjacency lists
        int num_nodes = edges.size() + 1;
        vector<unordered_set<int>> adj(num_nodes, unordered_set<int>());
        for (const vector<int> &edge : edges) {
            int a = edge[0], b = edge[1];
            adj[a].insert(b);
            adj[b].insert(a);
        }
        // print_graph(adj, num_nodes);

        // we know that non-coin leaves don't ever have to be traversed,
        // so remove them from the tree completely
        for (int i = 0; i < num_nodes; ++i) {
            if (adj[i].size() == 1 && coins[i] == 0) {
                int node = i;
                while (adj[node].size() == 1 && coins[node] == 0) {
                    int next = *adj[node].begin();
                    adj[node].erase(next);
                    adj[next].erase(node);
                    node = next;
                }
            }
        }
        // print_graph(adj, num_nodes);

        unordered_set<int> still_in, leaves;
        for (int i = 0; i < num_nodes; ++i) {
            if (adj[i].size()) still_in.insert(i);
            if (adj[i].size() == 1) leaves.insert(i);
        }

        // remove layers of leaves twice. why? we don't ever need to go
        // less than distance 2 from a leaf.
        bool no_more_nodes = false;
        for (int round = 1; round <= 2 && !no_more_nodes; ++round) {
            unordered_set<int> next_leaves;
            for (const int &leaf : leaves) {
                if (adj[leaf].size() == 1) {
                    int next = *adj[leaf].begin();
                    adj[leaf].erase(next);
                    adj[next].erase(leaf);
                    if (adj[next].size() == 1) {
                        next_leaves.insert(next);
                    }
                    still_in.erase(leaf);
                } else {
                    no_more_nodes = true;
                    break;
                }
            }
            leaves = next_leaves;
            // cout << "round " << round << ":\n";
            // print_graph(adj, num_nodes);
        }

        // finally, we know that we'll need to get to every node in
        // this tree, because by removing the layers, we already assumed
        // that there are coins beyond every leaf in the remaining tree,
        // so we traverse all edges
        return max(0, (int) (still_in.size() - 1) * 2);
    }
};
