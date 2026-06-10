#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    int n;
    cin >> n;
    vector<string> grid(2);
    cin >> grid[0] >> grid[1];
    
    bool valid = true;
    for (int i = 0; i < n; ++i) {
        if (grid[0][i] == '1' && grid[1][i] == '1') {
            valid = false;
            break;
        }
    }
    cout << (valid ? "YES" : "NO") << endl;
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
