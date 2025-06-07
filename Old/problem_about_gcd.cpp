#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

ll gcd(ll a, ll b) {
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll r = A % B;
        A = B;
        B = r;
    }
    return A;
}

void solve() {
    /**
     * put simply, if the gcd of A and B is G, then if we let A = cG and B = dG, we need
     * for gcd(c, d) to be equal to 1. we can then simply brute force through the pairs
     * of coprime c and d, making sure that we go in a proper ordering to meet the selection
     * criteria specified in the problem (outer loop increases left bound, inner loop decreases
     * right bound). also, pruning is used to make the time complexity less than
     * O((l-r)^2 * log(r)).
     */

    ll l, r, g;
    cin >> l >> r >> g;
    ll low = ((l+g-1) / g) * g, high = (r / g) * g;
    if (low > r || high < l) {
        cout << "-1 -1\n";
        return;
    }

    low /= g; high /= g;
    ll left = -1, right = -2;
    for (ll i = low; i <= high; ++i) {
        if (high - i < right - left) break;
        for (ll j = high; j >= i; --j) {
            if (j - i < right - left) break;
            if (gcd(i, j) == 1 && j - i > right - left) {
                right = j;
                left = i;
            }
        }
    }

    if (left != -1) {
        cout << left * g << " " << right * g << "\n";
    } else {
        cout << "-1 -1\n";
    }
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
