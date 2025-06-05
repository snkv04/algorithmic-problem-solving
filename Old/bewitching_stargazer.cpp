#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

pair<ll, ll> recurse(ll n, ll k) {
    if (n < k) {
        return make_pair(0, 0);
    }

    pair<ll, ll> left = recurse(n / 2, k);
    ll lucky = left.first, count = left.second;
    if (n % 2) {
        ll mid = (n + 1) / 2;
        lucky = 2 * lucky + mid * count;
        count *= 2;

        lucky += mid;
        count += 1;
    } else {
        ll mid = n / 2;
        lucky = 2 * lucky + mid * count;
        count *= 2;
    }
    return make_pair(lucky, count);
}

void solve() {
    ll n, k;
    cin >> n >> k;
    cout << recurse(n, k).first << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
