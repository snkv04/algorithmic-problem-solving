#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

vector<string> isects;
vector<vector<int>> cnt;
vector<string> grid;
vector<vector<int>> adj;
vector<bool> vis, onstack;
int n;

bool checkdl(int i, int j, int s) {
    int ni = i+s-1, nj = j;
    while (nj < j+s) {
        if (grid[ni][nj] != '/') return false;
        ni--;
        nj++;
    }
    return true;
}

bool checkdr(int i, int j, int s) {
    int ni = i, nj = j;
    while (nj < j+s) {
        if (grid[ni][nj] != '\\') return false;
        ++ni;
        ++nj;
    }
    return true;
}

int idx(int i, int j, string d) {
    if (d == "tl") return i*(n+1)+j;
    else if (d == "tr") return i*(n+1) + j+1;
    else if (d == "bl") return (i+1)*(n+1)+j;
    else return (i+1)*(n+1)+j+1;
}

bool cycle(int node, int parent) {
    vis[node] = true;
    onstack[node] = true;

    for (int next : adj[node]) {
        if (next == parent) continue;

        if (onstack[next]) return true;

        if (!vis[next]) {
            if (cycle(next, node)) {
                return true;
            }
        }
    }
    onstack[node] = false;
    return false;
}

bool checkloops() {
    int numnodes = (n+1)*(n+1);
    adj.clear();
    adj.resize(numnodes);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '/') {
                adj[idx(i, j, "bl")].push_back(idx(i, j, "tr"));
                adj[idx(i, j, "tr")].push_back(idx(i, j, "bl"));
            } else {
                adj[idx(i, j, "tl")].push_back(idx(i, j, "br"));
                adj[idx(i, j, "br")].push_back(idx(i, j, "tl"));
            }
        }
    }

    // cout << "grid is:\n";
    // for (int i = 0; i < n; ++i) cout << grid[i] << endl;
    
    vis = vector<bool>(numnodes, false);
    onstack = vector<bool>(numnodes, false);
    for (int i = 0; i < numnodes; ++i) {
        if (!vis[i]) {
            if (cycle(i, -1)) {
                // cout << "found cycle\n";
                return false;
            }
        }
    }
    return true;
}

bool dfs(int i, int j) {
    pair<int, int> tl = {i, j}, tr = {i, j+1}, bl = {i+1, j}, br = {i+1, j+1};
    vector<pair<int, int>> done = {tl};
    if (j == n-1) done.push_back(tr);
    if (i == n-1) done.push_back(bl);
    if (i == n-1 && j == n-1) done.push_back(br);

    map<char, vector<pair<int, int>>> choices = {
        {'/', {bl, tr}},
        {'\\', {tl, br}}
    };
    for (auto choice : choices) {
        char slash = choice.first;
        auto points = choice.second;
        grid[i][j] = slash;
        for (auto [r, c] : points) {
            ++cnt[r][c];
        }

        // check that intersections are satisfied
        bool passesisects = true;
        for (auto [r, c] : done) {
            if (isects[r][c] != '+' && isects[r][c] - '0' != cnt[r][c]) {
                passesisects = false;
                break;
            }
        }
        bool passesloops = checkloops();

        if (passesisects && passesloops) {
            int nexti, nextj;
            if (j == n-1) {
                nexti = i+1;
                nextj = 0;
            } else {
                nexti = i;
                nextj = j+1;
            }

            if (nexti == n) {
                return true;
            } else {
                if (dfs(nexti, nextj)) {
                    return true;
                } else {
                    // undo selection
                    grid[i][j] = ' ';
                    for (auto [r, c] : points) {
                        --cnt[r][c];
                    }
                }
            }
        } else {
            // undo selection
            grid[i][j] = ' ';
            for (auto [r, c] : points) {
                --cnt[r][c];
            }
        }
    }
    return false;
}

int main() {
    cin >> n;
    isects.resize(n+1);
    for (int i = 0; i <= n; ++i) cin >> isects[i];

    cnt = vector<vector<int>>(n+1, vector<int>(n+1, 0));
    grid = vector<string>(n, string(n, 'o'));
    bool result = dfs(0, 0);
    // cout << "result = " << result << endl;
    for (int i = 0; i < n; ++i) cout << grid[i] << endl;
}