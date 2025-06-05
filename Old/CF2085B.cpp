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
    int a[n];
    bool zero = false;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (!a[i]) {
            zero = true;
        }
    }

    if (!zero) {
        cout << "1\n1 " << n << "\n"; 
    } else {
        bool firstpart = a[0] == 0 || a[1] == 0;
        bool secondpart = false;
        for (int i = 2; i < n; ++i) secondpart = secondpart || (a[i] == 0);
        vector<pair<int, int>> ops;
        int size = n;
        if (secondpart) {
            ops.push_back(make_pair(3, n));
            size = 3;
        }
        if (firstpart) {
            ops.push_back(make_pair(1, 2));
            size -= 1;
        }
        ops.push_back(make_pair(1, size));
        cout << ops.size() << '\n';
        for (auto p : ops) {
            cout << p.first << " " << p.second << "\n";
        }
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
