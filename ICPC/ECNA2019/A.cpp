#include <bits/stdc++.h>
using namespace std;
using ld = long double;

ld dist(pair<int, int> p1, pair<int, int> p2) {
    int dx = p2.first - p1.first;
    int dy = p2.second - p1.second;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<pair<int, int>> judges, tars, feathers;
    for (int i = 0; i < n + m + p; ++i) {
        int x, y;
        cin >> x >> y;
        pair<int, int> p{x, y};
        if (i < n) {
            judges.push_back(p);
        } else if (i < n + m) {
            tars.push_back(p);
        } else {
            feathers.push_back(p);
        }
    }

    vector<array<ld, 3>> jt, jf;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            jt.push_back({dist(judges[i], tars[j]), (ld) i, (ld) j});
        }
        for (int j = 0; j < p; ++j) {
            jf.push_back({dist(judges[i], feathers[j]), (ld) i, (ld) j});
        }
    }
    sort(jt.begin(), jt.end());
    sort(jf.begin(), jf.end());

    set<int> uj, ut, uf;
    ld ans = 0;
    for (int i = 0; i < jt.size() && uj.size() < n; ++i) {
        if (uj.count(jt[i][1]) || ut.count(jt[i][2])) continue;

        uj.insert(jt[i][1]);
        ut.insert(jt[i][2]);
        ans += jt[i][0];
    }
    uj.clear();
    for (int i = 0; i < jf.size() && uj.size() < n; ++i) {
        if (uj.count(jf[i][1]) || uf.count(jf[i][2])) continue;

        uj.insert(jf[i][1]);
        uf.insert(jf[i][2]);
        ans += jf[i][0];
    }
    cout << fixed << setprecision(12) << ans << endl;
}
