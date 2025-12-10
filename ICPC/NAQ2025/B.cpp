#include <bits/stdc++.h>
using namespace std;

int r, c, n;
vector<vector<int>> t1, d1, t2, d2;
vector<int> di = {0, 0, 1, -1},
            dj = {1, -1, 0, 0};

bool in_bounds(int i, int j) {
    return i >= 0 && i < r && j >= 0 && j < c;
}

void solve() {
    cin >> r >> c >> n;
    t1 = vector<vector<int>>(r, vector<int>(c, 1e9));
    d1 = vector<vector<int>>(r, vector<int>(c, 1e9));
    t2 = vector<vector<int>>(r, vector<int>(c, 1e9));
    d2 = vector<vector<int>>(r, vector<int>(c, 1e9));

    queue<array<int, 4>> q;
    for (int idx = 1; idx <= n; ++idx) {
        int i, j;
        cin >> i >> j;
        --i; --j;
        q.push(array<int, 4>({i, j, idx, 0}));
    }

    while (q.size()) {
        array<int, 4> a = q.front();
        q.pop();
        int i = a[0], j = a[1], idx = a[2], dist = a[3];
        if (dist < d1[i][j] || (dist == d1[i][j] && idx < t1[i][j])) {
            // cout << "setting (" << i << ", " << j << ")'s first to " << idx << endl;
            d1[i][j] = dist;
            t1[i][j] = idx;
            for (int k = 0; k < 4; ++k) {
                int newi = i + di[k], newj = j + dj[k];
                if (in_bounds(newi, newj)) {
                    q.push(array<int, 4>({newi, newj, idx, dist + 1}));
                }
            }
        } else {
            if (t1[i][j] != idx && (dist < d2[i][j] || (dist == d2[i][j] && idx < t2[i][j]))) {
                // cout << "setting (" << i << ", " << j << ")'s second to " << idx << endl;
                // cout << d1[i][j] << "\n";
                d2[i][j] = dist;
                t2[i][j] = idx;
                for (int k = 0; k < 4; ++k) {
                    int newi = i + di[k], newj = j + dj[k];
                    if (in_bounds(newi, newj)) {
                        q.push(array<int, 4>({newi, newj, idx, dist + 1}));
                    }
                }
            } else {
                // do nothing
            }
        }
    }

    for (int i = 0; i < 2 * r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (i < r) {
                cout << t1[i][j] << " ";
            } else {
                cout << t2[i % r][j] << " ";
            }
        }
        cout << "\n";
    }
}

int main() {
    solve();

    return 0;
}