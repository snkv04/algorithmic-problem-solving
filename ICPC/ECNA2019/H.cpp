#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll funcd(ll val, ll a, ll b) {
    return val * (a - 2 * val) * (b - 2 * val);
}

int main() {
    ll a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;

    // calculate the poll where derivative is 0, find the best three
    // ll D = (ll)((a + b - sqrt(a * a - a * b + b * b)) / 6);
    vector<ll> vals;
    // for (ll i = -3; i <= 3; ++i) {
    //     vals.push_back({funcd(D + i, a, b), D + i});
    // }
    for (ll i = 1; i <= (b / 2); ++i) {
        vals.push_back(funcd(i, a, b));
    }
    sort(vals.rbegin(), vals.rend());

    // get the biggest 3 box values
    ll x = vals[0];
    ll y = vals[1];
    ll z = vals[2];

    // find N
    ll N = c;
    while (!((N % y == d % y) && (N % z == e % z))) {
        N += x;
    }
    while (!(f <= N && N <= g)) {
        N += lcm(x, lcm(y, z));
    }
    cout << N << endl;
}
