#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4e5 + 5, LOGMAXN = 25;
int wa[MAXN], wb[MAXN], wv[MAXN], wt[MAXN], mm[MAXN], sa[MAXN], rk[MAXN], ht[MAXN], rmq[MAXN], best[LOGMAXN][MAXN];

int cmp(int *r, int a, int b, int l) {
    return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int *r, int n, int m) {
    ++n;
    int i, j, p;
    int *x = wa;
    int *y = wb;
    int *t;
    for (i = 0; i < m; ++i) wt[i] = 0;
    for (i = 0; i < n; ++i) wt[x[i] = r[i]]++;
    for (i = 1; i < m; ++i) wt[i] += wt[i-1];
    for (i = n-1; i >= 0; --i) sa[--wt[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p) {
        for (p = 0, i = n-j; i < n; ++i) y[p++] = i;
        for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < n; ++i) wv[i] = x[y[i]];
        for (i = 0; i < m; ++i) wt[i] = 0;
        for (i = 0; i < n; ++i) wt[wv[i]]++;
        for (i = 0; i < m; ++i) wt[i] += wt[i-1];
        for (i = n-1; i >= 0; --i) sa[--wt[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; ++i)
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
    }
    return;
}

void calheight(int *r, int n) {
    int i, j, k = 0;
    for (i = 1; i <= n; ++i) rk[sa[i]] = i;
    for (i = 0; i < n; ht[rk[i++]] = k)
        for (k ? k-- : 0, j = sa[rk[i] - 1]; r[i+k] == r[j+k]; ++k)
            ;
    return;
}

void initrmq(int n) {
    int i, j, a, b;
    for (mm[0] = -1, i = 1; i <= n; ++i)
        mm[i] = ((i & (i-1)) == 0) ? mm[i-1] + 1 : mm[i-1];
    for (i = 1; i <= n; ++i)
        best[0][i] = i;
    for (i = 1; i <= mm[n]; ++i)
        for (j = 1; j <= n+1-(1<<i); ++j) {
            a = best[i-1][j];
            b = best[i-1][j+(1<<(i-1))];
            
            if (rmq[a] < rmq[b]) best[i][j] = a;
            else best[i][j] = b;
        }
    return;
}

int askrmq(int a, int b) {
    int t;
    t = mm[b-a+1];
    b -= (1 << t) - 1;
    a = best[t][a];
    b = best[t][b];
    return rmq[a] < rmq[b] ? a : b;
}

int lcp(int a, int b) {
    int t;
    a = rk[a];
    b = rk[b];
    if (a > b) swap(a, b);
    return ht[askrmq(a+1, b)];
}

void solve() {
    /*
    what would be a brute-force solution? for each cyclic shift (starting point), we binary search on the smallest
    length such that the cyclic substring starting at that point is not shared among any other substrings of that
    length. even if we use hashing, we have N starting points to check, and for each iteration of binary search, we
    have N other starting points to check, which is O(N^2 * log(N)). however, by using a suffix array, we only need
    to check 2 other shifts. in fact, for each of those 2 other shifts, we don't even have to use binary search to
    find the length of the LCP, because that can be found for free using the standard LCP precomputation, so we only
    do it in O(1).

    generalizable ideas for the future:
    - if we want to use substrings of the cyclic string, then just double the string and only consider suffixes
    starting in the first half (because those have the benefit of having another full extension of the original
    string coming after it).
    - given a substring, instead of looking over all other substrings to find the longest non-unique prefix of it,
    we can just check the two closest ones (to the left and right) in the lexicographical order (i.e., we're looking
    for the suffixes that are closest to the left and right in the suffix array) and take the max of their LCPs with
    the given substring. if these are NOT adjacent in the suffix array (because there are other substrings that we
    don't care about in between), we can just keep track of the closest left and right ones using some other method
    (like an auxiliary array).
    */

    int len;
    cin >> len;
    vector<int> a(len);
    for (int i = 0; i < len; ++i) cin >> a[i];

    int r[2*len+1];
    r[2*len] = 0;
    for (int i = 0; i < len; ++i) {
        r[i] = r[i+len] = (a[i] < a[(i+1)%len] ? 1 : 2);
    }
    // cout << "r: ";
    // for (int i = 0; i <= 2*len; ++i) cout << r[i] << " ";
    // cout << endl;

    int m = 3, n = 2*len;
    da(r, n, m);
    calheight(r, n);
    for (int i = 0; i <=n ; ++i) rmq[i] = ht[i];
    initrmq(n);

    vector<int> closestleft(len), closestright(len);
    int last = -1;
    for (int i = 0; i <= n; ++i) {
        if (sa[i] < len) {
            closestleft[sa[i]] = last;
            last = sa[i];
        }
    }
    last = -1;
    for (int i = n; i >= 0; --i) {
        if (sa[i] < len) {
            closestright[sa[i]] = last;
            last = sa[i];
        }
    }

    vector<int> ans(len);
    for (int i = 0; i < len; ++i) {
        int longest = 0;
        if (closestleft[i] != -1) longest = max(longest, lcp(i, closestleft[i]));
        if (closestright[i] != -1) longest = max(longest, lcp(i, closestright[i]));

        if (longest >= len) {
            ans[i] = -1;
        } else {
            ans[i] = longest + 1;
        }
    }

    for (int i = 0; i < len; ++i) cout << ans[i] << "\n";
}

int main() {
    solve();
    return 0;
}
