#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int ans = m;
        int ct = 0, cs = 0;
        while (n--) {
            int tm, side;
            cin >> tm >> side;
            if ((side ^ cs) != (tm - ct) % 2) {
                --ans;
            }
            ct = tm;
            cs = side;
        }
        cout << ans << '\n';
    }
}
