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
    int n, q;
    cin >> n >> q;
    int c[n]; for (int i = 0; i < n; ++i) cin >> c[i];
    int queries[q][3];
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> queries[i][j];
            queries[i][j]--;
        }
    }

    for (int i = q-1; i >= 0; --i) {
        int x=queries[i][0], y=queries[i][1], z=queries[i][2];
        if (z != x && z != y) {
            if (x == y) {
                if (c[x] == -1) {
                    c[x] = c[z];
                } else if (c[z] == -1) {
                    c[z] = c[x];
                } else {
                    if (c[z] != c[x]) {
                        cout << "-1\n";
                        return;
                    } else {
                        // all good
                    }
                }
            } else {
                //
            }
            if (c[z] = min(c[x], c[y])) {
                c[z] = -1;
            } else {
                cout << "-1\n";
                return;
            }
        } else { // z in [x, y]
            if (x == y) {
                // nothing to do
            } else {
                if (z == y) {
                    swap(x, y);
                }
                // z == x, x != y
                if (c[x] == -1 && c[y] == -1) {
                    
                } else if (c[x] == -1) {
                    //
                } else if (c[y] == -1) {
                    //
                } else {
                    //
                }
            }
        }
    }
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
