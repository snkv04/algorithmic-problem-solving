#include <bits/stdc++.h>
using namespace std;

void solve() {
    /*
    generalized ideas for the future:
    - before trying some weird heuristic optimization, try to find some set of things
    which you can brute-force over and check each one in the set
        - in this problem, it's the set of all possible locations where the character in s is
        lexicographically less than the character in t; this is useful because if we FIX the
        location to be one of those values, then other things are also FIXED, such as the fact
        that all characters to the left are saved, as well as the best (next) open parenthesis
        to use in t for being greater than the corresponding character in s
    - instead of (for a given fixed location of where t will beat s) starting with a minimum length
    string and then adding as many characters into it as possible, we can start with the maximum
    amount of characters we can have (while still having t beat s at that location) and remove as few
    characters from it as possible
    - since we delete ')'s before their matching '('s, the balance of every non-deleted character can
    only ever increase
    */

    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> suf(n, 0), next(n, -1);
    for (int i = n-1; i >= 0; --i) {
        suf[i] = (i == n-1 ? 0 : suf[i+1]) + (s[i] == '(');

        if (s[i] == '(') next[i] = i;
        else if (i < n-1) next[i] = next[i+1];
    }

    int ans = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == ')') {
            if (next[i] == -1) break;

            int nxt = next[i];
            int del = nxt - i;
            if (suf[nxt+1] >= del) ans = max(ans, n - 2 * del);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
