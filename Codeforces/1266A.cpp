#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    
    bool zero = 0, nonzero = 0;
    int evens = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
        int digit = s[i] - '0';
        zero = zero || (digit == 0);
        nonzero = nonzero || (digit != 0);
        evens += digit % 2 == 0;
        sum += digit;
    }
    cout << ((!nonzero || (zero && (evens >= 2) && (sum % 3 == 0))) ? "red" : "cyan") << endl;
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
