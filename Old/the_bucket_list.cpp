#include <iostream>
#include <map>
#include <fstream>

using namespace std;

void solve() {
    ifstream fin("blist.in");
    ofstream fout("blist.out");

    int n;
    fin >> n;
    map<int, int> mp;
    while (n--) {
        int si, ti, bi;
        fin >> si >> ti >> bi;
        mp[si] = bi;
        mp[ti] = -bi;
    }

    int curr = 0;
    int ans = 0;
    for (auto &pair : mp) {
        curr += pair.second;
        ans = max(ans, curr);
    }
    fout << ans << '\n';

    fin.close();
    fout.close();
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}