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
    // reads in all cats, and sorts them by left bound
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> cats(m);
    for (int i = 0; i < m; ++i) {
        cin >> cats[i].first >> cats[i].second;
    }
    sort(cats.begin(), cats.end());

    // iterates through timesteps, keeping track of cats overlapping each timestep
    int cat_idx = 0, curr_cats = 0;
    map<int, int> left_counts;
    map<int, vector<int>> right_to_lefts;
    vector<int> mem(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        // adds in all cats whose left bound is equal to i
        while (cat_idx < m && cats[cat_idx].first == i) {
            auto [l, r] = cats[cat_idx++];
            right_to_lefts[r].push_back(l);
            left_counts[l] += 1;
            curr_cats += 1;
        }

        // removes all cats whose right bound is to the left of i
        while (right_to_lefts.size() && right_to_lefts.begin()->first < i) {
            for (auto l : right_to_lefts.begin()->second) {
                left_counts[l] -= 1;
                if (!left_counts[l]) left_counts.erase(l);
                curr_cats -= 1;
            }
            right_to_lefts.erase(right_to_lefts.begin());
        }

        // either (don't do anything) or (feed all cats at current timestep and take best
        // mem value to the left of the leftmost cat that overlaps the current timestep)
        mem[i] = mem[i - 1];
        if (left_counts.size()) {
            mem[i] = max(mem[i], curr_cats + mem[left_counts.begin()->first - 1]);
        }
    }
    cout << mem[n] << endl;
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
