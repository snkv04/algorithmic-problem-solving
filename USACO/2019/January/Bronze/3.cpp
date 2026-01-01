#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("guess.in");
    ofstream cout("guess.out");

    int n;
    cin >> n;
    vector<unordered_set<string>> c(n);
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        int k;
        cin >> k;
        while (k--) {
            cin >> s;
            c[i].insert(s);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int cnt = 0;
            for (string trait : c[i]) {
                if (c[j].find(trait) != c[j].end()) {
                    ++cnt;
                }
            }
            ans = max(ans, cnt + 1);
        }
    }
    cout << ans << endl;
}
