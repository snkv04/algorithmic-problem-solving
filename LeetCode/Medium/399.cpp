class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // turn each string to a number
        unordered_map<string, int> to_num;
        int counter = 0;
        for (const vector<string> &equation : equations) {
            for (string s : equation) {
                if (to_num.find(s) == to_num.end()) {
                    to_num[s] = counter++;
                }
            }
        }

        // create the graph
        vector<vector<pair<int, double>>> adj(counter);
        for (int i = 0; i < equations.size(); ++i) {
            adj[to_num[equations[i][0]]].push_back(make_pair(
                to_num[equations[i][1]], values[i]
            ));
            adj[to_num[equations[i][1]]].push_back(make_pair(
                to_num[equations[i][0]], 1.0 / values[i]
            ));
        }

        // iterate through each query
        vector<double> result(queries.size());
        for (int q = 0; q < queries.size(); ++q) {
            // check that both numerator and denominator are valid variables
            string num = queries[q][0], denom = queries[q][1];
            if (
                to_num.find(num) == to_num.end() ||
                to_num.find(denom) == to_num.end()
            ) {
                result[q] = -1.0;
                continue;
            }

            // perform bfs, keeping track of each node as well as the
            // accumulated value (from the start node) at that node
            int n = to_num[num], d = to_num[denom];
            queue<pair<int, double>> que;
            que.push(make_pair(n, 1.0));
            double ans = -1.0;
            vector<bool> visited(counter, false);
            while (que.size()) {
                pair<int, double> front = que.front();
                que.pop();
                int node = front.first; double node_val = front.second;
                visited[node] = true;
                if (node == d) {
                    ans = node_val;
                    break;
                }

                for (pair<int, double> next : adj[node]) {
                    if (!visited[next.first]) {
                        que.push(make_pair(
                            next.first,
                            node_val * next.second
                        ));
                    }
                }
            }

            if (!visited[d]) {
                result[q] = -1.0;
            } else {
                result[q] = ans;
            }
        }
        return result;
    }
};
