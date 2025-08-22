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

struct PairHash {
    size_t operator()(const pair<int, int> &p) const {
        ll newx = p.first + bound, newy = p.second + bound;
        return (totalrange * newx) + newy;
    }
};

pair<int, int> operator+(const pair<int, int> &p1, const pair<int, int> &p2) {
    return make_pair(p1.first + p2.first, p1.second + p2.second);
}

pair<int, int> operator-(const pair<int, int> &p1, const pair<int, int> &p2) {
    return make_pair(p1.first - p2.first, p1.second - p2.second);
}

pair<int, int> convert(int dir, const pair<int, int> &p) {
    int dx = p.first, dy = p.second;
    if (dir == 0) {
        return make_pair(dx, dy);
    } else if (dir == 1) {
        return make_pair(-dy, dx);
    } else if (dir == 2) {
        return make_pair(-dx, -dy);
    } else {
        return make_pair(dy, -dx);
    }
}

int taxi(const pair<int, int> &p1, const pair<int, int> &p2) {
    int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
    return max(x2 - x1, x1 - x2) + max(y2 - y1, y1 - y2);
}

bool check_anchor(
    const pair<int, int> &anchor,
    int dir,
    unordered_set<pair<int, int>, PairHash> &sensed,
    unordered_set<pair<int, int>, PairHash> &forest,
    int rmax
) {
    // cout << "\nanchor: " << anchor << ", dir = " << dir << "\n";

    if (forest.find(anchor) != forest.end()) {
        return false;
    }

    // // gather all trees within distance
    // unordered_set<pair<int, int>, PairHash> inrange;
    // for (const pair<int, int> &tree : forest) {
    //     if (taxi(tree, anchor) <= rmax) {
    //         inrange.insert(tree);
    //     }
    // }

    // if (inrange.size() == sensed.size()) {
    //     bool works = true;
    //     for (const pair<int, int> &senseddirection : sensed) {
    //         pair<int, int> converted = convert(dir, senseddirection);
    //         pair<int, int> treeloc = anchor + converted;
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

    unordered_set<pair<int, int>, PairHash> found;
    for (const pair<int, int> &delta : sensed) {
        pair<int, int> converted = convert(dir, delta);
        pair<int, int> expected = converted + anchor;
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

    for (const pair<int, int> &tree : forest) {
        if (taxi(tree, anchor) <= rmax && found.find(tree) == found.end()) {
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

    unordered_set<pair<int, int>, PairHash> forest;
    unordered_set<pair<int, int>, PairHash> sensed(ns);
    for (int i = 0; i < nt + ns; ++i) {
        ll x, y;
        cin >> x >> y;
        pair<int, int> p = make_pair(x, y);
        if (i < nt) {
            forest.insert(p);
        } else {
            sensed.insert(p);
        }
    }
    // cout << "forest:\n";
    // for (const TreeLoc &t : forest) cout << t << "\n";
    // cout << "sensed:\n";
    // for (const TreeLoc &t : sensed) cout << t << "\n";

    bool possible = false;
    int ansx = -1, ansy = -1;
    for (const pair<int, int> &tree : forest) {
        for (int j = 0; j < 4; ++j) {
            pair<int, int> convertedfirst = convert(j, *sensed.begin());
            pair<int, int> anchor = tree - convertedfirst;
            // cout << "tree = " << tree << ", convertedfirst = " << convertedfirst << ", anchor = " << anchor << endl;

            if (check_anchor(anchor, j, sensed, forest, rmax)) {
                if (possible) {
                    cout << "Ambiguous\n";
                    return;
                } else {
                    // cout << "setting answer to " << anchor << '\n';
                    possible = true;
                    ansx = anchor.first;
                    ansy = anchor.second;
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
