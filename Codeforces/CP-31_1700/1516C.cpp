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
        - define an array as "good" if it CAN'T be split into two subsets that each have the same sum
        - find the minimum number of elements to remove from an array so that the remaining array is "good"
    - solution:
        - find if the array is already good or not using knapsack DP
        - if it isn't, then we can ALWAYS make the array good in 1 removal by either:
            - removing an odd element, so the overall array sum is odd
            - dividing all elements by a shared divisor, and then checking if we can do the first option
    = details:
        - it's important to note down the properties of what it means for the array to be good and for it to
        be bad. if it's good, then the half-sum of the array isn't achievable by taking a subset. if it's not
        already good, then the half-sum is achievable, which means the array sum is even. this is useful because
        it means that our goal can be simplified to making the array sum odd
        - the core idea of the solution is: a very convenient way to make sure there's no achievable half-sum
        (though DEFINITELY not the only way) is to make the overall sum odd. however, if that's not possible,
        then notice that by scaling down ALL elements in the array by a common factor, the property of "half-sum
        is achievable by taking subset" is maintained, so as long as our array has only even elements, we can
        scale everything down by 2 (because to be even means to have a divisor of 2, so all elements will have
        that divisor), and then once there's an odd element, we remove it.
        in other words, we can maintain our goal of "let's simply make the array sum odd", but scale down all
        elements of our array until we can achieve that goal.
            - if everything is even, then everything shares a divisor (of 2)
            - another way to think of it is we are just removing a shared divisor, which would work the same
            if we used the GCD instead
        - to find out that we ALWAYS only need 1 element, find the simple case where we obviously only need
        to remove 1 (i.e., there's an odd element), then recognize that every case can be transformed into
        that simple case by scaling all of the elements down, as described above
    */
    
    // reads in input
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // checks if array sum is odd; if so, then already good
    int sum = 0;
    for (int ai : a) sum += ai;
    if (sum % 2) {
        cout << "0\n";
        return;
    }

    // checks if half-sum is not achievable; if so, then already good, by definition
    vector<bool> mem(sum/2 + 1, false);  // max value we care about is sum/2, not sum
    mem[0] = true;
    for (int ai : a) {
        for (int i = sum/2; i >= ai; --i) {
            mem[i] = mem[i] || mem[i - ai];
        }
    }
    if (!mem[sum/2]) {
        cout << "0\n";
        return;
    }

    // finds which element is divisible by the smallest power of 2
    cout << "1\n";
    while (true) {
        // checks if any element is odd
        for (int i = 0; i < n; ++i) {
            if (a[i] % 2) {
                cout << i + 1 << '\n';
                return;
            }
        }

        // divide all elements by 2
        for (int &ai : a) {
            ai /= 2;
        }
    }
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
