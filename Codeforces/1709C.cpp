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

// going to make a copy anyway, so might as well pass by copy
string solve_max(string s) {
    int n = s.size(), open = n / 2, close = n / 2;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') --open;
        else if (s[i] == ')') --close;
    }

    for (int i = 0; i < n; ++i) {
        if (s[i] == '?') {
            if (open) {
                --open;
                s[i] = '(';
            } else {
                --close;
                s[i] = ')';
            }
        }
    }
    return s;
}

string solve_min_separate_cases(string s) {
    stack<int> stk;
    int balance = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        if (s[i] == '?') {
            // if can use ')', then use it, otherwise just use '('.
            if (balance > 0) {
                s[i] = ')';
                stk.push(i);
                --balance;
            } else {
                // it might be possible to update a previous ')' into a '(' so that we can use a ')' here,
                // but that would be suboptimal anyway
                s[i] = '(';
                ++balance;
            }
        } else {
            // can't change anything, just update the balance
            balance += (s[i] == '(') ? 1 : -1;

            // but check the balance, because something previous that we COULD change might have made the
            // balance negative here
            if (balance < 0) {
                assert(stk.size());
                s[stk.top()] = '(';
                stk.pop();
                balance += 2;
            }
        }
    }
    return s;
}

string solve_min_same_postprocessing(string s) {
    stack<int> stk;
    int balance = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        // always greedily place a ')' if we have the opportunity to replace a character,
        // even if the new balance is invalid
        if (s[i] == '?') {
            --balance;
            s[i] = ')';
            stk.push(i);
        } else {
            balance += s[i] == '(' ? 1 : -1;
        }

        // then, post-process this index, using the stack to restore the balance by modifying
        // the rightmost ')' that we placed down
        if (balance < 0) {
            balance += 2;
            assert(stk.size());
            s[stk.top()] = '(';
            stk.pop();
        }
    }
    return s;
}

void solve() {
    /*
    - problem:
        - we have an RBS with some characters replaced by "?"
        - we want to see if only one possible RBS fits that string
    - solution:
        - imagine the set of all possible RBSs that fit that string, and impose some total ordering upon them
        (such as lexicographical ordering)
        - now, in a way similar to the squeeze theorem, if the max and min of that set are equal, then there
        is only one element in the set
        - therefore, we don't have to check every element in the set; we can just check the lexicographically
        maximum and minimum one
    - details:
        - suppose each '(' is +1 and ')' is -1. then:
            - notes on lexicographically maximum sequence:
                - we know the number of opens and closes, and putting all the opens before closes will always
                be valid
                    - why? the original string is an RBS, and the prefix balance will be maximal this way, so
                    for any prefix its balance will be >= that of the original string, meaning that it will
                    never drop below 0, with a guarantee
                - so, we just do that
            - notes on lexicographically minimum sequence:
                - the idea is literally just: always put down a ')', and if that makes the balance too low, then
                replace the rightmost placed ')' with a '('
                    - the rightmost part is so that the leftmore index will be ')'
                    - concretely, if ...(...)... and ...)...(... both work, then we want the second one
                    - basically, we want closes to be as early as possible, so we don't want to displace an earlier
                    one with a later one, but if we have to change something, then change the later one
                - for the more straightforward, separate cases implementation:
                    - whenever we place down a character, we always choose our character based on the balance
                    beforehand
                    - we only ever notice that the balance isn't valid on the indices where we have no choice
                - for the cleaner, single-case implementation:
                    - on any index, whether we had a choice or not, we could make the balance invalid
                    - so we post-process the balance for that reason
    - useful ideas:
        - if there are multiple options for operations, consider if the alternatives are simply suboptimal
        - since in an RBS, the validity condition is that every prefix's balance must be >= 0, changing a
        ')' to a '(' will never make the string invalid
    */

    string s;
    cin >> s;
    // string filled_max = solve_max(s), filled_min = solve_min_separate_cases(s);
    string filled_max = solve_max(s), filled_min = solve_min_same_postprocessing(s);
    cout << (filled_max == filled_min ? "YES" : "NO") << "\n";
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
