#include <bits/stdc++.h>
using namespace std;

double find_loc(vector<int> &pref_h, vector<int> &pref_t, double time) {
    int l = 0, r = pref_h.size(), idx = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (pref_t[mid] <= time) {
            idx = mid;
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    // cout << "idx = " << idx << "\n";

    double loc = pref_h[idx];
    double remaining = time - pref_t[idx];
    // cout << "remaining = " << remaining << "\n";
    loc += remaining / ((double) pref_t[idx+1] - pref_t[idx]) * ((double) pref_h[idx+1] - pref_h[idx]);
    // cout << "loc = " << loc << "\n";
    return loc;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int a, d;
    cin >> a >> d;
    vector<int> pref_a_loc, pref_a_time, pref_d_loc, pref_d_time;
    pref_a_loc.push_back(0); pref_a_time.push_back(0);
    for (int i = 1; i <= a; ++i) {
        int dist, time;
        cin >> dist >> time;
        pref_a_loc.push_back(pref_a_loc.back() + dist);
        pref_a_time.push_back(pref_a_time.back() + time);
    }
    pref_d_loc.push_back(0); pref_d_time.push_back(0);
    for (int i = 1; i <= d; ++i) {
        int dist, time;
        cin >> dist >> time;
        pref_d_loc.push_back(pref_d_loc.back() + dist);
        pref_d_time.push_back(pref_d_time.back() + time);
    }

    double l = 0, r = min(pref_a_time[a], pref_d_time[d]);
    // cout << "r = " << r << '\n';
    for (int i = 1; i <= 60; ++i) {
        double mid = (l+r) / 2.0;
        // cout << "mid = " << mid << "\n";
        double heighta = find_loc(pref_a_loc, pref_a_time, mid), heightd = pref_a_loc[a] - find_loc(pref_d_loc, pref_d_time, mid);
        if (heighta < heightd) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";

    return 0;
}