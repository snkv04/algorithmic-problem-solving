class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        map<int, vector<pair<int, int>>> edges;
        for (auto m : meetings) {
            edges[m[2]].push_back(make_pair(m[0], m[1]));
        }

        vector<bool> knows(n, false);
        knows[0] = knows[firstPerson] = true;
        vector<vector<int>> adj(n);
        for (auto e : edges) {
            int time = e.first;
            set<int> starting;
            for (auto p : e.second) {
                // place edge
                adj[p.first].push_back(p.second);
                adj[p.second].push_back(p.first);
                if (knows[p.first]) starting.insert(p.first);
                if (knows[p.second]) starting.insert(p.second);
            }

            // propagate
            queue<int> q; for (int source : starting) q.push(source);
            set<int> visited;
            while (q.size()) {
                int node = q.front();
                q.pop();
                visited.insert(node);
                knows[node] = true;

                for (int next : adj[node]) {
                    if (visited.find(next) == visited.end()) {
                        q.push(next);
                    }
                }
            }

            for (auto p : e.second) {
                // remove edges
                adj[p.first].clear();
                adj[p.second].clear();
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; ++i) if (knows[i]) ans.push_back(i);
        return ans;
    }
};
