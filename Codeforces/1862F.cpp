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
    ll w, f, sum = 0;
    cin >> w >> f;
    int n;
    cin >> n;
    vector<ll> s;
    for (int i = 0; i < n; ++i) {
        ll si;
        cin >> si;
        s.push_back(si);
        sum += si;
    }

    vector<bool> mem(sum+1, false);
    mem[0] = true;
    for (int si : s) {
        for (int i = sum; i >= si; --i) {
            mem[i] = mem[i] || mem[i-si];
        }
    }

    ll ans = 1e9;
    for (int i = 0; i <= sum; ++i) {
        if (!mem[i]) continue;

        ll needforwater = (i+w-1)/w, needforfire = (sum-i+f-1)/f;
        ans = min(ans, max(needforwater, needforfire));
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
