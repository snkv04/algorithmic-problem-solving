#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5e5 + 5, MAXM = 35, LOGMAXN = 25;
int wa[MAXN], wb[MAXN], wv[MAXN], wt[MAXN];
int RMQ[MAXN], mm[MAXN], best[LOGMAXN][MAXN];

int cmp(int *r, int a, int b, int l) {
    return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int *r, int *sa, int n, int m) {
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
        for (i = 1; i < m; ++i) wt[i] += wt[i-1];
        for (i = n-1; i >= 0; --i) sa[--wt[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; ++i) 
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;
    }
    return;
}

void calheight(int *r, int *sa, int *ht, int *rk, int n) {
    int i, j, k = 0;
    for (i = 1; i <= n; ++i) rk[sa[i]] = i;
    for (i = 0; i < n; ht[rk[i++]] = k) 
        for (k ? k-- : 0, j = sa[rk[i] - 1]; r[i+k] == r[j+k]; ++k) ;
    return;
}

void solve() {
    /*
    generalizable ideas for the future:
    - no suffixes start at the same index; there are only n of them (outside the sentinel one, which
    makes n+1 total), and their start indices cover the range [0, n-1].
        - as a result, ALL suffixes are distinct. this becomes obvious after considering the fact that
        they all have different length.
    - any given substring of a string is a prefix of one of its suffixes.
    - for a given suffix i, the ones with the maximum LCP to it are either sa[rk[i]-1] or sa[rk[i]+1].
    so, iterating over the suffixes in sorted order, we can look at that suffix and the one right before
    it, take the LCP, and all of the prefixes of that suffix that are longer than that value are appearing
    for the first time so we add it to the count. by "first time", i'm talking about all the first time
    among all of the possible substrings considered so far when iterating through the suffixes in sorted
    order.
        - if we want to find all possible substrings that only appear a SINGLE time in the entire array,
        then i think for an index i, we would take max(lcp of sa[i] and sa[i-1], lcp of sa[i+1] and s[i]),
        then then all of the substrings that are longer than that of sa[i] would be unique throughout the
        entire array. this is because if anything longer than that was shared between the suffix starting
        at sa[i] and another suffix's prefix, then it would have been adjacent to sa[i] in the array sa.
    */

    string s;
    cin >> s;
    int n = s.size();
    int r[n+1];
    for (int i = 0; i < n; ++i) {
        r[i] = s[i] - 'a' + 1;
    }
    r[n] = 0;

    int sa[n+1]; fill(sa, sa+n+1, 0);
    da(r, sa, n, MAXM); // builds suffix array

    int ht[n+1]; fill(ht, ht+n+1, 0);
    int rk[n+1]; fill(rk, rk+n+1, 0);
    calheight(r, sa, ht, rk, n); // builds lcp array

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        int len = n - sa[i];
        ans += len - ht[i]; // ht[1] = 0, because sa[0] = n (the sentinel suffix)
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}
