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
    int cnt[30];
    fill(cnt, cnt+30, 0);
    int a[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        for (int j = 0; j < 30; ++j) {
            if ((a[i] & (1 << j)) > 0) {
                cnt[j] += 1;
            }
        }
    }
    // for (int j = 0; j < 30; ++j) {
    //     cout << "cnt[" << j << "] = " << cnt[j] << "\n";
    // }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j < 30; ++j) {
            if ((a[i] & (1 << j))) {
                sum += (ll) (n - cnt[j]) * (1LL << j);
            } else {
                sum += (ll) (cnt[j]) * (1LL << j);
            }
        }
        ans = max(ans, sum);
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
