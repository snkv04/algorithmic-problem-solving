#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll MOD = 1000000007;
unordered_map<ll, ll> sin_cache;
unordered_map<ll, ll> cos_cache;
//ll sin1;
//ll cos1;

ll cosa(ll n);

ll sina(ll n) {
    if (sin_cache.find(n) != sin_cache.end()) {
        return sin_cache[n];
    }

    //if (n == 1) return sin1 % MOD;
    if (n % 2 == 0) {
        return sin_cache[n] = (2 * (sina(n / 2) * cosa(n / 2)) % MOD) % MOD;
    }
    return sin_cache[n] = ((sina(n - 1) * cosa(1)) % MOD + (sina(1) * cosa(n - 1)) % MOD) % MOD;
}

ll cosa(ll n) {
    if (cos_cache.find(n) != cos_cache.end()) {
        return cos_cache[n];
    }

    if (n % 2 == 0) {
        ll c = cosa(n / 2) % MOD;
        ll s = sina(n / 2) % MOD;
        return cos_cache[n] = ((c * c) % MOD - (s * s) % MOD) % MOD;
    }
    return cos_cache[n] = ((cosa(n - 1) * cosa(1)) % MOD - (sina(1) * sina(n - 1)) % MOD) % MOD;
}

ll expa(ll a, ll n) {
    if (n == 1) return a % MOD;

    if (n % 2 == 0) {
        ll ans = expa(a, n/2) % MOD;
        return (ans * ans) % MOD;
    }
    return (a * expa(a, n - 1)) % MOD;
}

int main() {
    ll a, b, n;
    cin >> a >> b >> n;
    ll inv = expa((a*a % MOD + b*b % MOD) % MOD, MOD - 2);
    cos_cache[1] = (((a*a) % MOD - (b*b) % MOD + MOD) % MOD * inv) % MOD;
    sin_cache[1] = (2 * ((a * b) % MOD * inv) % MOD) % MOD;
    cout << (MOD - cosa(n+1)) % MOD << endl;
}