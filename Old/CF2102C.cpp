#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

// this function is incorrectly implemented
ll summex(vector<vector<int>> &grid) {
    int n = grid.size();
    ll sum = 0;
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            for (int t = 0; t < n; ++t) {
                for (int b = t; b < n; ++b) {
                    int mex = 0;
                    for (int i = l; i <= r; ++i) {
                        for (int j = t; j <= b; ++j) {
                            if (grid[i][j] == mex) ++mex;
                        }
                    }
                    sum += mex;
                }
            }
        }
    }
    return sum;
}

void solve() {
    int n;
    cin >> n;
    queue<pair<int, int>> q;
    q.push(make_pair(n/2, n/2));
    int counter = 0;
    vector<vector<int>> grid(n, vector<int>(n, 0));
    // bool visited[n][n];
    // for (int i = 0; i < n; ++i) fill(visited[i], visited[i]+n, false);
    // while (q.size()) {
    //     pair<int, int> p = q.front();
    //     q.pop();
    //     int i = p.first, j = p.second;
    //     if (visited[i][j]) continue;
    //     grid[p.first][p.second] = counter++;
    //     visited[i][j] = true;

    //     for (int k = 0; k < 4; ++k) {
    //         int newi = i + di[k], newj = j + dj[k];
    //         if (newi >= 0 && newi < n && newj >= 0 && newj < n && grid[newi][newj] == 0) {
    //             q.push(make_pair(newi, newj));
    //         }
    //     }
    // }

    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    int l = (n-1)/2, r = n/2, t = l, b = r;
    if (n % 2) {
        grid[t][l] = counter++;
    } else {
        grid[t][l] = counter++;
        grid[t][r] = counter++;
        grid[b][l] = counter++;
        grid[b][r] = counter++;
    }
    while (counter < n * n) {
        for (int i = t; i <= b; ++i) {
            grid[i][r+1] = counter++;
        }
        for (int j = l; j <= r+1; ++j) {
            grid[t-1][j] = counter++;
        }
        for (int j = l; j <= r+1; ++j) {
            grid[b+1][j] = counter++;
        }
        for (int i = t-1; i <= b+1; ++i) {
            grid[i][l-1] = counter++;
        }

        --l;
        ++r;
        --t;
        ++b;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    // if (n == 3) {
    //     grid[0][0] = 8;
    //     grid[0][1] = 4;
    //     grid[0][2] = 5;
    //     grid[1][0] = 6;
    //     grid[1][1] = 0;
    //     grid[1][2] = 1;
    //     grid[2][0] = 7;
    //     grid[2][1] = 2;
    //     grid[2][2] = 3;
    // }
    // cout << "sum = " << summex(grid) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
