#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    cin >> n;
    int people = 0;
    while (n--) {
        char type; cin >> type;
        int num; cin >> num;
        if (type == 'P') {
            people += num;
        } else {
            if (people >= num) {
                people -= num;
                num = 0;
            } else {
                num -= people;
                people = 0;
            }

            cout << (num >= 1 ? "YES" : "NO") << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
