#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int t1 = 0;
    int t2 = 0;
    
    for (int i = 0; i < 10; i++) {
        vector<ll> dist1,dist2;
        int n;
        cin >> n;
         for (int j = 0; j < n; j++) {
            int x,y;
            cin >> x >> y;
            dist1.push_back((x-144)*(x-144)+(y-84)*(y-84));
         }
        cin >> n;
         for (int j = 0; j < n; j++) {
            int x,y;
            cin >> x >> y;
            dist2.push_back((x-144)*(x-144)+(y-84)*(y-84));
         }
        sort(dist1.begin(),dist1.end());
        sort(dist2.begin(),dist2.end());
        if (dist1.size() == 0) {
            t2 += dist2.size();
        } else if (dist2.size() == 0) {
            t1 += dist1.size();
        } else {

        for (auto x : dist1) {
            if (x < dist2[0]) {
                t1 += 1;
            }
        }
        for (auto x : dist2) {
            if (x < dist1[0]) {
                t2 += 1;
            }
        }
        }
    }
    cout << t1 << " " << t2 << endl;
}