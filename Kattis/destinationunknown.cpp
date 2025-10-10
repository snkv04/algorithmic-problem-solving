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

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

struct Comp {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

void solve() {
    int n, m, t, s, g, h;
    cin >> n >> m >> t >> s >> g >> h;
    --s; --g; --h;

    vector<pair<int, int>> adj[n];
    for (int i = 0; i < n; ++i) adj[i] = vector<pair<int, int>>();
    for (int i = 0; i < m; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        --a; --b;
        adj[a].push_back(make_pair(b, d));
        adj[b].push_back(make_pair(a, d));
    }

    set<int> dests;
    while (t--) {
        int x;
        cin >> x;
        dests.insert(--x);
    }

    vector<int> dist(n, 1e9);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;
    pq.push(make_pair(s, 0));
    vector<bool> marked(n, false);
    while (pq.size()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int node = p.first, distance = p.second;
        if (distance > dist[node]) continue;  // outdated pair in the prioqueue

        for (pair<int, int> next : adj[node]) {
            int next_node = next.first, weight = next.second;
            bool crossing = (node == g && next_node == h) || (node == h && next_node == g);
            
            if (dist[next_node] > distance + weight) {
                dist[next_node] = distance + weight;
                pq.push(make_pair(next_node, dist[next_node]));

                if (crossing) marked[next_node] = true;
                else {
                    if (marked[node]) marked[next_node] = true;
                    else marked[next_node] = false;
                }
            } else if (dist[next_node] == distance + weight) {
                if (crossing || marked[node]) {
                    pq.push(make_pair(next_node, dist[next_node]));
                    marked[next_node] = true;
                }
            }
        }
    }
    // cout << "marked = ";
    // for (bool val : marked) cout << val << " ";
    // cout << "\n";

    for (int node : dests) {
        if (marked[node]) cout << (node + 1) << " ";
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
