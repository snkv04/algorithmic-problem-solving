#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    
    int start = -1, blanks = 0;
    int pairs = 0, lefts = 0, rights = 0, boths = 0;
    int sum = 0; map<char, int> mp = {{'I', 1}, {'V', 5}, {'X', 10}};
    for (int i = 0; i < n; ++i) {
        if (s[i] == '?') {
            blanks += 1;

            if (start == -1) {
                start = i;
            }

            if (i == n - 1 || s[i + 1] != '?') {
                bool left = start && s[start - 1] == 'I';
                bool right = i < n - 1 && (s[i + 1] == 'V' || s[i + 1] == 'X');
                
                if (left && right) {
                    if (i == start) {
                        boths += 1;
                    } else {
                        lefts += 1;
                        rights += 1;
                        pairs += (i - start + 1 - 2) / 2;
                    }
                } else if (left || right) {
                    lefts += left;
                    rights += right;
                    pairs += (i - start) / 2;
                } else {
                    pairs += (i - start + 1) / 2;
                }

                start = -1;
            }
        } else {
            if (s[i] == 'I') {
                if (i == n - 1 || (s[i + 1] == '?' || s[i + 1] == 'I')) {
                    sum += 1;
                } else {
                    sum -= 1;
                }
            } else {
                sum += mp[s[i]];
            }
        }
    }
    // cout << "lefts = " << lefts << ", rights = " << rights << ", boths = " << boths << ", pairs = " << pairs << endl;

    while (q--) {
        int ci, cv, cx;
        cin >> cx >> cv >> ci;

        // fix counts of each char
        int rem = blanks;
        if (ci >= rem) {
            ci = rem;
            cv = cx = 0;
        } else {
            rem -= ci;
            if (cv >= rem) {
                cv = rem;
                cx = 0;
            } else {
                rem -= cv;
                cx = rem;
            }
        }
        // cout << "ci = " << ci << ", cv = " << cv << ", cx = " << cx << endl;

        // handle lefts and rights
        // the entire reason why my code got WA was literally just that it was convoluted
        // and therefore easy to place bugs into. cleaning it up got AC. 💀
        int new_sum = sum;
        int num_rights = min(rights, ci);
        new_sum -= num_rights;
        ci -= num_rights;

        int rem_lefts = lefts;
        int taking = min(cv, rem_lefts);
        new_sum += 3 * taking;
        cv -= taking; rem_lefts -= taking;

        taking = min(cx, rem_lefts);
        new_sum += 8 * taking;
        cx -= taking; rem_lefts -= taking;

        // make max number of pairs (doesn't overlap with "both" segments)
        int avail_pairs = pairs;
        int num_pairs = min(ci, cv);
        num_pairs = min(num_pairs, avail_pairs);
        new_sum += num_pairs * 4;
        ci -= num_pairs; cv -= num_pairs; avail_pairs -= num_pairs;
        num_pairs = min(ci, cx);
        num_pairs = min(num_pairs, avail_pairs);
        new_sum += num_pairs * 9;
        ci -= num_pairs; cx -= num_pairs; avail_pairs -= num_pairs;
        
        // deals with "boths"
        int rem_boths = boths;
        // cout << "1: " << new_sum << endl;
        taking = min(rem_boths, ci);
        rem_boths -= taking;
        new_sum -= taking;
        ci -= taking;
        // cout << "2: " << new_sum << endl;

        taking = min(rem_boths, cv);
        rem_boths -= taking;
        new_sum += 3 * taking;
        cv -= taking;
        // cout << "3: " << new_sum << endl;

        taking = min(rem_boths, cx);
        rem_boths -= taking;
        new_sum += 8 * taking;
        cx -= taking;
        // cout << "4: " << new_sum << endl;

        // handles remaining chars
        new_sum += ci + 5 * cv + 10 * cx;
        cout << new_sum << endl;
    }
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
