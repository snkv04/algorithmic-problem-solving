#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

struct State {
    int i, j, diri, dirj, count;

    // State(int i, int j, int diri, int dirj, int count) {
    //     this->i = i;
    //     this->j = j;
    //     this->diri = diri;
    //     this->dirj = dirj;
    //     this->count = count;
    // }
    State(int i, int j, int diri, int dirj, int count)
        : i(i), j(j), diri(diri), dirj(dirj), count(count) {}

    bool operator==(const State &other) const {
        return this->i == other.i
            && this->j == other.j
            && this->diri == other.diri
            && this->dirj == other.dirj
            && this->count == other.count;
    }
};

struct Cmp {
    bool operator()(const pair<State, int> &a, const pair<State, int> &b) const {
        int dista = a.second, distb = b.second;
        return dista > distb;
    }
};

// struct Eql {
//     bool operator()(const State &a, const State &b) const {
//         return a.i == b.i
//             && a.j == b.j
//             && a.diri == b.diri
//             && a.dirj == b.dirj
//             && a.count == b.count;
//     }
// };

struct Hash {
    int operator()(const State &s) const {
        vector<int> arr = {s.i, s.j, s.diri, s.dirj, s.count};
        int val = 0;
        for (int num : arr) {
            val ^= hash<int>{}(num) + 0x9e3779b9 + (val << 6) + (val >> 2);
        }
        return val;
    }
};

void solve() {
    /*
    what's the main idea of the solution? the grid can be modeled as a graph where each
    node contains the location in the grid, the direction from its previous square to
    here, and how many times it has went along that direction. then, we can effectively
    do a dijkstra's on this graph, calculating the distance between nodes based on whether
    or not they are moving in the same direction and how many times they have moved in
    that direction. effectively, the pseudocode of the solution is: construct grid, find
    where s and t are, set the distance of s to 0 (and the others are implicitly at infinity,
    but instead of using a table for the distances, just use a map), then run dijkstra's
    by treating each node as a tuple (or, in this case, std::array) of length 5 (or 6, if
    the distance is grouped together with it, as it is in the priority queue for dijkstra's),
    then find the minimum distance to t across all directions and counts of consecutively
    moving in those directions.

    what other things can be learned (even if i already know some of these things)?
    memorize the syntax of priority queue: template arguments are:
        element type
        underlying container type (a vector of element type)
        comparator class
    the comparator struct:
        only really needs one method, implementing the () operator (so that instances of
            the struct can be called directly)
        neither the arguments nor function body of operator() need to be const
    const usage:
        for function arguments, it makes sure that those don't change
        for the return type, it makes sure that the returned item doesn't change
        for the function body, it makes sure that member variables (of the class or struct
            that the function is defined in) don't change
    hash class:
        for unordered maps, the first and second template arguments are the types of the key and
            value, but the optional third and fourth are the hasher struct (which uses operator())
            and the KeyEqual struct (which i think is optional if giving the hash struct)
        for ordered maps, the optional third argument is just the comparator struct
        for operator(), the return type can either be int or size_t (which defaults to long long
            on my computer but i think can vary across machines), the argument must be const, and
            the function body must be const
        if hashing an array, one way to make sure that the order of the elements matters is to
            go through each element, making the new hash after that element rely both on the element
            and the previous hash value before incorporating that element
    */

    int n, m;
    cin >> n >> m;
    string asdf;
    getline(cin, asdf);
    string grid[n];
    for (int i = 0; i < n; ++i) {
        getline(cin, grid[i]);
    }

    pair<int, int> s, t;
    unordered_map<State, int, Hash> dist;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') {
                s = make_pair(i, j);
                dist[State(i, j, 0, 0, 0)] = 0;
            } else {
                if (grid[i][j] == 'T') {
                    t = make_pair(i, j);
                }
            }
        }
    }

    priority_queue<pair<State, int>, vector<pair<State, int>>, Cmp> pq;
    pq.push(make_pair(State(s.first, s.second, 0, 0, 0), 0));
    while (pq.size()) {
        pair<State, int> node = pq.top();
        // cout << "visiting: " << node << "\n";
        pq.pop();
        State state = node.first;
        int i = state.i, j = state.j, diri = state.diri, dirj = state.dirj, count=state.count, distance=node.second;
        if (distance > dist[State(i, j, diri, dirj, count)]) continue; // visited node earlier with better distance

        for (int k = 0; k < 4; ++k) {
            int newi = i + di[k], newj = j + dj[k];
            // cout << "newi = " << newi << ", newj = " << newj << "\n";
            if (grid[newi][newj] == '#') continue;

            if (di[k] == diri && dj[k] == dirj) {
                int newdist = distance, newcount;
                if (count == 3) {
                    newdist += 3;
                    newcount = 2;
                } else {
                    newdist += 1;
                    newcount = count + 1;
                }

                State newnode(newi, newj, di[k], dj[k], newcount);
                if (dist.find(newnode) == dist.end() || dist[newnode] > newdist) {
                    dist[newnode] = newdist;
                    pq.push(make_pair(newnode, newdist));
                }
            } else {
                State newnode(newi, newj, di[k], dj[k], 1);
                if (dist.find(newnode) == dist.end() || dist[newnode] > distance + 1) {
                    dist[newnode] = distance + 1;
                    pq.push(make_pair(newnode, distance + 1));
                }
            }
        }
    }
    
    int distance = 1e9;
    for (int k = 0; k < 4; ++k) {
        for (int count = 1; count <= 3; ++count) {
            State node(t.first, t.second, di[k], dj[k], count);
            if (dist.find(node) != dist.end()) {
                distance = min(distance, dist[node]);
            }
        }
    }
    cout << (distance == 1e9 ? -1 : distance) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
