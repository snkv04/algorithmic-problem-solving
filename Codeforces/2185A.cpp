#include <iostream>

void solve() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cout << i;
        if (i < n) std::cout << ' ';
    }
    std::cout << std::endl;
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
