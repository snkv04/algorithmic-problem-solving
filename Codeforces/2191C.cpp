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
    - if the string is already sorted, then clearly Alice cannot win
    - if it isn't, the immediate first question is, can Alice use a trivial strategy, meaning that she
    wins in one move? the answer is yes, and the thought process ends there.
        - to win in one move, recognize that we need to select some indices corresponding to a group
        of 1s on the left then a group of 0s on the right. if we select all of the elements that aren't
        where they should be in the final arrangement, then 2 problems are solved at once:
        (1) the elements that don't need to move don't move, and the elements that do need to move will move
        (and note that they will in fact all move since there's an even distribution of 0s and 1s among this
        misplaced group). in other words, if we are able to make this move, then the entire array will be sorted
        immediately after.
        (2) since the final arrangement has 0s to the left and 1s to the right and we only pick
        elements that don't align with that final arrangement, the elements that we'll pick will have 1s to
        the left and 0s to the right. in other words, we are able to make this move.
    */

    int n;
    cin >> n;
    string s, t;
    cin >> s;
    t = s;
    sort(t.begin(), t.end());

    vector<int> misplaced;
    for (int i = 0; i < n; ++i) {
        if (s[i] != t[i]) misplaced.push_back(i+1);
    }

    if (misplaced.size()) {
        cout << "Alice\n";
        cout << misplaced.size() << "\n";
        for (int i : misplaced) cout << i << " ";
        cout << "\n";
    } else {
        cout << "Bob\n";
    }
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
