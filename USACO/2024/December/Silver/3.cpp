#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<vector<char>> grid;
vector<vector<bool>> visited;
vector<tuple<int, int, char>> ops;
int curr;
map<pair<int, int>, char> dirs = {
    {{0, 1}, 'L'},
    {{0, -1}, 'R'},
    {{1, 0}, 'U'},
    {{-1, 0}, 'D'}
};

void dfs(int i, int j) {
    visited[i][j] = true;
    if (i > 0 && i < n+1 && j > 0 && j < n+1) ++curr;

    for (auto e : dirs) {
        int newi = i + e.first.first;
        int newj = j + e.first.second;
        if (newi >= 0 && newi <= n+1 && newj >= 0 && newj <= n+1 && !visited[newi][newj] && (grid[newi][newj] == '?' || grid[newi][newj] == e.second)) {
            dfs(newi, newj);
        }
    }
}

// void print_grid() {
//     for (int i = 0; i < n+2; ++i) {
//         for (int j = 0; j < n+2; ++j) {
//             //
//         }
//     }
// }

int main() {
    cin >> n >> q;
    grid = vector<vector<char>>(n+2, vector<char>(n+2, '?'));
    visited = vector<vector<bool>>(n+2, vector<bool>(n+2, false));
    for (int i = 0; i < q; ++i) {
        int r, c;
        char t;
        cin >> r >> c >> t;
        ops.push_back(tuple<int, int, char>({r, c, t}));
        grid[r][c] = t;
    }

    vector<int> ans(q, -1);
    curr = 0;

    // ans after all
    for (int i = 0; i < n+2; ++i) {
        for (int j = 0; j < n+2; ++j) {
            if (i > 0 && i < n+1 && j > 0 && j < n+1) {
                continue;
            }

            if (!visited[i][j]) {
                dfs(i, j);
            }
        }
    }
    ans[q-1] = curr;

    // ans after each op, going backward
    for (int i = q-1; i > 0; --i) {
        int r = std::get<0>(ops[i]), c = std::get<1>(ops[i]);
        grid[r][c] = '?';
        if (!visited[r][c]) for (auto e : dirs) {
            // if visited is true for a cell, then that means it can reach the outside
            if (visited[r + e.first.first][c + e.first.second]) {
                dfs(r, c);
                break;
            }
        }
        ans[i-1] = curr;
    }

    for (int i = 0; i < q; ++i) {
        cout << n * n - ans[i] << '\n';
    }
}
