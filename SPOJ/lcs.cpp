#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5, LOGMAXN = 25;
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
    string s, t;
    cin >> s >> t;
    int lens = s.size(), lent = t.size();

    int r[lens+lent+2];
    r[lens] = 0;
    r[lens+lent+1] = 1;
    for (int i = 0; i <= lens+lent; ++i) {
        if (i < lens) {
            r[i] = s[i] - 'a' + 2;
        } else if (i > lens && i <= lens + lent) {
            r[i] = t[i-lens-1] - 'a' + 2;
        }
    }

    // build suffix array, lcp array, and sparse table
    int m = 28;
    int n = lens + lent + 1;
    da(r, n, m);
    calheight(r, n);
    for (int i = 0; i <= n; ++i) rmq[i] = ht[i];
    initrmq(n);

    // get closest (i.e., "having longest common prefix") suffix of S for each suffix of T
    vector<int> left(lent), right(lent);
    int lastfroms = -1;
    for (int i = 2; i <= n; ++i) {
        if (sa[i] < lens) {
            lastfroms = sa[i];
        } else if (sa[i] >= lens+1 && sa[i] <= lens+lent) {
            int sufidx = sa[i];
            left[sufidx-lens-1] = lastfroms;
        }
    }
    lastfroms = -1;
    for (int i = n; i >= 2; --i) {
        if (sa[i] < lens) {
            lastfroms = sa[i];
        } else if (sa[i] >= lens+1 && sa[i] <= lens+lent) {
            int sufidx = sa[i];
            right[sufidx-lens-1] = lastfroms;
        }
    }

    // iterate through suffixes of T
    int ans = 0;
    for (int i = 0; i < lent; ++i) {
        if (left[i] != -1) {
            // if the delimiters are different, which they should be, then we don't need to do this
            // additional checking, but i'm leaving it here commented out
            // int substrlen = min({lens-left[i], lent-i, lcp(i+lens+1, left[i])});
            // ans = max(ans, substrlen);

            ans = max(ans, lcp(i+lens+1, left[i]));
        }
        if (right[i] != -1) {
            ans = max(ans, lcp(i+lens+1, right[i]));
        }
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}
