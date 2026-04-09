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
    /*
    - solution:
        - rewrite C(a, b) as C(a, b) := |a| + |b| - 2 * shared(a, b), where shared(a, b) is the max length L such
        that a[1:L] == reversed(b[ |b|+1-L : |b| ])
        - then, find sum across i of (sum across j of shared(s_i, s_j)) using a trie, where each node keeps track
        of the number of words sharing the prefix corresponding to that node (basically, word count in subtree),
        and we walk through suffixes of s_i to see how many s_j share a prefix with that reversed suffix
            - prefix-walking logic is this: we want the suffix of length k of s_i to match the prefix of length k
            of any s_j (reversed). so suppose we have a list of all pairs (s_i, s_j), where s_i's suffix matches
            s_j's prefix, and i is fixed. when we increment k, some words s_j will be filtered out; the ones that
            aren't are the ones who still match s_i, so we basically pair one letter from s_i and one letter from s_j
            for EACH j that is valid. that is where "ans -= 2 * curr->word_count" comes from. the key idea is that
            this list of (s_i, s_j) pairs is implicitly maintained using the trie.
            - another way to think of the prefix-walking logic: mathematically, we are taking the
                sum across (j = 1 to n) of LCP(s_i', s_j)
            and rearranging it to
                sum across (len = 1 to |s_i'|) of |sharing(s_i', len)|, where sharing(a, len) is the set of words
                s_j for which LCP(a, s_j) >= len.
            in english, instead of, for each word s_i, iterating through each word s_j to find that pair's LCP,
            we, for each word s_i, iterate through all possible lengths of an LCP and count the number of words with
            AT LEAST that LCP using a trie.
            visually, imagine a histogram showing the LCPs with a fixed s_i:
             #
             # #
             # ##
            #####
            our goal is to find the area. the slow way would be to iterate through columns, and find the height
            of each column. one fast way (which we do here) is to iterate through rows and find the number of
            columns with height at least that row (using a trie) for each row. another fast way (which we don't
            do here) is to iterate through rows and find the number of columns with height exactly equal to that
            row (using a trie), multiplying it with the row's index, for each row.
    - generalized ideas for the future:
        - it is simpler (notice a pattern?) to think of "shared prefix between reversed a and b" than to think of
        "shared reversed suffix of a and prefix of b", so do that
    */

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

        TrieNode *curr = &trie.root;
        for (int j = 0; j < copy.size(); ++j) {
            int letter = copy[j] - 'a';
            if (curr->children[letter] != nullptr) {
                curr = curr->children[letter];
                ans -= 2 * curr->word_count;
            } else {
                break;
            }
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
