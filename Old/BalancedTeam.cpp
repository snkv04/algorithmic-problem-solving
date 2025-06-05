#include <iostream>
using namespace std;

int main() {
    int n;
    std::cin >> n;
    int a[n];
    for (int i = 0; i <= n-1; i++) {
        std::cin >> a[i];
    }
    std::sort(a, a+n);
    int i = 0, j = 0;
    int ans = 1;
    while (j <= n-1) {
        int valueAtI = a[i];
        if (a[j] <= valueAtI+5) {
            ans = max(ans, j-i+1);
            j++;
        } else {
            i++;
        }
    }
    cout << ans;
    return 0;
}