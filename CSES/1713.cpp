#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> d(1e6+1);
    for (int i = 1; i <= 1e6; ++i) {
        for (int j = i; j <= 1e6; j += i) {
            d[j] += 1;
        }
    }

    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        cout << d[x] << '\n';
    }
}
