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
        - we have a set of operations we can perform on an array with some limitations,
        and a property of the array that we care about
        - we want to find the maximum value we can obtain for that property using those operations within their limits
    - solution:
        - brute force over the whole search space of values for that property, and for each one, see if we can
        obtain that value using the given operations under their limitations
    - details:
        - first off, we care about the most efficient way of using the operations under their limitations:
            - note that if we were to split an element and then remove one part (or both parts) of the split to keep
            the GCD high, then we might as well have used one remove operation to eliminate the whole element
            - as a result, we don't need to worry about splitting then removing; for any element, we either split
            it or remove it
            - we also don't need to split an element multiple times; our goal is to make all elements divisible by
            some value G, so splitting it once gives us smaller numbers, or literally less options, for future splits
            to result in numbers divisible by G
        - now we need to find the max GCD. instead of finding the max GCD given the fixed array, or finding the max GCD
        given a fixed individual element, we can instead check each final GCD and see if we can make it.
            - how? we find the elements that are compatible with that final GCD (i.e., can be made to be divisible
            by that final GCD), trivially find the number of ones that aren't, and check if there are fewer than
            k ones that aren't.
        - how to check if an element is compatible with a final GCD value? how do we do it efficiently?
            - suppose we have a fixed G and we want to see what elements X can be "made to be divisible" by G. clearly,
            X = kG for any integer k will work. if X isn't divisible by G, then the remainder X%G needs to be placed into
            X_2 so then X_1 and X_3 are divisible by G. this gives us a few cases:
                - X < G: we can't even make one of the remaining X_i (where 1 <= i <= 3) divisible by G
                - G < X < 2G: we can only make one of the X_i divisble by G
                - 2G < X < 3G: we can make two X_i divisible by G, but the remainder will become the smallest (i.e., X_1),
                which means that the resulting numbers in our array aren't divisible by G
                - 3G < X < 4G: we can make two X_i divisible by G, but the remainder will be part of X_3, which again
                doesn't solve the problem
                - X > 4G: we can set X_1 = G, X_2 = G + X%G, and X_3 = G * ((X // G) -  2), which is always sufficient
                for the new numbers X_1 and X_3 to be divisible by G
            - so, for a fixed G, we can make all numbers X that are either >= 4G or in the set {G, 2G, 3G} divisible by G
            with only split operations, and the remaining ones have to be removed; the first set of numbers we can find
            with binary search, and the second set we can find with frequency counts
            - after we have the number of elements in our array that are compatible with G, the number of elements we have
            to remove is just n minus that number
    */

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;

    sort(a.begin(), a.end());
    map<int, int> freqs; for (int i = 0; i < n; ++i) freqs[a[i]] += 1;

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int l = 0, r = n - 1, idx = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (a[m] >= 4 * i) {
                idx = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        int cnt = idx == -1 ? 0 : n - idx;
        for (int multiple : vector<int>({i, 2*i, 3*i})) {
            if (freqs.find(multiple) != freqs.end()) {
                cnt += freqs[multiple];
            }
        }
        if (n - cnt <= k) {
            ans = i;
        }
    }
    cout << ans << '\n';
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
