#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }

        int ans = 0;
        long long sum = 0, mx = 0;
        for (int i = 0; i < n; ++i) {
            sum += a[i];
            mx = std::max(mx, a[i]);
            if (sum % 2 == 0 && sum / 2 == mx) {
                ++ans;
            }
        }
        std::cout << ans << '\n';
    }

    return 0;
}
