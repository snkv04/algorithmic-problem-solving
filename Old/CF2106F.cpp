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

void gen(string s) {
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) cout << ((s[j] - '0') ^ 1);
            else cout << s[j];
        }
        cout << "\n";
    }
}

void solve() {
    /*
    1001
    0101
    0011
    0000

    0011001
    1111001
    1001001
    1010001
    1011101
    1011011
    1011000

    0010
    0010
    0010
    0010

    1010
    0110
    0000
    0011


    01000010
    */

    int n;
    cin >> n;
    string s;
    cin >> s;

    // basically, keeps track of the contiguous areas on the top and bottom,
    // setting to 0 if it gets cut off and merging the prev bottom area to
    // the curr top area if there's that 0 bridging through the 1s, making
    // sure that all merges/bridges are automatically handled by top (either
    // if the bottom pokes through the right side with a 0, or if the top 
    // pokes through from the left with a 0, where the first case is explicitly
    // handled with the second branch below while the second case is automatically
    // handled with the way each top area value draws from the previous one)
    ll lasttop = 0, lastbottom = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        ll currtop = 0, currbottom = 0;
        if (s[i] == '0') { // continues the triangle/trapezoid
            currtop = lasttop + i;
            currbottom = lastbottom + n - i - 1;
        } else {
            currtop = lastbottom + 1;
        }
        ans = max(ans, max(currtop, currbottom));
        lasttop = currtop;
        lastbottom = currbottom;
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
