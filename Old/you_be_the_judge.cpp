#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (!(n % i)) {
            return false;
        }
    }
    return true;
}

void solve() {
    vector<string> tokens;
    string s;
    while (getline(cin, s)) {
        stringstream ss(s);
        string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
    }

    if (tokens.size() != 3) {
        cout << "0\n";
        return;
    }

    int a[3];
    for (int i = 0; i < 3; ++i) {
        try {
            a[i] = stoi(tokens[i]);
        } catch (...) {
            cout << "0\n";
            return;
        }

        if (tokens[i][0] == '0' || tokens[i][0] == '+' || tokens[i][0] == '-') {
            cout << "0\n";
            return;
        }
    }

    if (a[0] > 3 && a[0] <= 1e9 && !(a[0] % 2) && a[1] >= 2 && is_prime(a[1]) && a[2] >= 2 && is_prime(a[2]) && a[0] == a[1] + a[2]) {
        cout << "1\n";
    } else {
        cout << "0\n";
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
