#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    int r = n/2, l = n % 2 ? r : r-1;
    for (int i = 0; i < (n+1)/2; ++i) {
        if (i == 0) {
            if (n % 2) cout << a[r] << " ";
            else cout << a[r] << " " << a[l] << " ";
        }
        else cout << a[r+i] << " " << a[l-i] << " ";
    }
}

int main() {
    solve();
    return 0;
}