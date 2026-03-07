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
        - given an array, find the number of ordered 3-tuples of indices whose corresponding values in the array
        form a geometric sequence
    - solution:
        - brute-force over the SECOND element in the tuple and the ratio B, where there are 2 cases for the ratio:
            - B = 1, so all indices have the same element
            - B > 1, so all indices have different elements
        - for the second case of B, to do this efficiently, we can break a_j down into two cases:
            - a_j >= min(a_i) * cbrt(max(a_k / a_i))^2, so then b <= cbrt(max(a_k / a_i)) ~= 1e3
            - a_j <  min(a_i) * cbrt(max(a_k / a_i))^2, so then a_j <= 1e6 and a_j has O(1e3) divisors,
            which we can brute-force through to find possible values for b
    - details:
        - how do we know to split into cases based on a_j, and not based on a_i or a_k?
            - it's actually very interesting: one solution, which is this one, is to iterate over all a_j and
            find all triples for each a_j, but the way that we find all triples is different based on if a_j
            is big or small. another solution is to iterate over all a_k and find all triples for each a_k
            in the same way, but the way that we find each triple is different based on if the triple's smallest
            value (a_i) is small or large. there's a pattern here: we have a set A of objects and for each
            A_i in A we have a separate set B_i of objects to iterate over; in this solution, we enumerate them
            all by changing our enumeration method on the inner loop based on the variable in the outer loop,
            while in the other solution, we enumerate them all by splitting up the inner loop into two inner
            loops that are both separately efficient.
        - how to obtain this bound for b intuitively?
            - well, we know that we have a functional brute-force algorithm, but we need to optimize something.
            we can see if we can bound any of the variables (in this case, b) by splitting our search algorithm
            into cases. to see how to bound it, we can write out the relations between the variables mathematically,
            and look for a bound that makes the algorithm tractable.
        - BE CAREFUL ABOUT HEAP ALLOCATIONS BRUH
    */

    // read input
    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    // get max/min element and count frequencies
    map<ll, ll> freq;
    ll mx = 1, mn = 1e9; for (ll ai : a) { mx = max(mx, ai); mn = min(mn, ai); }
    for (int ai : a) freq[ai] += 1;

    // count triples where B = 1
    ll ans = 0;
    for (auto entry : freq) {
        ll cnt = entry.second;
        ans += cnt * (cnt - 1) * (cnt - 2);
    }

    // count triples where B > 1
    vector<ll> bs;  // allocate on heap once
    for (auto entry : freq) {
        ll aj = entry.first;
        ll cnt = entry.second;

        // break into cases: a_j is large, and a_j is small
        if (aj >= 1e6) {
            for (ll b = 2; b * aj <= mx; ++b) {  // implicitly defines maxb
                ll ai = aj / b;  // might not be divisible
                ll ak = aj * b;
                if (ai * b == aj && ak <= mx) {
                    // caches iterator accesses
                    auto itai = freq.find(ai), itak = freq.find(ak);
                    if (itai != freq.end() && itak != freq.end()) {
                        ans += itai->second * cnt * itak ->second;
                    }
                }
            }
        } else {
            // implementation detail: to catch all divisors of a_j, we do have to start div from 1
            // (main reason: we want to get a_j/1 = a_j as a divisor), but we should make sure to
            // not consider 1 as a possible value of b, since we've already done that
            for (int div = 1; div * div <= aj; ++div) {
                if (aj % div == 0) {
                    // get both divisors, unless a_j is a perfect square
                    bs.push_back(div);
                    if (div * div != aj) bs.push_back(aj/div);
                    bs.erase(std::remove(bs.begin(), bs.end(), 1), bs.end());

                    // check each value of b the same way
                    for (ll b : bs) {
                        ll ai = aj / b;  // should be divisible
                        ll ak = aj * b;
                        if (ai * b == aj && ak <= mx) {
                            // caches iterator accesses
                            auto itai = freq.find(ai), itak = freq.find(ak);
                            if (itai != freq.end() && itak != freq.end()) {
                                ans += itai->second * cnt * itak->second;
                            }
                        }
                    }

                    // empties bs
                    bs.clear();
                }
            }
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
