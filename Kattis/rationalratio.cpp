#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

ll gcd(ll a, ll b) {
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}

struct Frac {
    ll num, denom;

    Frac() : num(0), denom(1) {}

    Frac(ll num, ll denom) : num(num), denom(denom) {}

    void reduce() {
        ll g = gcd(num, denom);
        num /= g;
        denom /= g;
    }

    void operator+=(Frac &&other) {
        ll new_denom = lcm(this->denom, other.denom);
        this->num *= new_denom / this->denom;
        this->num += other.num * (new_denom / other.denom);
        this->denom = new_denom;
        this->reduce();
    }
};

ll pow(ll b, ll e) {
    if (e == 0) return 1;

    ll result = pow(b, e / 2);
    result *= result;
    if (e % 2) result *= b;
    return result;
}

void solve() {
    /*
    this comes down to the idea that for a segment after the decimal point to be repeating, such as
    0.abcabcabc..., we can represent it in a closed form as abc/999. namely, we can represent it as
    the repeating segment divided by (10 to the power of the length of the repeating segment, minus 1).
    the rest of the answer is just standard fractional representations of fixed (non-repeating) numbers
    in the base-10 system (namely, we take numbers and represent them as integers divided by powers
    of 10).
    */

    string number; int repeating_len;
    cin >> number >> repeating_len;

    ll before = 0, after = 0, repeating = 0;
    int nonrepeating_len = 0;
    bool crossed_dot = false;
    for (int i = 0; i < number.size(); ++i) {
        if (number[i] == '.') {
            crossed_dot = true;
        } else {
            int digit = number[i] - '0';
            if (!crossed_dot) {
                before *= 10;
                before += digit;
            } else {
                if (i >= number.size() - repeating_len) {
                    repeating *= 10;
                    repeating += digit;
                } else {
                    after *= 10;
                    after += digit;
                    ++nonrepeating_len;
                }
            }
        }
    }

    Frac ans = Frac(before, 1);
    if (after) {
        ans += Frac(after, pow(10, nonrepeating_len));
    }
    ans += Frac(repeating, (pow(10, repeating_len) - 1) * pow(10, nonrepeating_len));
    cout << ans.num << "/" << ans.denom << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
