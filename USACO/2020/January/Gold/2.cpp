#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /*
    generalizable ideas for the future:
    - when allocating large arrays near the memory limit, having multiple of them can push you over the
    limit. to circumvent this, try performing your operations in some order that reuses the same memory
    so that you only use one array.
    - if you have some array where arr[l][r] contains some information about the interval [l, r], and you
    want to make an arr2 where arr2[l][r] contains some information about every interval [i, j] such that
    l <= i <= j <= r, then we can calculate arr2[l][r] as equal to
    arr2[l][r-1] + arr2[l+1][r] - arr2[l+1][r-1] + arr[l][r]. why? by definition, arr2[l][r-1] has info
    about all the intervals [i, j] where l <= i <= j <= r-1, and to get the info about those intervals where
    j == r, we can use arr2[l+1][r] and then subtract the double-counted intervals that lie within the
    interval [l+1, r-1]. we can think of this as a 2D prefix sum (which also involves computing things by
    adding two things with overlap then subtracting the double-counted overlap), except instead of pref[i][j]
    being the sum of all arr[a][b] where a <= i and b <= j, we now have pref[i][j] = sum of all arr[a][b] where
    a >= i and b <= j, except when a > b, then arr[a][b] = 0. the correctness of this becomes much clearer
    with a visualization of the matrix, which is upper-triangular.
        - the alternative is to make a prefix sum array pref1, where pref1[i][j] = sum of arr[i][k] across
        all k where i <= k <= j, and then to make another prefix sum array (the one we want) pref2, where
        pref2[i][j] = sum of arr[l][r] across all i <= l <= r <= j, which is calculated using pref1 by
        fixing j. however, this involves more memory and time, so the first one with the prefix sum idea
        is simpler and smoother.
    */

    ifstream cin("threesum.in");
    ofstream cout("threesum.out");

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n < 3) {
        while (q--) {
            int l, r;
            cin >> l >> r;
            cout << "0\n";
        }
        return;
    }

    vector<vector<ll>> ans(n, vector<ll>(n, 0));
    for (int i = 0; i < n-2; ++i) {
        unordered_map<int, int> counts;
        for (int j = i + 2; j < n; ++j) {
            counts[a[j-1]] += 1;
            int target = -a[i] - a[j];
            ans[i][j] = counts.find(target) == counts.end() ? 0 : counts[target];
        }
    }

    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i < n-2 && i + len - 1 < n; ++i) {
            int j = i + len - 1;
            ans[i][j] += ans[i+1][j] + ans[i][j-1] - ans[i+1][j-1];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << ans[l][r] << '\n';
    }
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
