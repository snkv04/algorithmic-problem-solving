#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    int n, k;
    cin >> n >> k;
    map<int, int> f;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        f[ai] += 1;
    }
    
    int missing = 0, moving = (f.find(k) == f.end() ? 0 : f[k]);
    for (int i = 0; i < k; ++i) {
        if (f.find(i) == f.end()) ++missing;
    }
    cout << max(missing, moving) << '\n';
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
