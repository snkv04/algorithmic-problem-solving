#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dirs = {
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0}
};
int r, c;

bool in_bounds(int i, int j) {
    return i >= 0 && i < r && j >= 0 && j < c;
}

void solve() {
    cin >> r >> c;
    int istart, jstart, iend, jend;
    cin >> istart >> jstart >> iend >> jend;
    --istart; --jstart; --iend; --jend;

    vector<string> grid(r);
    for (int i = 0; i < r; ++i) cin >> grid[i];

    int i = istart, j = jstart, dir = 0;
    vector<vector<vector<bool>>> vis(r, vector<vector<bool>>(c, vector<bool>(4, false)));
    while (!(i == iend && j == jend) && !vis[i][j][dir]) {
        vis[i][j][dir] = true;
        // cout << "i = " << i << ", j = " << j << ", dir = " << dir << endl;

        // check turn left
        int nextdir = (dir + 1) % 4;
        int newi = i + dirs[nextdir][0], newj = j + dirs[nextdir][1];
        if (in_bounds(newi, newj) && grid[newi][newj] == '0') {
            i = newi;
            j = newj;
            dir = nextdir;
            continue;
        }

        // check forward
        newi = i + dirs[dir][0]; newj = j + dirs[dir][1];
        if (in_bounds(newi, newj) && grid[newi][newj] == '0') {
            i = newi;
            j = newj;
            continue;
        }

        // turn right
        dir = (dir + 3) % 4;
    }

    if (i == iend && j == jend) {
        cout << "1\n";
    } else {
        cout << "0\n";
    }
}

int main() {
    solve();

    return 0;
}