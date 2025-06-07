#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int a[n];
    int counts[3];
    fill(counts, counts+3, 0);
    set<int> positions[3];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ++counts[a[i]];
        positions[a[i]].insert(i);
    }

    vector<pair<int, int>> ans;
    for (int i = n-1; i >= n-counts[2]; --i) {
        if (a[i] == 1) {
            int left2 = *positions[2].begin();
            positions[2].erase(left2);
            positions[1].erase(i);

            a[left2] = 1;
            a[i] = 2;
            positions[1].insert(left2);
            positions[2].insert(i);

            ans.push_back(pair<int, int>(left2, i));
        } else if (a[i] == 0) {
            int left1 = *positions[1].begin();
            positions[0].erase(i);
            positions[1].erase(left1);

            a[left1] = 0;
            a[i] = 1;
            positions[0].insert(left1);
            positions[1].insert(i);

            ans.push_back(make_pair(i, left1));

            int left2 = *positions[2].begin();
            positions[2].erase(left2);
            positions[1].erase(i);

            a[i] = 2;
            a[left2] = 1;
            positions[2].insert(i);
            positions[1].insert(left2);

            ans.push_back(make_pair(i, left2));
        }
    }

    for (int i = 0; i < counts[0]; ++i) {
        if (a[i] == 1) {
            int right0 = *positions[0].rbegin();
            a[i] = 0;
            a[right0] = 1;
            positions[0].erase(right0);
            positions[1].erase(i);
            positions[0].insert(i);
            positions[1].insert(right0);
            ans.push_back(make_pair(i, right0));
        }
    }

    cout << ans.size() << "\n";
    for (const auto &p : ans) {
        cout << p.first + 1 << " " << p.second + 1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
