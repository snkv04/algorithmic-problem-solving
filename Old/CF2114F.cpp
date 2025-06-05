#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
map<string, int> mem;
int absbest;

template <typename Container>
string print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    stringstream ss;
    ss << prefix << "[";
    for (const auto &elem : c) {
        ss << elem << ",";
    }
    ss << "]";
    return ss.str();
}

ll sqrt(ll n) {
    // calculates the floor of sqrt(n) in O(log(n))
    if (n == 0) return 0;
    else if (n < 0) return -1;
    ll l = 1, r = n, sqrt = -1;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll factor = n / mid;
        if (mid <= factor) {
            sqrt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return sqrt;
}

vector<int> prime_factorization(int n) {
    vector<int> factors;
    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            n /= i;
            factors.push_back(i);
        }
    }
    if (n != 1) {
        factors.push_back(n);
    }
    return factors;
}

int gcd(int a, int b) {
    int A = max(a, b), B = min(a, b);
    while (B != 0) {
        int r = A % B;
        A = B;
        B = r;
    }
    return A;
}

string repr(int idx, vector<int> &groups) {
    stringstream ss;
    ss << idx << ";";
    ss << print_container(groups);
    return ss.str();
}

int recurse(int idx, vector<int> &primes, vector<int> &groups, int k) {
    string str = repr(idx, groups);
    // cout << "str = " << str << "\n";
    if (idx == primes.size()) {
        absbest = min(absbest, (int) groups.size());
        return (int) groups.size();
    }
    if (mem.find(str) != mem.end()) {
        // cout << "found in mem for str = " << str<<endl;
        absbest = min(absbest, mem[str]);
        return mem[str];
    }
    if (groups.size() >= absbest) return 1e9;

    int best = 1e9;
    int p = primes[idx];
    for (int i = 0; i < groups.size(); ++i) {
        if (k / groups[i] >= p) {
            groups[i] *= p;
            best = min(best, recurse(idx+1, primes, groups, k));
            groups[i] /= p;
        }
    }

    groups.push_back(p);
    best = min(best, recurse(idx+1, primes, groups, k));
    groups.pop_back();
    mem[str] = best;
    absbest = min(absbest, best);
    return best;
}

void solve() {
    int x, y, k;
    cin >> x >> y >> k;
    // print_container(prime_factorization(y), "prime factorization = ");

    int g = gcd(x, y);
    x /= g;
    y /= g;
    vector<int> px = prime_factorization(x), py = prime_factorization(y);
    // cout << "px = " << print_container(px) << "\n";
    // cout << "py = " << print_container(py) << "\n";
    int mx = 0;
    for (int pxi : px) mx = max(mx, pxi);
    for (int pyi : py) mx = max(mx, pyi);
    if (mx > k) {
        cout << "-1\n";
        return;
    }
    
    int ans = 0;
    for (vector<int> vec : vector<vector<int>>({px, py})) {
        absbest = 1e9;
        vector<int> groups;
        mem.clear();
        int val = recurse(0, vec, groups, k);
        ans += val;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
