#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> delta = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

int to1d(pair<int, int> pos, int r, int c) {
    return pos.first * c + pos.second;
}

pair<int, int> from1d(int &idx, int r, int c) {
    return make_pair(idx / c, idx % c);
}

bool inbounds(pair<int, int> &pos, int r, int c) {
    return pos.first >= 0 && pos.first < r && pos.second >= 0 && pos.second < c;
}

void solve() {
    /*
    - uses 0/1 BFS idea from https://codeforces.com/blog/entry/22276
    - basically, since all edge weights are 0 or 1, we can replace dijkstra's (which
    needs the prioqueue to have the nodes sorted by distance) with a BFS (which uses
    a deque in order to ensure that at all times, the deque can be split into 2 parts,
    the left and the right, where the left has nodes with distance D and the right has
    nodes with distance D+1). in short, since the insert operations on the queue only
    requires placing a new node on the front or back and not the middle to remain sorted,
    we use a deque instead of a prioqueue. why do we only have to place on front or back?
    if the distances in the queue are {D, D+1}, then the current node's distance will be D
    (since we pull from the front, as always), so then the next node's distance will either
    be D or D+1, which we can deal with by placing it at the front or back.
    - we are just leveraging the fact that the edge weights are either 0 or 1 instead
    of arbitrary
    */

    int r, c;
    cin >> r >> c;
    vector<string> map(r); for (int i = 0; i < r; ++i) cin >> map[i];

    vector<int> dist(r*c, 1e9);
    dist[0] = 0;
    deque<pair<int, int>> d; // holds (cell idx, cell dist)
    d.push_back(make_pair(0, 0));
    while (d.size()) {
        auto p = d.front();
        d.pop_front();
        int idx = p.first, distance = p.second;
        if (distance > dist[idx]) continue;

        auto pos = from1d(idx, r, c);
        for (int k = 0; k < 4; ++k) {
            auto newpos = pos + delta[k];
            if (inbounds(newpos, r, c)) {
                int newidx = to1d(newpos, r, c);
                int weight = map[pos.first][pos.second] != map[newpos.first][newpos.second];
                if (distance + weight < dist[newidx]) {
                    dist[newidx] = distance + weight;
                    if (weight) {
                        d.push_back(make_pair(newidx, dist[newidx]));
                    } else {
                        d.push_front(make_pair(newidx, dist[newidx]));
                    }
                }
            }
        }
    }
    cout << dist[to1d(make_pair(r-1, c-1), r, c)] << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
