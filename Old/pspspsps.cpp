#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    int n;
    string s;
    cin >> n >> s;
    set<pair<int, int>> segments;
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'p' || i == n-1) {
            segments.insert(make_pair(last + 1, i));
            last = i;
        }
    }

    bool good = true;
    for (int i = n-1; i >= 0 && good; --i) {
        if (s[i] == 's') {
            set<int> available;
            for (auto it = segments.rbegin(); it != segments.rend(); ++it) {
                int l = (*it).first, r = (*it).second;
                if (l >= i) {
                    for (int j = l; j <= r; ++j) available.insert(j);
                } else {
                    int count = r - i + 1;
                    for (int j = l; j < l + count; ++j) available.insert(j);
                }
            }

            int needed = n - i;
            for (int j = 0; j < needed; ++j) {
                if (available.find(j) == available.end()) {
                    good = false;
                    break;
                }
            }
        }
    }
    cout << (good ? "YES" : "NO") << "\n";
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
