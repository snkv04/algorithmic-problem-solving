#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int mn, mx;
    cin >> mn; mx = mn;
    int ans = 0;
    for (int i = 0; i < n-1; ++i) {
        int ai;
        cin >> ai;
        if (ai < mn || ai > mx) ++ans;
        mn = min(mn, ai);
        mx = max(mx, ai);
    }
    cout << ans << endl;
}
