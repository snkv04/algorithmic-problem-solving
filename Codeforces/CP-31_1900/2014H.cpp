#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
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

void solve(vector<ull> &rand_val) {
    /*
    - immediately intuitive solution is to take XOR using prefix sums to check if all elements have an even
    frequency.
    - this doesn't work, though, because of cases like [3, 3, 3, 2, 1] where different integers cancel each
    other out without all having even frequency. in simpler terms, the input numbers can be chosen so that
    the numbers cancel others out, and we'd perceive all frequencies to be even when they're not. it's a
    collision problem: 2 numbers can have their XOR be a third number, and then we're cooked.
    - to avoid the collision problem, where the inputs can be carefully chosen so that the bits of different
    numbers align just right for us to fail, we literally just map each number to a random value. then, the
    input numbers cannot be carefully chosen, because each input a_i has a random (but fixed) bit pattern.
    lol? that's it i guess.
    - in short: to avoid carefully chosen inputs causing our worst case, we just randomize the input so that
    we can apply our strategy without worrying about the worst case. the collision probability is super low.
    formally, the probability that we have 3 numbers in the input X, Y, and Z such that XOR(X, Y) == Z and all
    three of them are in a subarray [l, r] and at least one of them doesn't have an even frequency is extremely
    low.
        - this is called Zobrist hashing: it works by assigning each possible input value a random hash, and
        then combining inputs by combining hashes using XOR. in competitive programming, the niche use cases
        are to check if all elements occur an even number of times in a range, or if a range of length k contains
        the elements [1, k] each a single time. more generally, we can combine a bunch of objects (such as bounding
        boxes surrounding a cell) by assigning each object a random value then XORing together the objects' values
        in order to get a quick number representing the combination of the objects (such as for checking if
        two sets of objects are identical)
    - same core idea as in https://open.kattis.com/problems/pizzastrengur: we move the randomness (the thing
    that varies) from their control (the input data) to our control (the algorithm). this just makes it so that
    particular bit patterns or orderings of input cannot exploit our algorithm. the randomization makes the
    algorithm more robust by moving the worst case into the average case; the tradeoff is that the best case
    also gets moved into the average case.
    */

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    vector<ull> pref_xor(n + 1, 0);
    for (int i = 1; i <= n; ++i) pref_xor[i] = pref_xor[i - 1] ^ rand_val[a[i - 1]];

    while (q--) {
        int l, r;
        cin >> l >> r;
        bool all_even_freq = (pref_xor[r] ^ pref_xor[l - 1]) == 0;
        cout << (all_even_freq ? "YES" : "NO") << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(seed);
    constexpr int MAXAI = 1e6;
    vector<ull> rand_val(MAXAI + 1, 0);
    for (int i = 1; i <= MAXAI; ++i) {
        rand_val[i] = rng();  // generates a random number for each possible input a_i
    }

    int t = 1;
    cin >> t;
    while (t--) {
        solve(rand_val);
    }

    return 0;
}
