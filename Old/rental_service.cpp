#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    ifstream fin("rental.in");
    ofstream fout("rental.out");

    ll n, m, r;
    fin >> n >> m >> r;
    ll c[n];
    for (int i = 0; i < n; ++i) {
        fin >> c[i];
    }
    sort(c, c+n);

    vector<pair<ll, ll>> buyers;
    for (int i = 0; i < m; ++i) {
        ll q, p;
        fin >> q >> p;
        buyers.push_back(make_pair(q, p));
    }
    sort(buyers.begin(), buyers.end(), [](auto p1, auto p2) {
        return p1.second < p2.second;
    });
    vector<ll> renters(r, -1);
    for (int i = 0; i < r; ++i) {
        ll ri;
        fin >> ri;
        renters[i] = ri;
    }
    sort(renters.begin(), renters.end());
    // cout << "c = "; for (int i = 0; i < n; ++i) cout << c[i] << " "; cout << "\n";
    // cout << "buyers = "; for (int i = 0; i < m; ++i) cout << "(" << buyers[i].first << ", " << buyers[i].second << ")\n"; cout << "\n";
    // cout << "renters = "; for (int i = 0; i < r; ++i) cout << renters[i] << " "; cout << "\n";

    ll curr = 0;
    int renting = min(r, n);
    for (int i = 0; i < renting; ++i) {
        curr += renters[r - 1 - i];
    }
    int remaining = n - renting, remgallons = 0;
    for (int i = 0; i < remaining; ++i) {
        remgallons += c[n-1-i];
    }
    // cout << "initial remainng gallons = " << remgallons << "\n";
    int bidx = m-1;
    while (bidx >= 0) {
        if (buyers[bidx].first > remgallons) {
            ll buying = remgallons;
            curr += buying * buyers[bidx].second;
            buyers[bidx].first -= remgallons;
            remgallons = 0;
            break;
        } else {
            remgallons -= buyers[bidx].first;
            curr += buyers[bidx].first * buyers[bidx].second;
            buyers[bidx].first = 0; // not needed
            --bidx;
        }
    }
    ll ans = curr;
    // cout << "initial curr = " << curr << "\n";

    while (renting - 1 >= 0) {
        --renting;
        curr -= renters[r-1-renting];
        remgallons = c[renting];
        while (bidx >= 0) {
            if (buyers[bidx].first > remgallons) {
                ll buying = remgallons;
                curr += buying * buyers[bidx].second;
                buyers[bidx].first -= remgallons;
                remgallons = 0;
                break;
            } else {
                remgallons -= buyers[bidx].first;
                curr += buyers[bidx].first * buyers[bidx].second;
                --bidx;
            }
        }
        ans = max(curr, ans);
    }
    fout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
