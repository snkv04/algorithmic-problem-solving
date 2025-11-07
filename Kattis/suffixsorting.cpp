#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5, MAXM = 62, LOGMAXN = 25;
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

void initrmq(int n) {
    int i, j, a, b;
    for (mm[0] = -1, i = 1; i <= n; ++i)
        mm[i] = ((i & (i-1)) == 0) ? mm[i-1] + 1 : mm[i-1];
    for (i = 1; i <= n; ++i)
        best[0][i] = i;
    for (i = 1; i <= mm[n]; ++i)
        for (j = 1; j <= n + 1 - (1 << i); ++j) {
            a = best[i-1][j];
            b = best[i-1][j + (1 << (i-1))];
            if (RMQ[a] < RMQ[b]) best[i][j] = a;
            else best[i][j] = b;
        }
    return;
}

int askrmq(int a, int b) {
    int t;
    t = mm[b-a+1];
    b -= (1 << t)  - 1;
    a = best[t][a];
    b = best[t][b];
    return RMQ[a] < RMQ[b] ? a : b;
}

int lcp(int a, int b, int *ht, int *rk) {
    int t;
    a = rk[a];
    b = rk[b];
    if (a > b) swap(a, b);
    return ht[askrmq(a+1, b)];
}

void solve() {
    /*
    implementation note: be careful about the range of possible characters. all characters of the
    string must be within the inclusive interval [1, MAXN-1], so that the sentinel character can
    be 0, so we need to make sure that (1) MAXN is large enough, and (2) the ASCII codes of the
    input characters are properly mapped to this range.
    */

    string s;
    while (getline(cin, s)) {
        int n = s.size();
        if (!n) break;
        int r[n+1];
        for (int i = 0; i < n; ++i) {
            r[i] = s[i];
        }
        r[n] = 0;

        int sa[n+1];
        da(r, sa, n, 260);

        int q;
        cin >> q;
        while (q--) {
            int qi;
            cin >> qi;
            cout << sa[qi+1] << " ";
        }
        cout << endl;
        getline(cin, s);
    }
}

int main() {
    solve();
    return 0;
}
