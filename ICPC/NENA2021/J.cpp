#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    /*
    generalizable ideas for the future:
    - if multiple cells have the same value and same column, they can all be grouped together. same for
    the row. then, to distinguish them, the distance to a cell is the minimum distance between the distance
    for (that cell's row, combined with its value) and for (that cell's column, combined with its value). in
    short, we take each cell and recognize that it can be placed into two different groups (i.e., canonical
    forms): its row + its value, and its col + its value. then, we ONLY get the distance for those canonical
    forms, and the distance for a given cell is just the better of its two canonical forms.
    - only look at the "next" rows/columns that we need to. don't need to look at all. this can be precomputed.
    it's hard to reason about the time complexity for improvements like this, but it definitely cuts down
    runtime by pruning out unnecessary operations.
    */

    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, int>>> pos(k+1);
    vector<unordered_set<int>> rowexist(k+1), colexist(k+1);
    vector<vector<int>> grid(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            pos[grid[i][j]].push_back(make_pair(i, j));
            rowexist[grid[i][j]].insert(i);
            colexist[grid[i][j]].insert(j);
        }
    }
    for (int i = 1; i <= k; ++i) {
        if (pos[i].empty()) {
            cout << "-1\n";
            return;
        }
    }

    vector<vector<ll>> rowval(n, vector<ll>(k+1, 1e18)), colval(n, vector<ll>(k+1, 1e18));
    for (int i = 0; i < n; ++i) {
        rowval[i][1] = 0;
        colval[i][1] = 0;
    }

    for (int i = 1; i < k; ++i) {
        for (auto p : pos[i]) {
            int thisrow = p.first, thiscol = p.second;
            ll currdist = min(rowval[thisrow][i], colval[thiscol][i]);
            for (int row : rowexist[i+1]) {
                ll dist = (thisrow - row) * (thisrow - row);
                rowval[row][i+1] = min(rowval[row][i+1], currdist + dist);
            }
            for (int col : colexist[i+1]) {
                ll dist = (thiscol - col) * (thiscol - col);
                colval[col][i+1] = min(colval[col][i+1], currdist + dist);
            }
        }
    }

    ll ans = 1e18;
    for (auto p : pos[k]) {
        int i = p.first, j = p.second;
        ans = min(ans, min(rowval[i][k], colval[j][k]));
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}
