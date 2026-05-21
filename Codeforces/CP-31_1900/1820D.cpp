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
std::istream& operator>>(std::istream &is, std::pair<T, T> &p) {
    is >> p.first >> p.second;
    return is;
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

struct ByH {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first != b.first) {
            return a.first > b.first;
        } else {
            return a.second < b.second;
        }
    }
};

struct ByW {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        if (a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first < b.first;
        }
    }
};

pair<multiset<pair<int, int>, ByH>, multiset<pair<int, int>, ByW>> build(vector<pair<int, int>> &rectangles) {
    multiset<pair<int, int>, ByH> h;
    multiset<pair<int, int>, ByW> w;
    for (auto r : rectangles) {
        h.insert(r);
        w.insert(r);
    }
    return make_pair(h, w);
}

bool check(ll height, ll width, multiset<pair<int, int>, ByH> &h, multiset<pair<int, int>, ByW> &w) {
    while (true) {
        if (h.size() == 1) {
            // ensure that last block is of expected shape
            return h.begin()->first == height && h.begin()->second == width;
        }

        int maxh = h.begin()->first, maxw = w.begin()->second;
        if (maxh > height || maxw > width) {
            // remaining blocks don't fit in expected rectangle
            return false;
        } else if (maxh < height && maxw < width) {
            // remaining blocks are too small for expected rectangle
            return false;
        } else {
            // at least one of (block exists to make vertical cut with) and (block exists to make horizontal cut with)
            // is met. why is taking any such rectangle fine?
            // - if it is true that the remaining rectangles fit into a rectangle with the expected height and width,
            // and it's also true that there's a rectangle whose height is equal to the expected total height, then we
            // can place that rectangle on the left, cut it off with a vertical cut, and we are guaranteed to be able
            // to fit the rest into the new expected rectangle. if we couldn't do so, then such a rectangle with such
            // height wouldn't exist anyway.
            // - if it is not true that the remaining rectangles fit into a rectangle with the expected height and width,
            // then we will encounter that problem eventually anyway. specifically, removing such a rectangle (whose
            // height is equal to the expected total height) will not take away that property. if it did, then that means
            // we actually COULD fit everything into the expected rectangle, which is a contradiction.
            // so, in both cases, taking the rectangle whose height is equal to the expected total height (since one exists)
            // and cutting it off is the optimal (not suboptimal) step to take. the same logic holds for a horizontal cut.
            if (maxh == height) {
                // if both maxh == height and maxw == width, then our largest block is a square and it doesn't
                // matter which direction we make the cut in, so we arbitrarily assume we're making a vertical cut

                auto r = *h.begin();
                h.erase(h.find(r));
                w.erase(w.find(r));
                width -= r.second;
            } else {
                assert(maxw == width);

                auto r = *w.begin();
                h.erase(h.find(r));
                w.erase(w.find(r));
                height -= r.first;
            }
        }
    }
}

void solve() {
    /*
    - useful ideas for the future:
        - consider all possible cases (!). and when you consider a case, try your best to think of a concrete example
        of how that case could occur, because that makes reasoning about that case a lot easier and clearer.
    */

    // reads in the rectangles
    int n;
    cin >> n;
    vector<pair<int, int>> rectangles(n);
    cin >> rectangles;
    if (n == 1) {
        cout << "1\n";
        cout << rectangles[0].first << ' ' << rectangles[0].second << '\n';
        return;
    }

    // finds the area (which is used for checking valid heights/widths at the beginning)
    ll area = 0;
    for (auto [a, b] : rectangles) area += 1LL * a * b;

    // tries an initial vertical cut then an initial horizontal cut.
    // once we make the assumption of which cut went first, then we can take the max-height/max-width rectangle,
    // and determine both our h and w. then, we just check that (h, w) pair.
    set<pair<ll, ll>> ans;
    auto [h, w] = build(rectangles);
    if (area % h.begin()->first == 0) {
        ll height = h.begin()->first;
        ll width = area / height;
        if (check(height, width, h, w)) {
            ans.insert(make_pair(height, width));
        }
    }
    auto p = build(rectangles);
    h = p.first; w = p.second;
    if (area % w.begin()->second == 0) {
        ll width = w.begin()->second;
        ll height = area / width;
        if (check(height, width, h, w)) {
            ans.insert(make_pair(height, width));
        }
    }

    // collects the <= 2 possible (h, w) pairs
    cout << ans.size() << endl;
    for (auto [height, width] : ans) cout << height << ' ' << width << endl;
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
