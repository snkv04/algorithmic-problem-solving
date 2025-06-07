#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

ll modpow(ll a, ll p) {
    if (p == 0) return 1LL;
    ll ret = modpow(a, p/2);
    ret = (ret * ret) % MOD;
    if (p % 2 == 0) return ret;
    return (ret * a) % MOD;
}

ll modInvPrimeMod(ll a) {
    return modpow(a, MOD-2);
}

void solve() {
    int n, q;
    cin >> n >> q;
    pair<ll, int> a[n], b[n];
    for (int i = 0; i < 2*n; ++i) {
        if (i < n) {
            ll ai;
            cin >> ai;
            a[i] = make_pair(ai, i);
        } else {
            ll bi; cin >> bi;
            b[i%n] = make_pair(bi, i);
        }
    }
    sort(a, a+n, [](auto &p1, auto &p2){
        return p1.first < p2.first;
    });
    sort(b, b+n, [](auto &p1, auto &p2){
        return p1.first < p2.first;
    });
    // cout << "a = "; for (int i = 0; i < n; ++i) cout << "(" << a[i].first << ", " << a[i].second << ") "; cout << "\n";
    // cout << "b = "; for (int i = 0; i < n; ++i) cout << "(" << b[i].first << ", " << b[i].second << ") "; cout << "\n";

    map<int, int> mpa, mpb;
    for (int i = 0; i < n; ++i) {
        mpa[a[i].second] = i;
        mpb[b[i].second] = i;
    }

    ll product = 1;
    for (int i = 0; i < n; ++i) {
        product *= min(a[i].first, b[i].first);
        product %= MOD;
    }
    cout << product << " ";

    while (q--) {
        int oi, xi; cin >> oi >> xi; --xi;
        if (oi == 1) {
            int idx = mpa[xi];
            ll val = a[idx].first + 1;
            int newidx = idx;
            while (newidx + 1 < n && a[newidx+1].first < val) {
                ++newidx;
            }
            // cout << "\nidx = " << idx << ", newidx = " << newidx << "\n";

            // remove old product
            ll div = modInvPrimeMod(min(a[idx].first, b[idx].first));
            product *= div; product %= MOD;
            div = modInvPrimeMod(min(a[newidx].first, b[newidx].first));
            product *= div; product %= MOD;

            // add new product
            // cout << "before = "; for (int i = 0; i < n; ++i) cout << "(" << a[i].first << ", " << a[i].second << ") "; cout << "\n";
            // cout << "after = "; for (int i = 0; i < n; ++i) cout << "(" << a[i].first << ", " << a[i].second << ") "; cout << "\n";
            a[idx].first = a[newidx].first;
            a[newidx].first = val;
            product *= min(a[idx].first, b[idx].first); product %= MOD;
            product *= min(a[newidx].first, b[newidx].first); product %= MOD;

            // change mappings
            swap(a[idx].second, a[newidx].second);
            mpb[a[idx].second] = idx;
            mpb[a[newidx].second] = newidx;
        } else {
            int idx = mpb[xi];
            ll val = b[idx].first + 1;
            int newidx = idx;
            while (newidx + 1 < n && b[newidx+1].first < val) {
                ++newidx;
            }

            // remove old product
            ll div = modInvPrimeMod(min(a[idx].first, b[idx].first));
            product *= div; product %= MOD;
            div = modInvPrimeMod(min(a[newidx].first, b[newidx].first));
            product *= div; product %= MOD;

            // add new product
            b[idx].first = b[newidx].first;
            b[newidx].first = val;
            product *= min(a[idx].first, b[idx].first); product %= MOD;
            product *= min(a[newidx].first, b[newidx].first); product %= MOD;

            // change mappings
            swap(b[idx].second, b[newidx].second);
            mpb[b[idx].second] = idx;
            mpb[b[newidx].second] = newidx;
        }
        cout << product << " ";
    }
    cout << "\n";
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
