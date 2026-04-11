#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    int ans = 0;
    sort(p.begin(), p.end());
    for (int i = 0; i < (n + 1) / 2; ++i) ans += p[i] / 2;
    for (int i = (n + 1) / 2; i < n; ++i) ans += p[i];
    cout << ans << endl;
}
