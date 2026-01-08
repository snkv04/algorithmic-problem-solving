#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> true_num_paths(n, vector<int>(n, 0));
    for (int i = 0; i < n-1; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); ++j) {
            int k = i + j + 1;
            if (s[j] == '1') true_num_paths[i][k] = 1;
        }
    }

    vector<vector<int>> adj(n);
    for (int len = 1; len <= n-1; ++len) {
        for (int i = 0; i <= n-1-len; ++i) {
            int expected = 0;
            for (int next : adj[i]) {
                expected += true_num_paths[next][i+len];
            }

            if (expected % 2 != true_num_paths[i][i+len]) {
                adj[i].push_back(i+len);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) ans += adj[i].size();
    cout << ans << endl;
}
