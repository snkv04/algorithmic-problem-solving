#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int d;
    std::cin >> d;
    long double r = d / 2.0;
    std::cout << std::fixed << std::setprecision(12) << (M_PI * r * r) << std::endl;

    return 0;
}
