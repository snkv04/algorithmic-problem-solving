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
        - we have an array where no value is equal to a given value x
        - find the minimum possible number of segments we can break the array into such that no segment
        has a subset whose product is equal to x
    - solution:
        - greedily start new segments as late as possible, because starting a new segment later is always
        better than starting it earlier (since there will literally just be fewer possible products to make)
        - now, keep track of the subset products we can make only using the elements in the current segment
        with knapsack DP, and start a segment once the knapsack reveals that making x is possible
            - the knapsack only needs to tell us if the divisors of x are possible, because any non-divisor
            of x can't be used as part of a subset whose product is equal to x; there are O(sqrt(x)) divisors,
            so this solution runs in O(n * sqrt(x)), or O(n * sqrt(x) * log(sqrt(x))) based on the implementation
    - details:
        - one way to represent all possible factors of x is through the set of possible exponent tuples corresponding
        to the prime factors of x. there will still be O(sqrt(x)) of such tuples, because they still each represent
        a valid divisor of x, but this is much harder to implement. i don't know why this is the first thing
        i thought of. instead, we can store the divisors of x directly. for the future, when thinking about products
        of numbers equalling another number, think both of prime factorizations and of divisors
    */

    // reads in input
    ll n, x;
    cin >> n >> x;

    // precomputes divisors of x
    set<ll> divisors;
    for (int i = 1; i <= x; ++i) if (x % i == 0) divisors.insert(i);

    // iterates through each element, storing the possible subsets for the current segment
    set<ll> possible;
    possible.insert(1);
    int ans = 1;
    while (n--) {
        // reads in the element
        ll a_i;
        cin >> a_i;

        // if a_i is a divisor of x, then places all new possible-to-produce products (of subsets
        // of the segment) into the knapsack
        if (divisors.find(a_i) != divisors.end()) {
            ll curr = *possible.rbegin();
            while (true) {
                if (divisors.find(curr * a_i) != divisors.end()) {
                    possible.insert(curr * a_i);
                }

                auto it = possible.lower_bound(curr);
                if (it == possible.begin()) {
                    break;
                } else {
                    --it;
                    curr = *it;
                }
            }
        }

        // if x is now a possible product, then greedily start a new segment with only this element
        if (possible.find(x) != possible.end()) {
            ++ans;
            possible.clear();
            possible.insert(1);
            possible.insert(a_i);
        }
    }
    cout << ans << endl;
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
