#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void solve() {
    int n;
    cin >> n;

    multiset<ll> xs, ys;
    ll x[n], y[n];
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        xs.insert(x[i]);
        ys.insert(y[i]);
    }
    if (n == 1) {
        cout << "1\n";
        return;
    }

    ll ans = 2e18;
    for (int i = 0; i < n; ++i) {
        xs.erase(xs.find(x[i]));
        ys.erase(ys.find(y[i]));
        ll area = ((*ys.rbegin()) - (*ys.begin()) + 1) * ((*xs.rbegin()) - (*xs.begin()) + 1);
        if (area > n-1) {
            ans = min(area, ans);
        } else {
            area += min((*ys.rbegin()) - (*ys.begin()) + 1, (*xs.rbegin()) - (*xs.begin()) + 1);
            ans = min(area, ans);
        }
        xs.insert(x[i]);
        ys.insert(y[i]);
    }
    cout << ans << "\n";
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
