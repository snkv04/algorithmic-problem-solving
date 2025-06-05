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
    int n, m;
    cin >> n >> m;
    string grid[n];
    for (int i = 0; i < n; ++i) cin >> grid[i];

    int down[n][m], right[n][m];
    for (int i = 0; i < n; ++i) {
        fill(down[i], down[i] + m, 0);
        fill(right[i], right[i] + m, 0);        
    }
    bool works = true;
    for (int i = 0; i < n && works; ++i) {
        for (int j = 0; j < m; ++j) {
            int last = i == 0 ? 0 : down[i-1][j];
            down[i][j] = last + (grid[i][j] == '1');
            last = j == 0 ? 0 : right[i][j-1];
            right[i][j] = last + (grid[i][j] == '1');

            if (grid[i][j] == '1' && down[i][j] != i+1 && right[i][j] != j+1) {
                works = false;
                break;
            }
        }
    }
    cout << (works ? "YES" : "NO") << "\n";
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
