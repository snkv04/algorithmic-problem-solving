#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        
        int num = (n + 1) / 2;
        std::cout << num << " ";
        for (int i = 1; i < n; ++i) {
            if (i % 2) {
                num += i;
            } else {
                num -= i;
            }
            std::cout << num << " ";
        }
        std::cout << '\n';
    }

    return 0;
}
