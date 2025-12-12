#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        if (x < 0) x = -x;
        if (y < 0) y = -y;
        string s;
        cin >> s;
        int diag = 0;
        for (int i = 0; i < n; ++i) if (s[i] == '8') ++diag;
        
        if (max(x, y) <= n && x + y <= n + diag) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
