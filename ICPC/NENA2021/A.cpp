#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    string s1,s2;
    cin >> s1 >> s2;
    int count = 1;
    for (int i = 0; i < 4; i++) {
        if (s1[i] != s2[i]) count *= 2;
    }
    cout << count << endl;
}