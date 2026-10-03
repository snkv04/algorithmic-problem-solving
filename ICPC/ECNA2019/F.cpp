#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    int k[10000];
    cin >> n;
    for (int i =0;i<n;i++){
        cin>>k[i];
    }
    bool relieved[10000];
    for(int i=0;i<n;i++){
        relieved[i]=false;
    }

    int opus = k[0];
    int pos = 0;
    for (int i = 0; i < n - 1; ++i) {
        opus -= 1;
        opus %= (n - i);

        while (opus > 0) {
            if (!relieved[pos]) --opus;
            pos = (pos + 1) % n;
        }

        while (relieved[pos]) {
            pos = (pos + 1) % n;
        }
        relieved[pos] = true;

        while (relieved[pos]) {
            pos = (pos + 1) % n;
        }
        opus = k[pos];
    }
    cout << pos + 1 << endl;
}
