#include <bits/stdc++.h>
using namespace std;
using ll = long long;

long long m = 998244353;

ll pow(ll a, ll b) {
    if (b == 0) return 1;

    if (b % 2) {
        return (a * pow(a, b - 1)) % m;
    } else {
        ll k = pow(a, b/2);
        return (k * k) % m;
    }
}

int main() {
    ll n, k;
    cin >> n >> k;
    cout << ((((n * pow(2*k, 2*k)) % m) * pow(2*k+1, ((2*k * (m-2)) % (m-1)))) % m) << endl;
}