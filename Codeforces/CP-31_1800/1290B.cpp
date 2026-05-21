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
    /*
    - problem:
        - let an "irreducible anagram" of a string s be an anagram of s, called t, such that it's impossible
        to find a partition of s into at least 2 parts where the corresponding stretches of t are each anagrams
        of the stretch from s
        - we are given a string and a bunch of queries, where a query specifies a substring; determine whether or
        not an irreducible anagram exists for each query's substring
    - solution:
        - first, notice that if an anagram t of string s is reducible, then we can simplify it into exactly 2 parts;
        then, we can redefine irreducibility as no prefix of t having the same multiset of characters as the
        corresponding prefix of s
        - then, we just find some rules to classify a substring as irreducible, and use prefix sums to check them:
            - if a substring has at least 3 distinct characters, then it has an irreducible anagram
                - how? place all instances of the third (or last) distinct character into t, then place all
                instances of the last character from s into t (if it's different from the third/last character,
                otherwise do nothing), and then place the remaining characters in ANY order. the order of the
                other characters doesn't matter, because the multiset of the prefixes of t won't match those of
                s, since s's prefix multiset won't have all instances of that last character until the end, while
                t's prefix multiset already has it much before.
            - if a substring has 2 distinct characters, then it has an irreducible anagram if the first and last
            character aren't the same, otherwise it doesn't
                - why? basically, if the first and last characters aren't matching, we can place all instances of
                the last character from s into t, and then put the other character, which works because the number
                of instances of that character won't match s until the prefix is the full string. if they are
                matching, then at a high level, the counts are forced to balance at some point in the middle
                of the string.
            - if a substring has only 1 distinct character, then it's obviously irreducible if the substring length
            is 1 (since you can't make 2 parts from it anyway), otherwise it isn't
    */

    // gets prefix sums for each character
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> pref(n + 1, vector<int>(26, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 26; ++j) {
            pref[i][j] += pref[i-1][j];
        }
        pref[i][s[i - 1] - 'a'] += 1;
    }

    // runs those rules in O(26) for each query
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        
        int distinct = 0;
        for (int i = 0; i < 26; ++i) if (pref[r][i] - pref[l - 1][i]) ++distinct;
        if (distinct == 1) {
            cout << ((r == l) ? "Yes" : "No") << '\n';
        } else if (distinct == 2) {
            if (s[r - 1] == s[l - 1]) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
            }
        } else {
            cout << "Yes\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
