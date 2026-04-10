#include <bits/stdc++.h>
// #include <random>
using namespace std;

using ll = long long;
using ull = unsigned long long;
const int MOD = (int) 1e9 + 7;

vector<vector<ll>> matmul(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    if (a[0].size() != b.size()) {
        throw invalid_argument("Invalid sizes");
    }

    int common = a[0].size();
    vector<vector<ll>> result(a.size(), vector<ll>(b[0].size(), 0));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            for (int k = 0; k < common; ++k) {
                result[i][j] += a[i][k] * b[k][j];
                if (result[i][j] > MOD) {
                    result[i][j] %= MOD;
                }
            }
        }
    }

    return result;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<ll>> a(n, vector<ll>(n, 0)), b(n, vector<ll>(n, 0)), c(n, vector<ll>(n, 0));
    for (int i = 0; i < 3 * n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < n) {
                cin >> a[i][j];
            } else if (i < 2*n) {
                cin >> b[i%n][j];
            } else {
                cin >> c[i%n][j];
            }
        }
    }

    // the seed defines the initial state of the random number generator
    ull seed = std::chrono::steady_clock::now().time_since_epoch().count();
    // the random number generator (the "engine") generates a stream of completely random integers,
    // which is typically used for getting a random integer by drawing the next one in the stream
    std::mt19937 rng(seed);
    // the distribution just defines the shape that we sample numbers from; to actually get a number,
    // we pass in the engine -> engine produces random number -> shape takes random number -> shape produces
    // sampled value
    std::uniform_int_distribution<int> dist(1, (int) 1e9);

    int tests = 25;
    for (int k = 1; k <= tests; ++k) {
        vector<vector<ll>> v(n, vector<ll>(1, 0));
        for (int i = 0; i < n; ++i) {
            v[i][0] = dist(rng);
        }

        vector<vector<ll>> bv = matmul(b, v);
        vector<vector<ll>> abv = matmul(a, bv);
        vector<vector<ll>> cv = matmul(c, v);
        for (int i = 0; i < n; ++i) {
            if (abv[i][0] != cv[i][0]) {
                cout << "NO" << '\n';
                return;
            }
        }
    }
    cout << "YES" << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}