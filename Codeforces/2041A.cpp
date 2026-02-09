#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::set<int> remaining = {1, 2, 3, 4, 5};
    for (int i = 0; i < 4; ++i) {
        int num;
        std::cin >> num;
        remaining.erase(num);
    }
    std::cout << *remaining.begin() << std::endl;

    return 0;
}
