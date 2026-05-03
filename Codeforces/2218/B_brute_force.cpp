#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        std::vector<int> a(7);
        for (int i = 0; i < 7; ++i) std::cin >> a[i];
        
        int ans = -1e9;
        for (int i = 0; i < 7; ++i) {
            int sum = 0;
            for (int j = 0; j < 7; ++j) {
                if (j == i) {
                    sum += a[j];
                } else {
                    sum += -a[j];
                }
            }
            ans = std::max(ans, sum);
        }
        std::cout << ans << std::endl;
    }
    
    return 0;
}
