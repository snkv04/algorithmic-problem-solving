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

ll sqrt(ll n) {
    // calculates the floor of sqrt(n) in O(log(n))
    if (n == 0) return 0;
    else if (n < 0) return -1;
    ll l = 1, r = n, sqrt = -1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll factor = n / mid;
        if (mid <= factor) {
            sqrt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return sqrt;
}

void solve() {
    string s;
    cin >> s;
    ll n = stoll(s);
    ll r = sqrt(n);
    if (r * r == n) {
        cout << "0 " << r << "\n";
    } else {
        cout << "-1\n";
    }
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
