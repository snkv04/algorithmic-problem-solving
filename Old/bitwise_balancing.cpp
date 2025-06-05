#include <iostream>
#include <vector>

using namespace std;

void solve() {
    long long bcd[3];
    for (int i = 0; i < 3; ++i) {
        cin >> bcd[i];
    }

    vector<int> a;
    while (bcd[0] + bcd[1] + bcd[2]) {
        int b = bcd[0] % 2, c = bcd[1] % 2, d = bcd[2] % 2;
        if (b == c && c == d) {
            a.push_back(0);
        } else if (b == c) {
            a.push_back(1);
        } else if (c == d) {
            cout << -1 << '\n';
            return;
        } else {
            a.push_back(0);
        }
        
        for (int i = 0; i < 3; ++i) {
            bcd[i] /= 2;
        }
    }

    long long ans = 0;
    for (int i = 0; i < a.size(); ++i) {
        ans += (long) a[i] * (1LL << i);
    }
    cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
