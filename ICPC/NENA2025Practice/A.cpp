#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll w, s;
    cin >> w >> s;
    ll expected = 29260 * s * (s+1) / 2;
    ll diff = w - expected;
    cout << diff / 110 << endl;
}

int main() {
    solve();
    return 0;
}