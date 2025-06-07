#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int l = 1, r = 1e6, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        cout << mid << endl;
        // fflush(stdout);
        string input;
        cin >> input;
        if (input == ">=") {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << "! " << ans << endl;
    // fflush(stdout);

    return 0;
}