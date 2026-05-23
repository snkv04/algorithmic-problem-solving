#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; ++i) {
        cin >> segments[i].first >> segments[i].second;
    }

    vector<pair<int, int>> combined;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (segments[i].second >= segments[j].first && segments[j].second >= segments[i].first) {
                int l = min(segments[i].first, segments[j].first);
                int r = max(segments[i].second, segments[j].second);
                combined.push_back(make_pair(l, r));
            }
        }
    }
    sort(combined.begin(), combined.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    int last = -1, ans = n;
    for (int i = 0; i < combined.size(); ++i) {
        if (combined[i].first > last) {
            ans -= 2;
            last = combined[i].second;
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
