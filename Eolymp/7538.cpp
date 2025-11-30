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

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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

struct DSU {
    int n;
    vector<int> parent, nodesize, edgesize;

    DSU(int n) : n(n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        nodesize = vector<int>(n, 1);
        edgesize = vector<int>(n, 0);
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            if (nodesize[c] >= nodesize[d]) {
                parent[d] = c;
                nodesize[c] += nodesize[d];
                edgesize[c] += edgesize[d] + 1;
            } else {
                parent[c] = d;
                nodesize[d] += nodesize[c];
                edgesize[d] += edgesize[c] + 1;
            }
        } else {
            edgesize[c] += 1;
        }
    }
};

void solve() {
    /*
    - at first glance, this is easily solveable with 2-SAT, since for any picture, any pair of cards sharing
    that picture can have an implication pair between each other. the variables are the cards; either we show
    the front or the back. however, that would require placing up to O(n^2) edges, which is probably too slow.
    - so, instead, we can find an alternate formulation of the problem. we can make each picture a node, with
    the cards being undirected edges between them. then, our goal is that for each edge, we want to select one
    of the vertices adjacent to it so that no vertex is selected more than once. through a little bit of
    experimentation, we can see that this condition is satisfiable if and only if each vertex is not part of
    more than one cycle. this can be easily computed with DSU, keeping track of the number of nodes and edges
    in each component.

    generalizable ideas for the future:
    - if one proposed solution doesn't work, then maybe it can be optimized, but there might also be another
    solution, and there might even be another formulation of the problem itself. it's hard to know which is the
    case a priori. the only thing left to do is to try out as many ideas as possible as quickly as possible.
    */

    int n;
    cin >> n;
    DSU dsu(2*n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        dsu.join(a - 1, b - 1);
    }

    for (int i = 0; i < 2*n; ++i) {
        int root = dsu.find(i);
        if (dsu.edgesize[root] > dsu.nodesize[root]) {
            cout << "impossible\n";
            return;
        }
    }
    cout << "possible\n";
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
