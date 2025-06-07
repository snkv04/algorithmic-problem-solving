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
    ifstream cin("breedflip.in");
    ofstream cout("breedflip.out");

    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (s1[i] != s2[i] && (i == 0 || s1[i-1] == s2[i-1])) {
            ++ans;
        }
    }
    cout << ans << "\n";

    cin.close();
    cout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
