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

ll xor_0_to_x(ll x) {
    ll rem = x % 4;
    switch (rem) {
        case 0:
            return x;
        case 1:
            return 1;
        case 2:
            return x + 1;
        case 3:
            return 0;
        default:
            throw std::logic_error("what?");
    }
}

ll xor_range(ll l, ll r) {
    return xor_0_to_x(r) ^ (l > 0 ? xor_0_to_x(l - 1) : 0);
}

ll xor_spaced(ll l, ll r, ll i, ll k) {
    if (r < k) return 0;

    ll min_id = (l - k + ((1LL << i) - 1)) / (1LL << i);  // will always have a multiple of 2^i >= l - k
    ll max_id = (r - k) / (1LL << i);  // need to ensure that we have a multiple of 2^i >= r - k, hence the check above

    ll high_bits_of_xor = xor_range(min_id, max_id) << i;
    ll low_bits_of_xor = ((max_id - min_id + 1) % 2) ? k : 0;  // same as if we used parity as indicator var. then mult. by k

    ll result = high_bits_of_xor + low_bits_of_xor;
    return result;
}

void solve() {
    /*
    - problem:
        - given some (l, r, i, k), find the XOR of all integers i where i is in the interval [l, r] and
        i is not congruent to k mod 2^i
    - solution:
        - straightforwardly, we can separate it out into XOR(l, r) and the XOR of the integers x where x IS congruent
        to k mod 2^i, and XOR them together, because the XOR operation is its own inverse operation
        - for XOR(l, r):
            - we can use the a nice closed-form formula for XOR(0, n) based on n % 4
            - then, we pretty much just apply the prefix XOR sum formula: take prefix up to right, and cancel out
            stuff before left
        - for XOR(l, r, i, k):
            - first, to be clear, we intend to take XOR of all elements in the set {x : l <= x <= r and x = k (mod 2^i)}
            - remember that XOR is a bitwise operation, meaning we can separate out the results from different bits
            and sum them together to get the total result
            - so, we can take the sum of XOR(l, r, i, k, lower bits) and XOR(l, r, i, k, higher bits). BOTH of these
            require knowing the shape of the set (i.e., the count and bounds). so do that first.
            - how to find the bounds (min and max element) of the set of possible x?
                - we want to find the minimum x such that x = 2^i * c + k and x >= l. if we solve for c, then we have
                x. think of c as the ID of x. observe that this is the same as finding the minimum c such that
                2^i * c >= l - k. easily doable with ceiling division, since it's just a multiple of 2^i.
                - we also want to find the maximum x such that x = 2^i * c + k <= r. floor division is even easier.
            - for XOR(l, r, i, k, lower bits):
                - the lower bits are the same, the higher bits differ across all x. so, once we know how many x exist,
                then our result is k if that count is odd, and 0 if that count is even.
                - we can easily find that count once we know the min and max element, which is described above.
            - for XOR(l, r, i, k, higher bits):
                - once we have the min and max elements, observe that we can bit-shift them to the right, and all such
                x are now consecutive (i.e., spaced by 1 instead of spaced by 2^i). then, we can just use the range
                XOR formula again, and bit-shift our values back to the left.
    - useful ideas for the future:
        - we can take a target set or target quantity, separate it out into parts, and then find a pattern in those
        parts separately. in this problem, the pattern among all x for the lower bits is that those bits are equal.
        the pattern among all x for the higher bits is that those bits, if shifted right, represent consecutive numbers.
        - be careful about what your assumptions are. if you assume that you have some value <= r meeting some conditions,
        then check that. if you assume that you haev some value >= l meeting some conditions, then check that.
        - it's useful to think about the concept of "trying to understand the properties of something" as "trying to
        understand its shape". a lot of problem-solving is just understanding the "shape" of the objects of interest
        in the problem. this is only even worth writing down at all because it simplifies a major thought process by
        identifying it with a simple name.
        - can divide evenly-spaced elements by their space to make them consecutive. here, we make the x consecutive by
        shifting them to the right, taking the range XOR (that's why we made them consecutive), then shift back to the
        left.
    */

    ll l, r, i, k;
    cin >> l >> r >> i >> k;
    
    ll xor_all = xor_range(l, r);
    ll xor_uninteresting = xor_spaced(l, r, i, k);
    ll xor_interesting = xor_all ^ xor_uninteresting;
    cout << xor_interesting << endl;
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
