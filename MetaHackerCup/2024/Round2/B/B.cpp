#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int NUMSTATES = 823543;
vector<string> grid(6);
vector<vector<int>> adj;
vector<vector<pair<int, int>>> lines = {
    {
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 3}
    },
    {
        {0, 0},
        {1, 1},
        {2, 2},
        {3, 3}
    },
    {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0}
    },
    {
        {0, 0},
        {1, -1},
        {2, -2},
        {3, -3}
    },
};

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

struct RollingHash {
private:
    vector<ll> P = {998244353, 999999937};
    vector<ll> MOD = {1000000007, 1000000009};
    vector<vector<ll>> PPOW;
    vector<vector<ll>> rolling;
    string s;
    int n;

    void _build_hashes() {
        rolling = vector<vector<ll>>(n + 1, vector<ll>(2, 0));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = s[i - 1];
                rolling[i][t] = (rolling[i - 1][t] * P[t] + letter_as_int) % MOD[t];
            }
        }
    }

    void _build_powers() {
        PPOW = vector<vector<ll>>(n + 1, vector<ll>(2, 1));
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                PPOW[i][t] = (PPOW[i - 1][t] * P[t]) % MOD[t];
            }
        }
    }

public:
    RollingHash(string &s) : s(s), n(s.size()) {
        _build_hashes();
        _build_powers();
    }

    // l and r are both 0-based indices, where l is inclusive and r is exclusive
    pair<ll, ll> get_hash(int l, int r) {
        vector<ll> result(2);
        for (int t = 0; t < 2; ++t) {
            result[t] = (rolling[r][t] - (rolling[l][t] * PPOW[r - l][t] % MOD[t]) + MOD[t]) % MOD[t];
        }
        return make_pair(result[0], result[1]);
    }
};

int toidx(array<int, 7> &state) {
    int idx = 0;
    for (int i = 0; i < 7; ++i) {
        idx = 7 * idx + state[i];
    }
    return idx;
}

array<int, 7> fromidx(int idx) {
    array<int, 7> state;
    for (int i = 6; i >= 0; --i) {
        state[i] = idx % 7;
        idx /= 7;
    }
    return state;
}

void dfs(array<int, 7> &state, bool connie, vector<bool> &visited) {
    int oldidx = toidx(state);
    if (visited[oldidx]) return;

    visited[oldidx] = true;
    // print_container(state, "state = ");
    for (int j = 0; j < 7; ++j) {
        if (state[j] < 6 && grid[state[j]][j] == (connie ? 'C' : 'F')) {
            state[j] += 1;
            int newidx = toidx(state);
            adj[oldidx].push_back(newidx);
            adj[newidx].push_back(oldidx);
            dfs(state, !connie, visited);
            state[j] -= 1;
        }
    }
}

void builddists(int start, vector<int> &dist) {
    dist[start] = 0;
    queue<int> que;
    que.push(start);
    while (que.size()) {
        int node = que.front();
        que.pop();

        for (int next : adj[node]) {
            if (dist[next] > dist[node] + 1) {
                dist[next] = dist[node] + 1;
                que.push(next);
            }
        }
    }
}

set<char> get_winners(array<int, 7> state) {
    set<char> winners;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int d = 0; d < 4; ++d) {
                vector<pair<int, int>> cells = lines[d];
                for (int c = 0; c < 4; ++c) {
                    cells[c].first += i;
                    cells[c].second += j;
                }

                char player = ' ';
                for (int c = 0; c < 4; ++c) {
                    // check bounds
                    if (cells[c].second >= 0 && cells[c].second < 7 && cells[c].first >= 0 && cells[c].first < state[cells[c].second]) {
                        if (player == ' ') {
                            player = grid[cells[c].first][cells[c].second];
                        } else if (player != ' ' && player != grid[cells[c].first][cells[c].second]) {
                            player = '.';
                            break;
                        }
                    } else {
                        player = '.';
                        break;
                    }
                }
                if (player != '.') {
                    winners.insert(player);
                }
            }
        }
    }
    return winners;
}

