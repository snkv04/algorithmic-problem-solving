#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to, theta;
    ll w;
};

struct Entry {
    int node;
    int theta_from;
    bool reached;
    ll distance;
};

struct Comp {
    bool operator()(const Entry &e1, const Entry &e2) const {
        return e1.distance > e2.distance;
    }
};

int main() {
    int n, d, a1, a2;
    cin >> n >> d >> a1 >> a2;
    --d;
    if (!d) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<Edge>> adj(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        while (m--) {
            Edge e;
            cin >> e.to >> e.w >> e.theta;
            e.theta %= 360; --e.to;
            adj[i].push_back(e);
        }
    }

    vector<vector<int>> adj2(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (auto [to, theta, w] : adj[i]) {
            adj2[to][i] = (theta + 180) % 360;
        }
    }

    vector<vector<vector<ll>>> dist(n, vector<vector<ll>>(360, vector<ll>(2, 1e18)));
    priority_queue<Entry, vector<Entry>, Comp> pq;
    for (int i = 0; i < 360; ++i) {
        pq.push(Entry{0, i, 0, 0});
        dist[0][i][0] = 0;
        // break;
    }
    while (pq.size()) {
        auto [node, theta_from, reached, distance] = pq.top();
        pq.pop();
        if (dist[node][theta_from][reached] < distance) continue;

        for (auto [next, theta_next, weight] : adj[node]) {
            // cout << "at node " << (node + 1) << " from " << theta_from << ", going to " << (next + 1) << " with " << theta_next << " and distance=" << distance << endl;
            int delta = (theta_next - theta_from + 360) % 360;
            // cout << "delta = " << delta << endl;
            bool can_turn;
            if (delta == 180) {
                can_turn = (a1 == 180) || (a2 == 180);
            } else if (delta < 180) {
                can_turn = delta <= a1;
            } else {
                can_turn = delta >= (360 - a2);
            }
            if (can_turn) {
                // cout << "could turn!" << endl;
                ll new_distance = distance + weight;
                bool new_reached = reached || (next == d);
                int new_theta = adj2[node][next];
                assert(new_theta != -1);
                if (new_distance < dist[next][new_theta][new_reached]) {
                    pq.push(Entry{next, new_theta, new_reached, new_distance});
                    dist[next][new_theta][new_reached] = new_distance;
                }
            }
        }
    }

    ll ans = 1e18;
    for (int i = 0; i < 360; ++i) ans = min(ans, dist[0][i][1]);
    cout << (ans == 1e18 ? "impossible" : to_string(ans)) << endl;

    return 0;
}
