#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = 998244353;
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
    int pow[n];
    for (int i = 0; i < n; ++i) {
        if (i==0) pow[i] = 1;
        else {
            pow[i] = (2 * pow[i-1]) % MOD;
        }
    }

    int pmax=-1, pidx=-1, qmax=-1, qidx=-1;
    int p[n], q[n];
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> q[i];
    }

    for (int i = 0; i < n; ++i) {
        if (p[i] > pmax) {
            pmax = p[i];
            pidx = i;
        }
        if (q[i] > qmax) {
            qmax = q[i];
            qidx = i;
        }

        if (pmax > qmax) {
            cout << ((pow[pmax] + pow[q[i-pidx]]) % MOD) << " ";
        } else if (qmax > pmax) {
            cout << ((pow[qmax] + pow[p[i-qidx]]) % MOD) << " ";
        } else {
            if (q[i-pidx] > p[i-qidx]) {
                cout << ((pow[pmax] + pow[q[i-pidx]]) % MOD) << " ";
            } else {
                cout << ((pow[qmax] + pow[p[i-qidx]]) % MOD) << " ";
            }
        }
    }
    cout<<"\n";
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
