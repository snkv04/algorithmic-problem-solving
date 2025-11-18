#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    map<int, int> freqs;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        freqs[ai] += 1;
    }

    int missing = 0;
    for (int i = 0; i <= n; ++i) {
        int ans = max(freqs.find(i) == freqs.end() ? 0 : freqs[i], missing);
        cout << ans << "\n";
        missing += freqs.find(i) == freqs.end();
    }
}

int main() {
    solve();

    return 0;
}