#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    map<char, int> to_val = {
        {'A', 1},
        {'B', 10},
        {'C', 100},
        {'D', 1000},
        {'E', 10000},
    };
    string letters = "ABCDE";
    
    int ans = -2e9;
    for (int i = 0; i < n; ++i) {  // iterates through each character; order of this loop doesn't matter
        // capture the original letter
        char orig = s[i];

        // iterate through all possibilities that we can change it to
        for (int j = 0; j < 5; ++j) {
            // update the letter
            s[i] = letters[j];

            // brute-force find the value for the string
            int value = 0;
            char max_seen = 'A';
            for (int k = n-1; k >= 0; --k) {
                if (max_seen > s[k]) {
                    value -= to_val[s[k]];
                } else {
                    value += to_val[s[k]];
                }
                max_seen = max(max_seen, s[k]);
            }
            ans = max(ans, value);
        }

        // return the letter to what it was
        s[i] = orig;
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
