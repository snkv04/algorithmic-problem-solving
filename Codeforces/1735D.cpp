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

string getother(string a, string b) {
    stringstream ss;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == b[i]) {
            ss << a[i];
        } else {
            char c = '0';
            if (c == a[i] || c == b[i]) ++c;
            if (c == a[i] || c == b[i]) ++c;
            ss << c;
        }
    }
    return ss.str();
}

void solve() {
    /*
    - problem:
        - we have a set of N cards, each with K features, where any feature has 3 possible values.
        - we also have a condition that classifies a set of 3 cards as valid
        - our goal is to find the number of sets of 5 cards in which there's at least 2 sets of 3 cards
        that are valid
    - solution:
        - observe that 2 valid sets of 3 cards cannot overlap on more than a single card, so then
        a valid set of 3 cards is like a triangle and a target set of 5 cards (i.e., the type of set we
        are targeting) is like two triangles sharing a single point
        - then, we simply count the number of these double-triangle shapes by iterating over each possible
        center point and counting the number of quadruples that could work for the other 4 points
    - details:
        - important observations:
            - if we know what two cards are in a set, then the third card is fixed; as a result, if we think
            of each card as a point on a triangle, then two valid triangles cannot share an edge, only a point
            - so, if a set of 5 cards has 2 valid triangles, then they must share a point
            - also, as a result, a set of 5 cards cannot have more than 2 valid triangles, so the target sets
            that we are looking for will have exactly 2 valid sets of 3 cards
        - given those observations, we want to count the number of possible double-triangle shapes. formally,
        we want to count the number of unordered (a, b, c, d, e), where (a, b, c) and (c, d, e) are valid sets.
        we do this by:
            - counting, for any index c, the number of pairs of other indices (j, k) such that (c, j, k) is a
            valid triangle; this can be efficiently done in O(n^2) instead of O(n^3) by iterating over j and k
            and incrementing a count for c
            - noting that for any given c, no other configuration of (a, b, d, e) (outside of reordering (a, b)
            or (d, e)) will be valid, due to the above observation that triangles can't share a side. what this
            means for us is that all pairs ((a, b, c), (c, d, e)) will be such that a!=d and a!=e and b!=d and b!=e
            - then, for each c, counting the number of pairs of pairs we can take, by just using the C(c, 2) formula
            - in summary, for each possible center card, we initially count the number of pairs of cards where the
            3 make a triangle. then, for each possible center card, we count the number of pairs of pairs of cards,
            therefore counting the number of pairs of triangles centered there
    */
        
    int n, k;
    cin >> n >> k;
    vector<string> cards(n);
    set<string> st;
    for (int i = 0; i < n; ++i) {
        vector<int> card(k);
        cin >> card;

        stringstream ss;
        for (int feature : card) ss << feature;

        string str = ss.str();
        cards[i] = str;
        st.insert(str);
    }
    // cout << "cards = " << cards << endl;

    map<string, int> count;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            string othercard = getother(cards[i], cards[j]);
            if (st.find(othercard) != st.end()) {
                count[othercard] += 1;
            }
        }
    }
    
    ll ans = 0;
    for (auto entry : count) {
        ll cnt = entry.second;
        ans += (cnt * (cnt - 1)) / 2;
    }
    cout << ans << '\n';
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
