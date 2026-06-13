#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct Comparator {
    bool operator()(const array<int, 3> &a, const array<int, 3> &b) {
        return a[1] > b[1];
    }
};

void solve() {
    int n, m, t, s, g, h;
    cin >> n >> m >> t >> s >> g >> h;
    --s; --g; --h;

    vector<vector<pair<int, int>>> adj(n);
    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        adj[a].push_back(make_pair(b, w));
        adj[b].push_back(make_pair(a, w));
    }

    vector<int> destinations;
    while (t--) {
        int node;
        cin >> node;
        --node;
        destinations.push_back(node);
    }
    sort(destinations.begin(), destinations.end());

    vector<int> dist(n, 1e9);
    dist[s] = 0;
    priority_queue<array<int, 3>, vector<array<int, 3>>, Comparator> pq;
    pq.push({s, 0, 0});
    vector<bool> marked(n, false);
    while (pq.size()) {
        auto [node, d, has_mark] = pq.top();
        pq.pop();
        if (d > dist[node]) continue;
        assert(d == dist[node]);

        for (auto [next_node, weight] : adj[node]) {
            bool will_mark = has_mark || ((node == g && next_node == h) || (node == h && next_node == g));

            if (dist[next_node] > d + weight) {
                marked[next_node] = will_mark;
                dist[next_node] = d + weight;
                pq.push({next_node, dist[next_node], marked[next_node]});
            } else if (dist[next_node] == d + weight) {
                marked[next_node] = marked[next_node] || will_mark;
                pq.push({next_node, dist[next_node], marked[next_node]});
            }
        }
    }

    for (int dest : destinations) {
        if (marked[dest]) {
            cout << dest + 1 << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
