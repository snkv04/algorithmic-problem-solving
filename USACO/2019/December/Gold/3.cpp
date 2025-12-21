#include <bits/stdc++.h>
using namespace std;
constexpr int INF = 1e9;

int main() {
    ifstream cin("cowmbat.in");
    ofstream cout("cowmbat.out");

    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    vector<vector<int>> cost(m, vector<int>(m, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> cost[i][j];
        }
    }

    vector<vector<int>> dist = cost;
    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                dist[i][j] = min(
                    dist[i][j],
                    dist[i][k] + dist[k][j]
                );
            }
        }
    }
    // for (int i = 0; i < m; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         cout << dist[i][j] << " ";
    //     }
    //     cout << std::endl;
    // }

    vector<vector<int>> pref(m, vector<int>(n, 0));
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            int last = i == 0 ? 0 : pref[j][i-1];
            pref[j][i] = last + dist[(int)(s[i]-'a')][j];
        }
    }

    vector<vector<int>> mem(m, vector<int>(n, INF));
    vector<int> best(n, INF);
    for (int j = 0; j < m; ++j) {
        mem[j][k-1] = pref[j][k-1];
        best[k-1] = min(best[k-1], mem[j][k-1]);
    }
    for (int i = k; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mem[j][i] = min(mem[j][i-1] + dist[(int)(s[i]-'a')][j], pref[j][i] - pref[j][i-k] + best[i-k]);
            best[i] = min(best[i], mem[j][i]);
        }
    }

    int ans = INF;
    for (int j = 0; j < m; ++j) ans = min(ans, mem[j][n-1]);
    cout << ans << endl;

    return 0;
}
