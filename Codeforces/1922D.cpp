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

void solve() {
    /*
    main ideas:
    - this can obviously be simulated with brute-force, but O(n^2) is too slow. so, the core idea
    is that we only have to simulate the monsters whose neighbors have recently died. (in the first
    round, we check all monsters). why? because if we already know from a previous round that a monster
    doesn't die, then it won't die this round if its neighbors haven't changed. in other words,
    only a select few nodes in the doubly-linked list have to be checked on each round. we also just have
    to keep track of which nodes have already died, in order to avoid re-simulating them (adding them to
    the set of nodes whose neighbors have changed) after they've already been fully processed. not doing
    this will only cause bugs when multiple consecutive monsters die within a round, because otherwise,
    each monster will only be linked to monsters that are already guaranteed alive after the most recent
    round.
    */

    int n;
    cin >> n;
    vector<ll> a(n+2, 0), d(n+2, 1e18);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }

    vector<int> prev(n+2, -1), next(n+2, -1);
    for (int i = 0; i <= n; ++i) {
        next[i] = i+1;
    }
    for (int i = 1; i <= n+1; ++i) {
        prev[i] = i-1;
    }

    unordered_set<int> changed_neighbors; for (int i = 1; i <= n; ++i) changed_neighbors.insert(i);
    vector<int> ans;
    vector<bool> has_died(n+2, false);
    while (changed_neighbors.size()) {
        unordered_map<int, ll> dmg;
        for (int i : changed_neighbors) {
            dmg[i] = a[prev[i]] + a[next[i]];
        }

        unordered_set<int> new_changed;
        int num_died = 0;
        for (int i : changed_neighbors) {
            // cout << "i = " << i << "\n";
            if (dmg[i] > d[i]) {
                ++num_died;
                has_died[i] = true;
                new_changed.insert(prev[i]);
                new_changed.insert(next[i]);
                prev[next[i]] = prev[i];
                next[prev[i]] = next[i];
            }
        }
        // print_container(has_died, "has_died = ");
        // print_container(new_changed, "new_changed = ");
        // print_container(prev, "prev = ");
        // print_container(next, "next = ");

        changed_neighbors = new_changed;
        changed_neighbors.erase(0); changed_neighbors.erase(n+1);
        for (int i : new_changed) {
            // don't need to keep track of already dead monsters; prev and next links should jump over
            // them when these links are being updated
            if (has_died[i]) changed_neighbors.erase(i);
        }
        ans.push_back(num_died);
    }

    while (ans.size() < n) ans.push_back(0);
    for (int num : ans) cout << num << " ";
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
