#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    int n, s;
    cin >> s >> n;
    vector<int> a(n+2);
    a[0] = 0;
    a[n+1] = s+1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> b;
    for (int i = 0; i <= n; ++i) {
        int diff = a[i+1] - a[i] - 1;
        b.push_back(diff);
    }
    if (a[1] != 1 && a[n] != s) {
        b[0] += b.back();
        b.pop_back();
    }

    int ans = 0;
    for (int diff : b) ans += (diff-1)/2;
    cout << ans << "\n";
}