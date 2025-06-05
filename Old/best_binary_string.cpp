#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    char last = '-';
    for (int i = 0; i < n; ++i) {
        if (s[i] != '?') {
            last = s[i];
        } else if (last != '-') {
            s[i] = last;
        }
    }

    char firstsegment = '?';
    for (int i = 0; i < n; ++i) {
        if (s[i] != firstsegment) {
            firstsegment = s[i];
            break;
        }
    }
    if (firstsegment == '?') firstsegment = '0';

    for (int i = 0; i < n; ++i) {
        if (s[i] == '?') s[i] = firstsegment;
        else break;
    }
    
    cout << s << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
