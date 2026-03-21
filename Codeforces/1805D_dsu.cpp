#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

void dfs(int node, int parent, vector<vector<int>> &adj, vector<int> &dist) {
    for (int next : adj[node]) {
        if (next == parent) continue;

        dist[next] = dist[node] + 1;
        dfs(next, node, adj, dist);
    }
}

int get_furthest(vector<int> &dist) {
    int idx = -1, max_dist = -1;
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] > max_dist) {
            idx = i;
            max_dist = dist[i];
        }
    }
    return idx;
}

map<int, vector<int>> dist_to_map(vector<int> &dist) {
    map<int, vector<int>> mp;
    for (int i = 0; i < dist.size(); ++i) {
        mp[dist[i]].push_back(i);
    }
    return mp;
}

struct DSU {
    DSU(int n) : n(n), comp_size(n, 1) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int node1, int node2) {
        int root1 = find(node1), root2 = find(node2);
        if (root1 != root2) {
            if (comp_size[root1] >= comp_size[root2]) {
                parent[root2] = root1;
                comp_size[root1] += comp_size[root2];
            } else {
                parent[root1] = root2;
                comp_size[root2] += comp_size[root1];
            }
        }
    }

    int size(int node) {
        return comp_size[find(node)];
    }

private:
    int n;
    std::vector<int> parent, comp_size;
};

void solve() {
    /*
    - problem:
        - we are given a tree
        - for each value of k in [1, n]: suppose we make a new graph where each node i is connected to all
        nodes j whose distance from i is at least k. count the number of connected components in this graph.
    - solution:
        - find a diameter of the tree, and get both of its endpoints. for both of those 2 endpoints, map each
        possible distance value to all nodes that are that distance value from the endpoint
        - then, for each value of k in descending order, connect both of those endpoints to all nodes which
        are k distance away from those endpoints, using DSU to keep track of existing components; the number
        of components decrements each time 2 disconnected components are joined together
    - details:
        - intuitions:
            - the brute-force solution is to go and build the graph for each k. this is O(n^3): O(n) for iterating
            through each k, and O(n^2) for going through all node pairs.
            - we need to speed this up.
            - let's suppose we have a simple tree with a chain structure. let k be fixed. what do we notice?
            for a given node i, it's connected to all nodes with distance >= k from it. all of those nodes
            form a component.
            - however, if we look at the leftmost node in the chain and keep k fixed, all nodes to the right
            of node i that node i was connected to (and MORE) will be connected to that leftmost node. flip
            it, and we get the same logic. in fact, if node i was connected to anything at ALL, then it will
            be connected to at least one of those 2 nodes. in other words, it'll be in one of those 2 connected
            components (which might actually just be the same).
            - so, for finding ALL connected components, we only need to check the connected components of the
            two ends of the chain. this can be generalized to trees: the two endpoints E and F of a diameter
            of the tree are such that for any node i, the farthest possible node from i will either be E or F.
            more accurately, for any node i, the set of farthest possible nodes from i will contain at least one
            of E and F.
            - even if we only check the two endpoints, though, this is still O(n^2). how do we speed this up?
            by using the same connected components information from previous values of k.
            - suppose we iterate through k in descending order. then, for each of the two ends of the diameter
            (let's call them E and F), the neighborhood of E, denoted N(E), will be a superset of what it was when
            k was 1 greater. same for F. so, when iterating through k, we just join the nodes that are that distance
            away from E or F.
            - how do we know that two nodes are not in the same component? DSU.
                - a simpler way: notice that once k drops to be sufficiently low, E and F will be in the same
                component. it is the first component to be formed, barring any other possible diameters (which
                will then be in the same component anyway). we can imagine all of the nodes are getting absorbed
                1 by 1 into that component. so, we can keep track of the not-yet-absorbed nodes in a "visited"
                set or array.
            - that's it.
        - by the way, if k <= the diameter, then both ends of the diameter path are connected
        - we can imagine that, on the chain, the set of nodes that are still not connected to E and F are the
        nodes in the middle, and as k decreases, this interval of nodes gets narrower and narrower. on a tree,
        it's the same idea: the only nodes that aren't connected for a fixed k are the nodes i such that
        min(dist(i, E), dist(i, F)) is sufficiently large.
    */

    // constructs tree
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // finds distances from arbitrary node (0)
    vector<int> dist(n, -1);
    dist[0] = 0;
    dfs(0, -1, adj, dist);

    // finds distances from first endpoint of diameter, and maps distances to node lists
    int end1 = get_furthest(dist);
    vector<int> dist1(n, -1);
    dist1[end1] = 0;
    dfs(end1, -1, adj, dist1);
    auto mp1 = dist_to_map(dist1);

    // finds distances from second endpoint of diameter, and maps distances to node lists
    int end2 = get_furthest(dist1);
    vector<int> dist2(n, -1);
    dist2[end2] = 0;
    dfs(end2, -1, adj, dist2);
    auto mp2 = dist_to_map(dist2);

    // iterates backward through each distance value, using DSU to join nodes at that distance value
    int comps = n;
    DSU dsu(n);
    vector<int> ans(n+1, 1);
    for (int i = n; i >= 1; --i) {
        // iterates through nodes at this distance from end1
        if (mp1.find(i) != mp1.end()) {
            for (auto node : mp1[i]) {
                if (dsu.find(end1) != dsu.find(node)) {
                    comps -= 1;
                    dsu.join(end1, node);
                }
            }
        }

        // iterates through nodes at this distance from end2
        if (mp2.find(i) != mp2.end()) {
            for (auto node : mp2[i]) {
                if (dsu.find(end2) != dsu.find(node)) {
                    comps -= 1;
                    dsu.join(end2, node);
                }
            }
        }

        // breaks if we can't get any fewer components
        ans[i] = comps;
        if (comps == 1) break;
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
