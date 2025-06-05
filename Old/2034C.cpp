#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000, MAXM = 1000;
char grid[MAXN][MAXM];
bool cycle[MAXN][MAXM];
bool visited[MAXN][MAXM];
unordered_map<char, pair<int, int>> mp;
int n, m;
int ans;

bool in_bounds(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

void propagate(int i, int j) {
    visited[i][j] = 1;
    cycle[i][j] = false;
    --ans;

    for (const pair<char, pair<int, int>> &p : mp) {
        int ni = i + -1 * p.second.first, nj = j + -1 * p.second.second;
        if (in_bounds(ni, nj) && grid[ni][nj] == p.first && !visited[ni][nj]) {
            propagate(ni, nj);
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = s[j];
        }
    }

    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        cycle[i][j] = 1;
        visited[i][j] = 0;
    }

    ans = n * m;
    for (int i = 1; i < n-1; ++i) {
        if (!visited[i][0] && grid[i][0] == 'L') {
            propagate(i, 0);
        }
        if (!visited[i][m-1] && grid[i][m-1] == 'R') {
            propagate(i, m-1);
        }
    }
    for (int j = 1; j < m-1; ++j) {
        if (!visited[0][j] && grid[0][j] == 'U') {
            propagate(0, j);
        }
        if (!visited[n-1][j] && grid[n-1][j] == 'D') {
            propagate(n-1, j);
        }
    }
    if (!visited[0][0] && (grid[0][0] == 'U' || grid[0][0] == 'L')) {
        propagate(0, 0);
    }
    if (!visited[0][m-1] && (grid[0][m-1] == 'U' || grid[0][m-1] == 'R')) {
        propagate(0, m-1);
    }
    if (!visited[n-1][0] && (grid[n-1][0] == 'D' || grid[0][0] == 'L')) {
        propagate(n-1, 0);
    }
    if (!visited[n-1][m-1] && (grid[n-1][m-1] == 'D' || grid[n-1][m-1] == 'R')) {
        propagate(n-1, m-1);
    }

    // cout << "grid:\n";
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         cout << cycle[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '?') {
                bool found = 0;
                for (const auto &p : mp) {
                    int ni = i + p.second.first, nj = j + p.second.second;
                    if (in_bounds(ni, nj) && cycle[ni][nj]) {
                        found = 1;
                        break;
                    }
                }
                ans -= 1 - found;
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    mp['U'] = pair<int, int>(-1, 0);
    mp['D'] = pair<int, int>(1, 0);
    mp['L'] = pair<int, int>(0, -1);
    mp['R'] = pair<int, int>(0, 1);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}