#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    map<int, int> m;
    for (int i = 0; i < n; ++i)
    {
        int temp;
        cin >> temp;
        ++m[temp];
    }
    int s = m.size();
    if (s < k)
    {
        cout << s;
    }
    else
    {
        cout << k;
    }
}

int main() {
    solve();

    return 0;
}