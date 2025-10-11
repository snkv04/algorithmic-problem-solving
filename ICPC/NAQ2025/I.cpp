#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; 
    cin >> n;
    vector<ll> bonus;
    vector<ll> solves;
    for (int i = 0; i < n; i++) {
        ll k;
        cin >> k;
        bonus.push_back(k);
    }
    for (int i = 0; i < n; i++) {
        ll k;
        cin >> k;
        solves.push_back(k);
    }
    sort(solves.begin(), solves.end());
    reverse(solves.begin(), solves.end());
    ll acc = 0;
    double max_r = 0;
    for (int i = 0; i < n; i++) {
        acc += solves[i];
        double new_r = (acc+bonus[i])/(i+1.0);
        max_r = max_r > new_r ? max_r : new_r;
    }
    cout << fixed << setprecision(8) << max_r << endl;
}