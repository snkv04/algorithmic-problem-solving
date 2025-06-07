#include <bits/stdc++.h>
using namespace std;

unordered_map<string, int> mp;
const int MAXP = 60;
int coords[MAXP][3];
unordered_set<int> adj[MAXP];

struct Comp {
    bool operator()(const pair<int, double> &p1, const pair<int, double> &p2) {
        return p1.second >= p2.second;
    }
};

double length(int a, int b) {
    double dx = coords[a][0] - coords[b][0], dy = coords[a][1] - coords[b][1], dz = coords[a][2] - coords[b][2];
    return sqrt(dx * dx + dy * dy + dz * dz);
}

void solve() {
    int p, w, q;
    cin >> p;
    for (int i = 0; i < p; ++i) {
        string s;
        int x, y, z;
        cin >> s >> x >> y >> z;
        mp[s] = i;
        coords[i][0] = x;
        coords[i][1] = y;
        coords[i][2] = z;
    }

    cin >> w;
    for (int i = 0; i < p; ++i) {
        adj[i].clear();
    }
    for (int i = 0; i < w; ++i) {
        string a, b;
        cin >> a >> b;
        adj[mp[a]].insert(mp[b]);
    }

    cin >> q;
    while (q--) {
        string a, b;
        cin >> a >> b;
        int start = mp[a], end = mp[b];
        double dist[p];
        fill(dist, dist+p, 1e18);
        dist[start] = 0;
        priority_queue<pair<int, double>, vector<pair<int, double>>, Comp> pq;
        pq.push(pair<int, double>(start, 0));
        while (pq.size()) {
            pair<int, double> pr = pq.top();
            // cout << "currently looking at node " << pr.first << "\n";
            // cout << "dist:\n";
            // for (int i = 0; i < p; ++i) {
            //     cout << dist[i] << " ";
            // }
            // cout << "\n";
            pq.pop();

            for (int i = 0; i < p; ++i) {
                if (i == pr.first) continue;

                double d = adj[pr.first].find(i) == adj[pr.first].end()
                    ? length(pr.first, i) : 0;
                if (dist[i] > dist[pr.first] + d) {
                    dist[i] = dist[pr.first] + d;
                    pq.push(pair<int, double>(i, dist[i]));
                }
            }
        }
        // cout << "currently looking at request " << a << " to " << b << "\n";
        // cout << "dist:\n";
        // for (int i = 0; i < p; ++i) {
        //     cout << dist[i] << " ";
        // }
        // cout << "\n";

        cout << "The distance from " << a << " to " << b << " is " << dist[end] << " parsecs.\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(0);

    int t = 1;
    cin >> t;
    int i = 1;
    while (t--) {
        cout << "Case " << i++ << ":\n";
        solve();
    }

    return 0;
}
