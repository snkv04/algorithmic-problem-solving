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

struct TrieNode {
    std::array<TrieNode*, 26> children;
    int end;

    TrieNode() : children{}, end(0) {}
};

struct PrefixTree {
    PrefixTree() : root() {}

    void insert(const std::string &str) {
        TrieNode *curr = &root;
        for (int i = 0; i < str.size(); ++i) {
            int letter_as_int = str[i] - 'a';
            if (curr->children[letter_as_int] == nullptr) {
                curr->children[letter_as_int] = new TrieNode();
            }
            curr = curr->children[letter_as_int];
        }
        curr->end += 1;
    }

    void search(int idx, string &s, vector<ll> &mem) {
        TrieNode *curr = &root;
        for (int i = idx; i < s.size(); ++i) {
            int letter = s[i] - 'a';
            if (curr->children[letter] != nullptr) {
                curr = curr->children[letter];
                if (curr->end) {
                    mem[idx] = (mem[idx] + mem[i + 1]) % MOD;
                }
            } else {
                break;
            }
        }
    }

private:
    TrieNode root;
};

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int k;
    cin >> k;
    PrefixTree trie;
    while (k--) {
        string word;
        cin >> word;
        trie.insert(word);
    }

    vector<ll> mem(n + 1, 0);
    mem[n] = 1;
    for (int i = n - 1; i >= 0; --i) {
        trie.search(i, s, mem);
    }
    cout << mem[0] << endl;
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
