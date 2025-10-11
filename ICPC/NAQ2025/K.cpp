#include <bits/stdc++.h>
using namespace std;

void solve() {
    vector<string> queries = {
        "? 2 2",
        "? 2 4",
        "? 4 2"
    };
    vector<vector<int>> b = {
        {1, 1},
        {1, 3},
        {3, 1}
    };

    int bi = -1, bj = -1;
    for (int k = 0; k < 3; ++k) {
        cout << queries[k] << endl;
        int res;
        cin >> res;
        if (res) {
            bi = b[k][0];
            bj = b[k][1];
            break;
        }
    }
    if (bi == -1) {
        bi = 3;
        bj = 3;
    }

    cout << "? " << bi << " " << bj + 1 << endl;
    int res1; cin >> res1;
    cout << "? " << bi + 1 << " " << bj << endl;
    int res2; cin >> res2;

    if (res1 && res2) {
        //
    } else if (res1) {
        ++bj;
    } else if (res2) {
        ++bi;
    } else {
        ++bi;
        ++bj;
    }
    cout << "! " << bi << " " << bj << endl;
}

int main() {
    solve();

    return 0;
}