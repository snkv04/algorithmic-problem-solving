#include <iostream>
#include <string>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::string s;
        std::cin >> s;
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] != s[n-1]) {
                ++ans;
            }
        }
        std::cout << ans << std::endl;
    }
}
