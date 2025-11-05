#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

string convert(ll i) {
    if (i < 0) return "Rubble!";
    if (i % 3 == 0) return "A";
    if (i % 3 == 1) return "B";
    return "C";
}

void solve() {
    ll A, B, C;
    cin >> A >> B >> C;
    ll high = max(max(A, B), C);
    ll high_loc;
    if (high == A) high_loc = 0;
    if (high == B) high_loc = 1;
    if (high == C) high_loc = 2;
    ll low = min(min(A, B), C);
    ll low_loc;
    if (low == A) low_loc = 0;
    if (low == B) low_loc = 1;
    if (low == C) low_loc = 2;
    ll mid = A + B + C - high - low;

    if (high >= 2*(mid + low)) {
        cout << convert(high_loc) << " " << high - 2*(mid + low) + 1 << endl;
        return;
    }
    
    if ((A + B + C) % 3 != 1) {
        cout << convert(-1) << endl;
        return;
    }
    if (high - mid > mid - low) {
//        cout << high << " " << mid << " " << low << endl;
        cout << convert(high_loc + 2 * low + (high + low - 2 * mid) / 3) << " " << 1 << endl;
    } else {
        cout << convert(low_loc + 2 * low - 1) << " " << 1 << endl;
    }
}



int main() {
    solve();
}