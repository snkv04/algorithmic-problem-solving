#include <iostream>
#include <map>

using namespace std;

#define ll long long

void solve() {
    ll end = 2;
    map<ll, int> map;
    while (true) {
        cout << "buf[" << end << "]" << endl;
        int result;
        cin >> result;
        map[end] = result;
        if (result) {
            end *= 2;
        } else {
            break;
        }
    }
    
    ll l = end / 2, r = end-1, ans = -1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        int result;
        if (map.find(mid) == map.end()) {
            cout << "buf[" << mid << "]" << endl;
            cin >> result;
            map[mid] = result;
        } else {
            result = map[mid];
        }
        
        if (result) {
            l = mid + 1;
            ans = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << "strlen(buf) = " << ++ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}