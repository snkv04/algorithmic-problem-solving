#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void apply(vector<string> &grid, int endi, int endj) {
    for (int i = 0; i <= endi; ++i) {
        for (int j = 0; j <= endj; ++j) {
            grid[i][j] = (((grid[i][j] - '0') + 1) % 2) + '0';
        }
    }
}

void solve() {
    ifstream fin("cowtip.in");
    ofstream fout("cowtip.out");

    int n;
    fin >> n;
    vector<string> grid(n, string());
    for (int i = 0; i < n; ++i) fin >> grid[i];

    int ans = 0;
    for (int i = n-1; i >= 0; --i) {
        for (int j = n-1; j >= 0; --j) {
            if (grid[i][j] == '1') {
                ++ans;
                apply(grid, i, j);
            }
        }
    }
    fout << ans << "\n";
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
