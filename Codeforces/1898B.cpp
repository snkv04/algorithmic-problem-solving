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

// from https://leetcode.com/problems/minimum-replacements-to-sort-the-array/description/
class Solution {
public:
    long long minimumReplacement(vector<int>& nums) const {
        long long ans = 0, n = nums.size(), bound = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] > bound) {
                int ops = (nums[i] + bound - 1) / bound - 1;
                ans += ops;
                int spots = ops + 1;
                bound = nums[i] / spots;  // floor division
            } else {
                bound = nums[i];
            }
        }
        return ans;
    }
};

void solve(const Solution &solver) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    cout << solver.minimumReplacement(a) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution solver;
    int t = 1;
    cin >> t;
    while (t--) {
        solve(solver);
    }

    return 0;
}
