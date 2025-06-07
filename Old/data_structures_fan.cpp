#include <iostream>

using namespace std;

void solve() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    string s;
    cin >> s;

    int pref0[n+1], pref1[n+1];
    pref0[0] = 0; pref1[0] = 0;
    for (int i = 1; i <= n; ++i) {
        pref0[i] = pref0[i-1];
        pref1[i] = pref1[i-1];
        if (s[i-1] == '0') {
            pref0[i] = pref0[i] ^ a[i-1];
        } else {
            pref1[i] = pref1[i] ^ a[i-1];
        }
    }
    int total0 = pref0[n], total1 = pref1[n];

    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int l, r;
            cin >> l >> r;
            int xor0 = pref0[r] ^ pref0[l-1], xor1 = pref1[r] ^ pref1[l-1];
            total0 = total0 ^ xor0;
            total0 = total0 ^ xor1;
            total1 = total1 ^ xor0;
            total1 = total1 ^ xor1;
        } else {
            int g; cin >> g;
            if (g == 0) {
                cout << total0 << " ";
            } else {
                cout << total1 << " ";
            }
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}