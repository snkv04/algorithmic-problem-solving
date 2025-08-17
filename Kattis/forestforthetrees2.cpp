#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
stringstream ss;
ll bound = 1e5;
ll totalrange = 2 * bound + 1;

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

struct TreeLoc {
    ll x;
    ll y;

    TreeLoc() : x(0), y(0) {}

    TreeLoc(ll x, ll y): x(x), y(y) {}

    TreeLoc operator+(const TreeLoc &other) const {
        return TreeLoc(this->x + other.x, this->y + other.y);
    }

    TreeLoc operator-(const TreeLoc &other) const {
        return TreeLoc(this->x - other.x, this->y - other.y);
    }
};

std::ostream& operator<<(std::ostream &os, const TreeLoc &t) {
    os << "(" << t.x << ", " << t.y << ")";
    return os;
}

struct TreeHash {
    size_t operator()(const TreeLoc &t) const {
        ll newx = t.x + bound, newy = t.y + bound;
        return (totalrange * newx) + newy;
    }
};

struct TreeEqual {
    bool operator()(const TreeLoc &t1, const TreeLoc &t2) const {
        return t1.x == t2.x && t1.y == t2.y;
    }
};

TreeLoc convert(int dir, const TreeLoc &t) {
    ll dx = t.x, dy = t.y;
    if (dir == 0) {
        return TreeLoc(dx, dy);
    } else if (dir == 1) {
        return TreeLoc(-dy, dx);
    } else if (dir == 2) {
        return TreeLoc(-dx, -dy);
    } else {
        return TreeLoc(dy, -dx);
    }
}

ll taxi(const TreeLoc &t1, const TreeLoc &t2) {
    return max(t2.x - t1.x, t1.x - t2.x) + max(t2.y - t1.y, t1.y - t2.y);
}

// ll toid(pair<ll, ll> &p) {
//     ll newx = p.first + bound, newy = p.second + bound;
//     return (totalrange * newx) + newy;
// }

// pair<ll, ll> fromid(ll id) {
//     ll newx = id / totalrange, newy = id % totalrange;
//     return make_pair(newx - bound, newy - bound);
// }

bool check_anchor(
    const TreeLoc &anchor,
    int dir,
    unordered_set<TreeLoc, TreeHash, TreeEqual> &sensed,
    unordered_set<TreeLoc, TreeHash, TreeEqual> &forest,
    int rmax
) {
    // cout << "\nanchor: " << anchor << ", dir = " << dir << "\n";

    if (forest.find(anchor) != forest.end()) {
        return false;
    }

    // // gather all trees within distance
    // unordered_set<TreeLoc, TreeHash, TreeEqual> inrange;
    // for (const TreeLoc &tree : forest) {
    //     if (taxi(tree, anchor) <= rmax) {
    //         inrange.insert(tree);
    //     }
    // }

    // if (inrange.size() == sensed.size()) {
    //     bool works = true;
    //     for (const TreeLoc &senseddirection : sensed) {
    //         TreeLoc converted = convert(dir, senseddirection);
    //         TreeLoc treeloc = anchor + converted;
    //         if (inrange.find(treeloc) != inrange.end()) {
    //             inrange.erase(treeloc);
    //         } else {
    //             return false;
    //         }
    //     }
    //     return true;
    // } else {
    //     return false;
    // }

    unordered_set<TreeLoc, TreeHash, TreeEqual> found;
    for (const TreeLoc &delta : sensed) {
        TreeLoc converted = convert(dir, delta);
        TreeLoc expected = converted + anchor;
        // cout << "checking if expected " << expected << " is a tree\n";
        if (forest.find(expected) != forest.end()) {
            // cout << "is\n";
            found.insert(expected);
        } else {
            // cout << "isn't\n";
            return false;
        }
    }

    if (found.size() != sensed.size()) {
        // shouldn't even happen, but just checking anyway
        // cout << "huh?\n";
        return false;
    }

    for (const TreeLoc &tree2 : forest) {
        if (taxi(tree2, anchor) <= rmax && found.find(tree2) == found.end()) {
            // cout << "found tree " << tree2 << " that wasn't already sensed, returning false\n";
            return false;
        }
    }
    // cout << "returning true\n";
    return true;
}

void solve() {
    int nt, ns, rmax;
    cin >> nt >> ns >> rmax;
    if (ns > nt) {
        cout << "Impossible\n";
        return;
    }

    unordered_set<TreeLoc, TreeHash, TreeEqual> forest;
    unordered_set<TreeLoc, TreeHash, TreeEqual> sensed(ns);
    for (int i = 0; i < nt + ns; ++i) {
        ll x, y;
        cin >> x >> y;
        TreeLoc t(x, y);
        if (i < nt) {
            forest.insert(t);
        } else {
            sensed.insert(t);
        }
    }
    // cout << "forest:\n";
    // for (const TreeLoc &t : forest) cout << t << "\n";
    // cout << "sensed:\n";
    // for (const TreeLoc &t : sensed) cout << t << "\n";

    bool possible = false;
    int ansx = -1, ansy = -1;
    for (const TreeLoc &tree : forest) {
        for (int j = 0; j < 4; ++j) {
            TreeLoc convertedfirst = convert(j, *sensed.begin());
            TreeLoc anchor = tree - convertedfirst;
            // cout << "tree = " << tree << ", convertedfirst = " << convertedfirst << ", anchor = " << anchor << endl;

            if (check_anchor(anchor, j, sensed, forest, rmax)) {
                if (possible) {
                    cout << "Ambiguous\n";
                    return;
                } else {
                    // cout << "setting answer to " << anchor << '\n';
                    possible = true;
                    ansx = anchor.x;
                    ansy = anchor.y;
                }
            }
            // cout << "right now, ansx = " << ansx << ", ansy = " << ansy << "\n";
        }
    }
    // cout << "forest:\n";
    // for (const TreeLoc &t : forest) cout << t << "\n";
    // cout << "sensed:\n";
    // for (const TreeLoc &t : sensed) cout << t << "\n";

    if (!possible) {
        cout << "Impossible\n";
    } else {
        // cout << "FINAL\n";
        cout << ansx << " " << ansy << "\n";
    }
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