void dfs2(int idx, set<char> &all_winners, vector<bool> &validstate) {
    stack<int> stk;
    vector<bool> visited(NUMSTATES, false);
    stk.push(idx);
    while (stk.size()) {
        int node = stk.top();
        stk.pop();
        if (visited[node]) continue;

        visited[node] = true;
        array<int, 7> state = fromidx(node);
        set<char> winners = get_winners(state);
        if (winners.size()) {
            if (winners.size() > 1) {
                std::exit(1);
            }

            // should only have 1 element
            all_winners.insert(*winners.begin());
            continue;
        } else {
            for (int nextidx : adj[node]) {
                if (!visited[nextidx] && validstate[nextidx]) {
                    stk.push(nextidx);
                }
            }
        }
    }
    // cout << visited[386561] << "\n";
    // cout << validstate[386561] << "\n";    
}

void solve() {
    /*
    generalizable ideas for the future:
    - in contests like there, where they don't select the compilation options and instead we
    run our code, use optimization flags. the runtime on the sample cases went from 19s (with no
    flags) to 2s (with the O2 flag).
    - if a game has discrete states, then we can represent a simulation of the game as a path through
    a directed graph where the states are nodes. in my previous attempt, i was considering each state
    as entirely disjoint from everything else (as if it's always possible to get to). so, in cases
    where it's possible to have C win but to get there with proper move orders we need to see F win
    first (in other words, where a state meeting a condition cannot be reached without having a
    another state reached first as a prerequisite), then my solution was wrong. if we want to represent
    a game where the rules of the game impose some constraints on the reachability of each state, then
    a graph could be a good idea.
    - if we are in a state where there are multiple winners, then because of the fact that one player
    places a piece at a time, there must have been a prior state with exactly one winner. it's kind of
    like the intermediate value theorem; to have gotten to a state with one winner is a prerequisite.
    therefore, if we want to find the first winner across all game paths, we only need to go up to the
    states with exactly 1 winner.
    */

    for (int i = 0; i < 6; ++i) {
        cin >> grid[5-i]; // read in rows so that (0, 0) is bottom left
    }

    set<char> winnersatend = get_winners(array<int, 7>({6, 6, 6, 6, 6, 6, 6}));
    if (winnersatend.empty()) {
        cout << "0" << endl;
        return;
    }

    // construct graph
    adj = vector<vector<int>>(NUMSTATES);
    array<int, 7> state({0, 0, 0, 0, 0, 0, 0});
    vector<bool> visited(NUMSTATES, false);
    dfs(state, true, visited);

    // find all states that are reachable from both start and end
    vector<int> diststart(NUMSTATES, 1e9), distend(NUMSTATES, 1e9);
    builddists(0, diststart);
    builddists(NUMSTATES-1, distend);
    vector<bool> validstate(NUMSTATES, false);
    int cnt = 0;
    for (int i = 0; i < NUMSTATES; ++i) {
        if (diststart[i] + distend[i] == 42) {
            validstate[i] = true;
            ++cnt;
        }
    }
    // cout << cnt << " valid states\n";

    // // slow way is checking all game states
    // set<char> winners;
    // for (int i = 0; i < NUMSTATES; ++i) {
    //     if (!validstate[i]) continue;

    //     // cout << "checking " << i << "\n";
    //     set<char> state_winners = get_winners(fromidx(i));
    //     if (state_winners.size() == 1) {
    //         winners.insert(*state_winners.begin());
    //     }
    // }

    // faster way is to DFS and prune out any states that come after a single win
    set<char> all_winners;
    dfs2(0, all_winners, validstate);

    if (all_winners.size() == 2) {
        cout << "?" << endl;
    } else {
        cout << *all_winners.begin() << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
