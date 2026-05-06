#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }

    vector<pair<int, int>> lis;
    for (int i = 0; i < n; ++i) {
        if (lis.empty() || lis.back() < a[i]) {
            lis.push_back(a[i]);
            cout << lis.size() << " ";
        } else {
            int l = 0, r = lis.size() - 1, idx = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (lis[m] >= a[i]) {
                    idx = m;
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            lis[idx] = a[i];
            cout << idx + 1 << " ";
        }
    }
    cout << endl;

    return 0;
}
