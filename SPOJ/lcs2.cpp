#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 20, LOGMAXN = 25;
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
    vector<string> strs;
    string s;
    while (getline(cin, s)) {
        if (s.size() == 0) break;
        strs.push_back(s);
    }
    int n = strs.size();
    sort(strs.begin(), strs.end(), [](const string &a, const string &b) {return a.size() < b.size();});
    if (n == 1) {
        cout << strs[0].size() << endl;
        return;
    }

    // startidx[i] and endidx[i] say the indices in the concatenated string correspond to the
    // first character and delimiter of strs[i], respectively
    int delimiters = n;
    vector<int> startidx(n), endidx(n); // start inclusive, end exclusive, end is on delimiter
    int sumlengths = 0; // includes delimiters
    for (int i = 0; i < n; ++i) {
        startidx[i] = sumlengths;
        endidx[i] = sumlengths + strs[i].size();
        sumlengths += strs[i].size() + 1;
    }

    // place all of the strings into one string (with different delimiters) before building the suffix array
    int r[sumlengths];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < strs[i].size(); ++j) {
            int c = strs[i][j] - 'a' + delimiters;
            r[startidx[i] + j] = c;
        }
        r[startidx[i] + strs[i].size()] = i; // delimiter
    }
    int m = 26 + n; // accounts for all delimiters
    da(r, sumlengths - 1, m);
    calheight(r, sumlengths - 1);
    for (int i = 0; i < sumlengths; ++i) rmq[i] = ht[i];
    initrmq(sumlengths - 1);

    // for each suffix of the shortest string (strs[0]), which starts at index i of that string,
    // left[i][j] is such that across all indices of the concatenated string that correspond to
    // an index in strs[j], left[i][j] is the closest one to the left of the index corresponding
    // to index i in strs[0]; right[i][j] is analogous. in other words, left[i][j] and right[i][j]
    // say which 2 indices in the concatenated string that correspond to indices in strs[j] have the
    // longest common prefix with suffix i of strs[0]
    map<int, int> startidx_to_idx; for (int i = 0; i < n; ++i) startidx_to_idx[startidx[i]] = i;
    vector<vector<int>> left(strs[0].size(), vector<int>(n, -1)), right(strs[0].size(), vector<int>(n, -1));
    vector<int> last(n, -1);
    for (int i = 0; i < sumlengths; ++i) {
        int suf = sa[i];
        auto it = startidx_to_idx.upper_bound(suf);
        --it;
        int stridx = it->second;
        if (suf >= startidx[stridx] && suf < endidx[stridx]) { // not a delimiter
            if (stridx == 0) {
                for (int j = 1; j < n; ++j) {
                    left[suf-startidx[0]][j] = last[j];
                }
            } else {
                last[stridx] = suf;
            }
        }
    }
    last = vector<int>(n, -1);
    for (int i = sumlengths-1; i >= 0; --i) {
        int suf = sa[i];
        auto it = startidx_to_idx.upper_bound(suf);
        --it;
        int stridx = it->second;
        if (suf >= startidx[stridx] && suf < endidx[stridx]) { // not a delimiter
            if (stridx == 0) {
                for (int j = 1; j < n; ++j) {
                    right[suf-startidx[0]][j] = last[j];
                }
            } else {
                last[stridx] = suf;
            }
        }
    }

    // iterate through all suffixes of strs[0] and find the LCP of that suffix with all other strings
    int ans = 0;
    for (int i = 0; i < strs[0].size(); ++i) {
        int common_with_all = 1e9;
        for (int j = 1; j < n; ++j) {
            int best = 0;
            if (left[i][j] != -1) {
                best = max(best, lcp(i, left[i][j]));
            }
            if (right[i][j] != -1) {
                best = max(best, lcp(i, right[i][j]));
            }
            common_with_all = min(common_with_all, best);
        }

        ans = max(ans, common_with_all);
    }
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}
