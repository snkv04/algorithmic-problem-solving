#include <bits/stdc++.h>
using namespace std;

class Solution {
    void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &top) {
        visited[node] = true;
        for (int next : adj[node]) {
            if (!visited[next]) {
                dfs(next, adj, visited, top);
            }
        }
        top.push_back(node);
    }

    vector<int> get_top_sort(vector<vector<int>> &adj) {
        vector<int> top;
        vector<bool> visited(adj.size(), false);
        for (int i = 0; i < adj.size(); ++i) {
            if (!visited[i]) {
                dfs(i, adj, visited, top);
            }
        }
        reverse(top.begin(), top.end());
        return top;
    }

    bool check_no_cycles(vector<vector<int>> &adj) {
        vector<int> top = get_top_sort(adj);
        vector<int> pos(adj.size());
        for (int i = 0; i < top.size(); ++i) {
            pos[top[i]] = i;
        }
        for (int i = 0; i < adj.size(); ++i) {
            for (int j : adj[i]) {
                if (pos[j] < pos[i]) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // check if groups are topologically sortable
        vector<vector<int>> adj(m);
        for (int i = 0; i < n; ++i) {
            if (group[i] == -1) {
                group[i] = m++;
                adj.push_back({});
            }
            for (int prev : beforeItems[i]) {
                if (group[prev] == -1) {
                    group[prev] = m++;
                    adj.push_back({});
                }
                adj[group[prev]].push_back(group[i]);
            }
        }
        if (!check_no_cycles(adj)) {
            return vector<int>();
        }

        // if so, check that all items are topologically sortable
        vector<vector<int>> adj2(n);
        for (int i = 0; i < n; ++i) {
            for (int prev : beforeItems[i]) {
                adj2[prev].push_back(i);
            }
        }
        if (!check_no_cycles(adj2)) {
            return vector<int>();
        }

        // if they are, then:
        //     iterate through groups in topological order
        //     as soon as we encounter a group, push all of its items onto the answer
        vector<int> top_sort = get_top_sort(adj2);
        map<int, queue<int>> group_to_items;
        for (int item : top_sort) {
            group_to_items[group[item]].push(item);
        }

        vector<int> group_top_sort = get_top_sort(adj);
        vector<int> answer;
        for (int group : group_top_sort) {
            while (group_to_items[group].size()) {
                answer.push_back(group_to_items[group].front());
                group_to_items[group].pop();
            }
        }
        return answer;
    }
};
