#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, n;
        cin >> a >> b >> n;
        if (b == a) {
            cout << "1\n";
        } else {
            if (static_cast<double>(a) / n >= b) {
                cout << "1\n";
            } else {
                cout << "2\n";
            }
        }
    }
}
