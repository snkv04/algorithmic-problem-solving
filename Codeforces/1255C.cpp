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

void add(array<int, 3> arr, map<pair<int, int>, set<int>> &other) {
    for (int i = 0; i < 3; ++i) {
        int a = -1, b = -1;
        for (int j = 0; j < 3; ++j) {
            if (j != i) {
                if (a == -1) a = arr[j];
                else b = arr[j];
            }
        }
        other[make_pair(min(a,b), max(a,b))].insert(arr[i]);
    }
}


void remove(array<int, 3> arr, map<pair<int, int>, set<int>> &other) {
    for (int i = 0; i < 3; ++i) {
        int a = -1, b = -1;
        for (int j = 0; j < 3; ++j) {
            if (j != i) {
                if (a == -1) a = arr[j];
                else b = arr[j];
            }
        }
        other[make_pair(min(a,b), max(a,b))].erase(arr[i]);
    }
}

pair<int, int> getpair(int a, int b) {
    if (a > b) swap(a, b);
    return make_pair(a, b);
}

void propagate(int inner, int outer, map<pair<int, int>, set<int>> &other, deque<int> &ans, bool right) {
    while (true) {
        auto p = getpair(inner, outer);
        if (other[p].empty()) {
            break;
        } else {
            int next = *other[p].begin();
            remove({inner, outer, next}, other);
            if (right) ans.push_back(next);
            else ans.push_front(next);
            inner = outer;
            outer = next;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    map<pair<int, int>, set<int>> other;
    for (int i = 1; i <= n - 2; ++i) {
        array<int, 3> arr;
        for (int j = 0; j < 3; ++j) cin >> arr[j];
        add(arr, other);
    }

    int i1 = -1, i2 = -1, o1 = -1, o2 = -1;
    for (int i = 1; i <= n && i1 == -1; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            auto p = make_pair(i, j);
            if (other[p].size() == 2) {
                i1 = i;
                i2 = j;
                o1 = *other[p].begin();
                o2 = *other[p].rbegin();
                break;
            }
        }
    }
    // guarantee that there's something on the left of o1 (basically, normalize/standardize our outer elements)
    if (other[getpair(o1, i1)].size() == 1 && other[getpair(o1, i2)].size() == 1) swap(o1, o2);
    // use the fact that there's something on the left to guarantee that i1 and i2 are ordered correctly
    if (other[getpair(o1, i1)].size() == 1) swap(i1, i2);

    deque<int> ans;
    ans.push_back(o1); ans.push_back(i1); ans.push_back(i2); ans.push_back(o2);
    remove({o1, i1, i2}, other);
    remove({i1, i2, o2}, other);
    propagate(i1, o1, other, ans, false);
    propagate(i2, o2, other, ans, true);
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    cout << "\n";
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
