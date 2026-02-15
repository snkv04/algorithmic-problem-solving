#include <bits/stdc++.h>
using namespace std;

int countshifts(vector<int> &v1, vector<int> &v2) {
    int s = 0, n = v1.size();
    for (int i = 0; i < n; ++i) {
        bool works = true;
        for (int j = 0; j < n; ++j) {
            if (v1[j] >= v2[(i+j)%n]) {
                works = false;
                break;
            }
        }
        s += works;
    }
    return s;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> v(3, vector<int>(n));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> v[i][j];
        }
    }

    int c1 = countshifts(v[0], v[1]), c2 = countshifts(v[1], v[2]);
    cout << 1LL * n * c1 * c2 << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
