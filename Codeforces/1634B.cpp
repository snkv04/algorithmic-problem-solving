#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    int change = 0;
    for (int i = 0; i < n; ++i) change ^= a[i] & 1;
    cout << (((x & 1) ^ (y & 1) == change) ? "Alice" : "Bob") << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
