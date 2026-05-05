#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
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

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
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
    - interesting ideas:
        - if multiple operations seem optimal after a first check, always perform the operation that allows
        as many options as possible in the future. here, that means that if we're going to leave out an
        index from getting a bit, then we should leave out one of the "equal" ones, so that it gets turned
        into a "less" index and we can do whatever we want with it from then on.
        - the general less/greater than idea:
            - suppose we have a number and a bound. we can perform operations on the number, but can't perform
            operations on the bound.
            - now, let's move from the MSB to LSB, and perform operations on our number. let's call the bits
            already processed the "high bits", and the bits to process the "low bits". there are 3 cases:
                - on the high bits, our number is equal to the bound.
                    - our current bit can either tip the scales, moving us into one of the below 2 cases for
                    all future bits, or keep the number equal to the bound, keeping us in this case for the
                    next bit
                - on the high bits, our number is less than the bound
                    - no matter what we do on the remaining bits, the number will remain less than the bound,
                    because a single higher bit matters more than all lower bits combined
                - on the high bits, our number is greater than the bound:
                    - no matter what we do on the remaining bits, the number will remain greater than the bound,
                    because a single higher bit matters more than all lower bits combined
        - the resulting loose/tight strategy:
            - we cannot have any value exceed n
            - suppose we are moving from MSB to LSB. if an element is equal to n, then we can't place a bit
            where n doesn't have it, while if it's less than n, we can place a bit anywhere
            - so, we can keep track of the indices whose values are equal to n, and the indices whose values
            are less than n.
                - keep in mind k is assumed to be even
                - if, on a bit, n has that bit activated, we want to activate an odd number of indices. k-1 is
                best, and it works for all (equal + less) indices, because n has it activated. then, one of the
                k indices cannot activate that bit (so we meet the XOR constraint), so try to make that index an
                "equal" one (so it BECOMES a "less" one).
                - if, on a bit, n doesn't have that bit activated, then we need to activate an even number of
                indices. we cannot activate it on indices whose values are equal to n, because that will make them
                greater than n. so, we only activate it on an even number of indices in the "less" category.
        - why doesn't the greedy strategy work (set first k-2 elems to n, fill in bits greedily for last
        2 elems)?
            - it is, in a literal sense, just a less optimal version of the full loose/tight strategy. namely,
            we fill in k-2 indices with n, and then we run the loose/tight strategy only on those last 2 elements
            INSTEAD of on all elements.
            - for all bits where n is 1, it gives the same result: k - 1 indices are turned on at that bit.
            - for all bits where n is 0, we literally just give ourselves fewer indices to turn that bit on,
            because we'll only ever turn it on in the last 2 indices (once we've moved both elements to the
            "less" pile) instead of in more indices.
    */

    int n, k;
    cin >> n >> k;
    if (k % 2) {
        while (k--) {
            cout << n << " ";
        }
        cout << "\n";
        return;
    }

    vector<int> equal, less;
    for (int i = 0; i < k; ++i) equal.push_back(i);
    vector<int> ans(k, 0);
    for (int b = 30; b >= 0; --b) {
        if ((n >> b) & 1) {
            int in_less = min(k - 1, (int) less.size()), in_equal = k - 1 - in_less;
            for (int i = 0; i < in_less; ++i) {
                ans[less[i]] += 1 << b;
            }
            for (int i = 0; i < in_equal; ++i) {
                ans[equal[i]] += 1 << b;
            }
            if (equal.size()) {
                less.push_back(equal.back());
                equal.pop_back();
            }
        } else {
            for (int i = 0; i < less.size() / 2 * 2; ++i) {
                ans[less[i]] += 1 << b;
            }
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
