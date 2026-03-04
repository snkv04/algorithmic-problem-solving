#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;

    bool decreases = false;
    int last = -1;
    for (int i = 0; i < m; ++i) {
        int ai;
        std::cin >> ai;
        last = ai;
        if (i && ai == 1) {
            decreases = true;
        }
    }
    
    if (decreases) {
        std::cout << "1\n";
    } else {
        std::cout << n - last + 1 << '\n';
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
