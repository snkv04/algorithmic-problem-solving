#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MOD = 1e9 + 7;
vector<ll> fac, invfac;

ll modpow(ll b, ll e) {
    if (!e) {
        return 1;
    }

    if (e % 2) {
        return (modpow(b, e-1) * b) % MOD;
    } else {
        ll result = modpow(b, e/2);
        return (result * result) % MOD;
    }
}

ll moddiv(ll a, ll b) {
    ll inv = modpow(b, MOD - 2);
    return (a * inv) % MOD;
}

ll nCr(ll n, ll r) {
    ll num = fac[n], denom1 = invfac[r], denom2 = invfac[n-r];
    return (((num * denom1) % MOD) * denom2) % MOD;
}

int main() {
    /*
    - how does this solution relate to the editorial? first, just for context, recognize that there will
    be n/(k+1) M's, and k*n/(k+1) O's. then, if we go from right to left (like in this algorithm), then
    for each M, we just want to have the number of remaining O's to the right that haven't been used.
    however, if we go from left to right, we can still calculate the number of "remaining" O's that haven't
    been used by M's to the right, as the remaining O's will increase as we move from left to right (because
    there will be fewer O's that are used by M's to the right of each M that we pass) while they'll also
    decrease by a bit since we'll literally have less O's to the right as we move to the right. it's just
    another implementation; this code is more intuitive.
    */

    ll k, n, l;
    cin >> k >> n >> l;
    string t;
    cin >> t;
    assert(t[0] == 'M');

    fac.resize(n+1);
    invfac.resize(n+1);
    fac[0] = invfac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = (fac[i-1] * i) % MOD;
        invfac[i] = moddiv(invfac[i-1], i);
    }

    ll ans = 1, count = 0;
    for (int i = n-1; i >= 0; --i) {
        if (t[i] == 'O') {
            ++count;
        } else {
            ans = (ans * nCr(count, k)) % MOD;
            count -= k;
        }
    }
    ans = modpow(ans, l);
    cout << ans << endl;
}
