#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int n, k, ans;
vector<int> a;

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

bool check(int threshold) {
    vector<int> pre(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + (a[i - 1] >= threshold ? 1 : -1);
    }

    ll bestlval = 1e18, bestl = -1;
    for (int i = k; i <= n; ++i) {
        if (pre[i - k] < bestlval) {
            bestlval = pre[i - k];
            bestl = i - k + 1;
        }

        if (pre[i] > bestlval) {
            ans = threshold;
            return true;
        }
    }
    return false;
}

void solve() {
    // almost same exact code as https://codeforces.com/contest/2128/problem/E1

    cin >> n >> k;
    a = vector<int>(n);
    cin >> a;

    int lo = 1, hi = n;
    ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
