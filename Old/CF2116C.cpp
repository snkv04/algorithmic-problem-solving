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

int gcd(int a, int b) {
    int A = max(a, b), B = min(a, b);
    while (B != 0) {
        int r = A % B;
        A = B;
        B = r;
    }
    return A;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n, 0); for (int i = 0; i < n; ++i) cin >> a[i];
    int mn = a[0];
    for (int i = 1; i < n; ++i) {
        mn = gcd(mn, a[i]);
    }

    bool eql = false;
    for (int i = 0 ;i < n; ++i) {
        if (a[i] == mn) {
            eql = true;
            break;
        }
    }
    
    if (eql) {
        int ans = 0;
        for (int i = 0; i < n; ++i) if (a[i] != mn) ++ans;
        cout << ans << "\n";
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = a[i] / mn;
        }
        // cout <<"mn ="<< mn << endl;
        // print_container(a, "after dividing, a = ");

        int ans = 0;
        while (true) {
            int mini=-1, minj=-1, mn = 1e9;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < i; ++j) {
                    int g = gcd(a[i], a[j]);
                    if (g < mn) {
                        mn = g;
                        mini = i;
                        minj = j;
                    }
                }

            }

            if (a[mini] > a[minj]) {
                a[mini] = mn;
            } else {
                a[minj] = mn;
            }

            ++ans;
            // print_container(a, "a = ");
            if (mn == 1) {
                break;
            }
        }
        cout << ans + n - 1 << "\n";
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
