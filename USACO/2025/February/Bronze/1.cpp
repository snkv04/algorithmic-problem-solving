#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, u;
    cin >> n >> u;
    vector<string> grid(n); for (int i = 0; i < n; ++i) cin >> grid[i];
    vector<vector<int>> counts(n/2, vector<int>(n/2, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool hash = grid[i][j] == '#';
            int r = i < n/2 ? i : n-1-i;
            int c = j < n/2 ? j : n-1-j;
            counts[r][c] += hash;
        }
    }

    int total = 0;
    for (int i = 0; i < n/2; ++i) {
        for (int j = 0; j < n/2; ++j) {
            total += min(counts[i][j], 4 - counts[i][j]);
        }
    }
    cout << total << "\n";

    while (u--) {
        int i, j;
        cin >> i >> j;
        --i; --j;
        int r = i < n/2 ? i : n-1-i;
        int c = j < n/2 ? j : n-1-j;
        total -= min(counts[r][c], 4 - counts[r][c]);
        if (grid[i][j] == '.') {
            grid[i][j] = '#';
            counts[r][c] += 1;
        } else {
            grid[i][j] = '.';
            counts[r][c] -= 1;
        }
        total += min(counts[r][c], 4 - counts[r][c]);
        cout << total << "\n";
    }
}

int main() {
    solve();

    return 0;
}