#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> rotate(vector<vector<int>> grid) {
    int r = grid.size(), c = grid[0].size();
    vector<vector<int>> newgrid(c, vector<int>(r, 0));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            newgrid[j][r-1-i] = grid[i][j];
        }
    }
    // cout << "newgrid:\n";
    // for (int i = 0; i < c; ++i) {
    //     for (int j = 0; j < r; ++j) {
    //         cout << newgrid[i][j] << " ";

    //     }
    //     cout << "\n";
    // }
    return newgrid;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    vector<int> statues;
    for (int i = 0; i < n; ++i ) {
        for (int j =0 ; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] != -1) {
                statues.push_back(grid[i][j]);
            }
        }
    }
    sort(statues.begin(), statues.end());
    // cout << "statues\n";
    // for (int i = 0; i < statues.size(); ++i) {
    //     cout << statues[i] << " ";
    // }
    // cout << "\n";

    int ans = 1e9;
    for (int corner = 0; corner < 4; ++corner) {
        vector<map<int, int>> per_diag;
        int k = 0;
        for (int diag = 1; diag <= m + n - 1; ++diag) {
            int i = min(diag - 1, (int) grid.size() - 1);
            int j = diag - i - 1;
            map<int, int> thisdiag;
            while (i >= 0 && j <= grid[0].size()-1) {
                if (grid[i][j] > 0) {
                    thisdiag[statues[k++]] += 1;
                }
                // cout << "("<<i<<", "<<j<<")\n";

                --i;
                ++j;
            }
            per_diag.push_back(thisdiag);
            // cout << "diag = " << diag << ", statues:";
            // for (auto p : thisdiag) cout << "("<<p.first<<", "<<p.second<<") ";
            // cout << "\n";
        }
        // cout << "\n";

        int count = 0;
        for (int diag = 1; diag <= m + n - 1; ++diag) {
            int i = min(diag - 1, (int)grid.size() - 1);
            int j = diag - i - 1;
            while (i >= 0 && j <= grid[0].size()-1) {
                if (grid[i][j] > 0) {
                    int statue = grid[i][j];
                    if (per_diag[diag-1].find(statue) == per_diag[diag-1].end()) {
                        count += 1;
                    } else {
                        per_diag[diag-1][statue] -= 1;
                        if (per_diag[diag-1][statue] == 0) {
                            per_diag[diag-1].erase(statue);
                        }
                    }
                }

                --i;
                ++j;
            }
        }
        ans = min(ans, count);

        grid = rotate(grid);
    }
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}