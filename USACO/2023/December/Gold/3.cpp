#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    sort(x.begin(), x.end());

    vector<ll> pref(n, 0), suf(n, 0);
    for (int i = 1; i < n; ++i) {
        pref[i] = pref[i-1] + i * (x[i] - x[i-1]);
    }
    for (int i = n-2; i >= 0; --i) {
        suf[i] = suf[i+1] + (n-1-i) * (x[i+1] - x[i]);
    }

    /*
    - the case where ternary search breaks down (on a discrete space) is where there's a flat region
    that is NOT at the mode of the function. we want to prevent this from happening. by looking at the
    formula for what happens to the sum of scaled distances when moving from haybale i to haybale (i+1),
    this can only happen when the distance jumped is 0. so, we can skip all of these additional haybales
    (meaning those with equivalent x-coordinate), because they do not help us find the mode any easier.
    - more generally, if you're trying to apply an algorithm but there's a case where it fails, see if
    there's a simplification you can make to the inputs that removes the case where the algorithm fails
    but still keeps the algorithm correct.
    */
    vector<int> indices = {0};
    for (int i = 1; i < n; ++i) {
        if (x[i] != x[i-1]) indices.push_back(i);
    }

    int q;
    cin >> q;
    auto get_cost = [&](int idx, ll ai, ll bi) { return pref[idx] * ai + suf[idx] * bi; };
    while (q--) {
        ll ai, bi;
        cin >> ai >> bi;

        int l = 0, r = indices.size()-1;
        while (r - l >= 3) {
            int m1 = l + (r-l)/3, m2 = r - (r-l)/3;
            ll sum1 = get_cost(indices[m1], ai, bi);
            ll sum2 = get_cost(indices[m2], ai, bi);
            if (sum1 <= sum2) {
                r = m2;
            } else {
                l = m1;
            }
        }

        ll ans = 1e18;
        for (int i = l; i <= r; ++i) {
            ans = min(ans, get_cost(indices[i], ai, bi));
        }
        cout << ans << '\n';
    }
}
