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
    vector<int> a;
    int last = -1;
    for (int i= 0; i < n; ++i) {
        int ai;
        cin >> ai;
        if (last != ai) {
            a.push_back(ai);
        }
        last = ai;
    }
    n = a.size();

    int ans = 0, count = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || a[i] == a[i-1] + 1) {
            ++count;
        } else {
            count = 1;
        }

        if (i == n-1 || a[i] < a[i+1]-1) {
            ans += (count+1)/2;
        }
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
