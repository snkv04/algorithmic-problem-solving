#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

void solve() {
    vector<int> counts(3);
    cin >> counts;
    string rgb = "RGB";

    int ansi = -1, ansj = -1, cntij = -1, ansk = -1, maxlen = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == j) continue;

            for (int len = 0; len <= min(counts[i], counts[j]); ++len) {
                vector<int> newcnts = counts;
                newcnts[i] -= len;
                newcnts[j] -= len;

                int k = 3 - i - j;  // just a formula to get the other idx
                int lenkj = 0, lenki = 0;
                lenkj = min(newcnts[j], newcnts[k]);
                newcnts[j] -= lenkj;
                newcnts[k] -= lenkj;
                if (lenkj) {  // to have the ki segment, we need at least one instance of kj in the middle
                    lenki = min(newcnts[i], newcnts[k]);
                    newcnts[i] -= lenki;
                    newcnts[k] -= lenki;
                }

                int total = 2 * (len + lenkj + lenki);
                if (newcnts[k]) total += 1;
                // cout << "total = " << total << endl;
                if (total > maxlen) {
                    ansi = i;
                    ansj = j;
                    ansk = k;
                    cntij = len;
                    maxlen = total;
                }
            }
        }
    }
    // cout << ansi << " " << ansj << " " << cntij << " " << ansk << "\n";

    // builds the string according to the best formula
    stringstream ss;
    while (cntij--) {
        ss << rgb[ansi] << rgb[ansj];
        --counts[ansi];
        --counts[ansj];
    }
    int lenkj = 0, lenki = 0;
    lenkj = min(counts[ansj], counts[ansk]);
    counts[ansj] -= lenkj;
    counts[ansk] -= lenkj;
    if (lenkj) {  // to have the ki segment, we need at least one instance of kj in the middle
        lenki = min(counts[ansi], counts[ansk]);
        counts[ansi] -= lenki;
        counts[ansk] -= lenki;
    }
    while (lenkj--) {
        ss << rgb[ansk] << rgb[ansj];
    }
    while (lenki--) {
        ss << rgb[ansk] << rgb[ansi];
    }
    if (counts[ansk]) {
        ss << rgb[ansk];
    }
    cout << ss.str() << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
