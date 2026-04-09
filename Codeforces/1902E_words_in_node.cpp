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
    int end, word_count;

    TrieNode() : children{}, end(0), word_count(0) {}
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

    void _update_counts(TrieNode *node) {
        int cnt = node->end;
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                _update_counts(node->children[i]);
                cnt += node->children[i]->word_count;
            }
        }
        node->word_count = cnt;
    }
    
    void update_counts() {
        _update_counts(&root);
    }

    void _print_trie(int num_tabs, char curr_letter, TrieNode *curr_node, std::stringstream &stream) {
        for (int i = 0; i < num_tabs; ++i) {
            stream << ' ';
        }
        stream << "('" << curr_letter << "', " << curr_node->end << ")\n";
        for (int i = 0; i < 26; ++i) {
            if (curr_node->children[i] != nullptr) {
                _print_trie(num_tabs + 2, static_cast<char>('a' + i), curr_node->children[i], stream);
            }
        }
    }

    std::string print_trie() {
        std::stringstream stream;
        _print_trie(0, '.', &root, stream);
        return stream.str();
    }

    TrieNode root;
};

void solve() {
    int n;
    cin >> n;
    vector<string> s(n);
    cin >> s;

    PrefixTree trie;
    for (int i = 0; i < n; ++i) {
        trie.insert(s[i]);
    }
    trie.update_counts();

    ll sum = 0;
    for (int i = 0; i < n; ++i) sum += s[i].size();
    ll ans = sum * 2 * n;
    for (int i = 0; i < n; ++i) {
        string copy = s[i];
        reverse(copy.begin(), copy.end());

        // set of possible LCP values is [0, s[i].size()]
        // let max_lcp = max possible LCP any word has with s[i]
        // then the bottom 2 branches handle max_lcp, and the first branch handles LCP values strictly < max_lcp
        // in some situations, we need a special case for the first value; in this case, it's for the last value,
        // though in a way, it's induced by having a special node before the first character in every string
        TrieNode *curr = &trie.root;
        bool broke = false;
        for (int j = 0; j < copy.size(); ++j) {
            int letter = copy[j] - 'a';
            if (curr->children[letter] != nullptr) {
                // finds number of words whose LCP is EXACTLY j
                ll num_words = curr->word_count - curr->children[letter]->word_count;
                curr = curr->children[letter];
                ans -= 2 * num_words * j;
            } else {
                // can't go further in the word, because no nodes
                ll num_words = curr->word_count;
                ans -= 2 * num_words * j;
                broke = true;
                break;
            }
        }
        if (!broke) {
            // can't go further in the word, because it ended
            ans -= 2LL * curr->word_count * copy.size();
        }
    }
    cout << ans << endl;
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
