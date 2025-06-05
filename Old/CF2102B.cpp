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
    int a1;
    cin >> a1;
    if (a1 < 0) a1 *= -1;
    int less = 0, greater = 0;
    for (int i = 1; i < n; ++i) {
        int ai;
        cin >> ai;
        if (ai < 0) ai *= -1;
        if (ai < a1) {
            ++less;
        } else {
            ++greater;
        }
    }

    // cout << "greater="<<greater<<", less="<<less<<'\n';
    if (greater < less - 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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
