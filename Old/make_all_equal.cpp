#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    int n;
    cin >> n;
    map<int, int> mp;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        ++mp[ai];
        mx = max(mx, mp[ai]);
    }
    cout << n - mx << "\n";
}
 
int main() {
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
