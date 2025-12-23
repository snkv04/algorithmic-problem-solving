#include <bits/stdc++.h>
using namespace std;

// doesn't this problem use the wrong definition of permutation?

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> ans = {(1<<n)-1, (1<<(n-1))-1};
        set<int> seen(ans.begin(), ans.end());
        for (int i = n-2; i >= 0; --i) {
            for (int j = 0; j < (1 << (n-i)); ++j) {
                int num = (j << i) + (1 << i) - 1;
                if (seen.find(num) == seen.end()) {
                    ans.push_back(num);
                    seen.insert(num);
                }
            }
        }

        for (int num : ans) cout << num << ' ';
        cout << '\n';
    }
}
