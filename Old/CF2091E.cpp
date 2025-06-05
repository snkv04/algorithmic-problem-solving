#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /*
    Let a and b be fixed
    g = gcd(a, b)
    a = cg, b = dg
    lcm(a, b) = ab/g = cgdg/g = cd*g
    F(a, b) = cdg/g = cd
    if we want F to be prime, then cd has to be prime, so then a has to be 1 times g
        and b has to be some larger multiple of g
    however, note that there are absolutely no restrictions on g itself
    so, we can iterate over values of g, fixing a=g and seeing how many values of b
        we can take using that value of g
    */

    int n;
    cin >> n;
    vector<bool> isprime(n+1, true);
    for (int d = 2; d <= n/2; ++d) {
        for (int multiple = 2*d; multiple <= n; multiple += d) {
            isprime[multiple] = false;
        }
    }
    vector<int> primelist;
    for (int i = 2; i <= n; ++i) {
        if (isprime[i]) primelist.push_back(i);
    }

    ll ans = 0;
    for (int g = 1; g <= n/2; ++g) {
        int l = 0, r = primelist.size() - 1, idx = -1, bound = n/g;
        while (l <= r) {
            int m = (l + r) / 2;
            if (primelist[m] <= bound) {
                idx = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        ans += idx + 1;
    }
    cout << ans << "\n";
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
