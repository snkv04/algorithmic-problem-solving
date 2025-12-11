#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    set<int> indices;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') indices.insert(i+1);
    }
    
    cout << indices.size() << "\n";
    for (int idx : indices) cout << idx << " ";
    cout << "\n";
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
