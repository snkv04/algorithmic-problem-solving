#include <iostream>
#include <set>

using namespace std;

void solve() {
    int n;
    cin >> n;
    multiset<int> ls, rs;
    while (n--) {
        char c;
        int l, r;
        cin >> c >> l >> r;
        if (c == '+') {
            ls.insert(l);
            rs.insert(r);
        } else {
            ls.erase(ls.find(l));
            rs.erase(rs.find(r));
        }
        cout << (ls.size() && rs.size() && *(ls.rbegin()) > *(rs.begin()) ? "YES" : "NO") << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}