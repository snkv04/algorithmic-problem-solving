class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        /*
        - we want to find distances between nodes in terms of ROUTES, not edges
        - one way to do this is to have edges between all node pairs that share
        a route, so then we can just find the shortest path; however, this
        is too slow, because there can be 1e5 nodes in 1 route
        - instead, we can make the routes themselves into special nodes, remove
        all edges between normal nodes, and only have edges between normal
        nodes and special (route) nodes
            - the intuition is that moving from one node to another by
            traversing the path of a route is replaced by moving from the
            first node to the route's central/special node and then to the
            second
        - 3 ways of doing this:
            - have each edge have weight 1, then do a BFS and divide the final
            distance by 2; assuming N = (n + routes.size()) and
            M = (2 * sum(routes[i].size())), runtime is O(N + M)
            - have edges from normal nodes to special nodes have weight 0
            and edges from special nodes to normal nodes have weight 1, then
            simply run Dijkstra's because the shortest paths are accurate;
            runtime is O(M + N log N)
            - have edges from normal nodes to special nodes have weight 0
            and edges from special nodes to normal nodes have weight 1, then
            run an 0/1 BFS; runtime is O(N + M)
        */

        // constructs the graph
        int n = 1e6, num_routes = routes.size();
        vector<vector<int>> adj(n + num_routes);
        for (int i = 0; i < routes.size(); ++i) {
            int route_idx = n + i;
            for (int bus : routes[i]) {
                adj[bus].push_back(route_idx);
                adj[route_idx].push_back(bus);
            }
        }

        // finds shortest path
        vector<int> dist(n + num_routes, 1e9);
        dist[source] = 0;
        queue<pair<int, int>> q;
        q.push(make_pair(source, 0));
        while (q.size()) {
            // processes the node
            auto [node, distance] = q.front();
            q.pop();
            if (distance > dist[node]) continue;

            // processes adjacent nodes
            for (int next : adj[node]) {
                if (distance + 1 < dist[next]) {
                    dist[next] = distance + 1;
                    q.push(make_pair(next, dist[next]));
                }
            }
        }
        return dist[target] == 1e9 ? -1 : (dist[target] / 2);
    }
};
