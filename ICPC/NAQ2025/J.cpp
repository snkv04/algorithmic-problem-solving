#include <bits/stdc++.h>
using namespace std;

void solve() {
    int arr[100];
    for (int i = 0; i < 100; ++i)
    {
        cin >> arr[i];
    }
    int remainder = arr[99] % 10;
    if (remainder == 0)
    {
        remainder = 10;
    }
    cout << remainder;
}

int main() {
    solve();

    return 0;
}