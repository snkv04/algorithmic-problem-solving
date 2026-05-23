#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> pow = {1, 10, 100, 1000, 10000};
    vector<int> a(n); for (int i = 0; i < n; ++i) a[i] = s[i] - 'A';
    
    vector<vector<vector<int>>> mem(n+1, vector<vector<int>>(2, vector<int>(5, -2e9)));
    mem[n][0][0] = 0;  // max value for the empty suffix where no letters were changed and the max letter seen was A is 0
    for (int i = n-1; i >= 0; --i) {
        for (int to = 0; to < 5; ++to) {  // letter that we're changing to
            if (to != a[i]) {  // the letter we're considering for this index actually is different
                // iterate over possible maxes to right
                for (int max_to_right = 0; max_to_right < 5; ++max_to_right) {
                    // update DP value for a subproblem which we calculate the index for
                    int new_max = max(to, max_to_right);
                    mem[i][1][new_max] = max(
                        // the previous value we got for this subproblem
                        mem[i][1][new_max],

                        // grab value from right where we didn't change any letter, and add
                        // the value from the letter we're changing to, making sure to check
                        // if the max to right is greater than the letter we're changing to
                        mem[i+1][0][max_to_right] + (to >= max_to_right ? pow[to] : -pow[to])
                    );
                }
            } else {  // we didn't actually change the letter
                for (int max_to_right = 0; max_to_right < 5; ++max_to_right) {
                    int new_max = max(to, max_to_right);
                    for (int change_made = 0; change_made < 2; ++change_made) {
                        // just propagate the values from the right for the cases where we either
                        // have or haven't made a change somewhere to the right, and then just
                        // apply the value of the letter
                        mem[i][change_made][new_max] = max(
                            mem[i][change_made][new_max],
                            mem[i+1][change_made][max_to_right] + (to >= max_to_right ? pow[to] : -pow[to])
                        );
                    }
                }
            }
        }
    }

    int ans = -2e9;
    for (int max_seen = 0; max_seen < 5; ++max_seen) {
        for (int change_made = 0; change_made < 2; ++change_made) {
            ans = max(ans, mem[0][change_made][max_seen]);
        }
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
