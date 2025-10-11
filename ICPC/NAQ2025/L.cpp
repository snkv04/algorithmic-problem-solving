#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n = 0; 
    cin >> n;
    vector<int> dists;
     for (int i = 0; i < n ; i++) {
        int k;
        cin >> k;
        dists.push_back(k);
     }
    sort(dists.begin(),dists.end());
    int a = dists[0]/3;
    int c = dists[dists.size() - 1]/3;
    int b = dists[1] - a - a;
    cout << a << " " << b << " " << c << endl;
}