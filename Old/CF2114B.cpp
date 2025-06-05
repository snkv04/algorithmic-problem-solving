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
    int n, k;
    string s;
    cin >> n >> k >> s;
    int a = 0, b = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') ++a;
        else ++b;
    }
    if (a > b) swap(a, b);

    int mn = (b-a)/2, mx = (b % 2) ? (n/2 - 1) : n/2;
    cout << ((mn <= k && k <= mx && (k%2 == mn%2)) ? "YES" : "NO") << "\n";
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
