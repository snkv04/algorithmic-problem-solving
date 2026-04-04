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
    TrieNode(bool val) : val(val), end_cnt(0), children({nullptr, nullptr}) {}

    bool val;
    int end_cnt;
    pair<TrieNode*, TrieNode*> children;
};

struct PrefixTree {
    PrefixTree() {
        root = new TrieNode(0);
    }

    void insert(int x) {
        TrieNode *curr = root;
        for (int i = 29; i >= 0; --i) {
            bool bit = (x >> i) & 1;
            if (bit) {
                if (curr->children.second == nullptr) {
                    curr->children.second = new TrieNode(1);
                }
                curr = curr->children.second;
            } else {
                if (curr->children.first == nullptr) {
                    curr->children.first = new TrieNode(0);
                }
                curr = curr->children.first;
            }
        }
        curr->end_cnt += 1;
    }

    // assumes there's already at least one item inserted into the tree
    int find_farthest_element(int x) {
        int result = 0;
        TrieNode *curr = root;
        for (int i = 29; i >= 0; --i) {
            bool bit = (x >> i) & 1;
            bool checking_for = !bit;  // basically, we try to go in the opposite direction, if such an element exists

            bool going_right = (checking_for && curr->children.second != nullptr) ||
                               (!checking_for && curr->children.first == nullptr);
            if (going_right) {
                curr = curr->children.second;
            } else {
                curr = curr->children.first;
            }
            result += going_right * (1 << i);
        }
        return result;
    }

    int find_largest_xor(int x) {
        return x ^ find_farthest_element(x);
    }

private:
    TrieNode *root;
};

void solve() {
    /*
    - problem:
        - given an array, find the maximum XOR sum of any subarray
    - solution:
        - we are trying to find some (l, r) such that XOR(x[l], x[l+1], ..., x[r]) is maximized
        - equivalently, we are trying to find some (l, r) such that pref_xor[r] ^ pref_xor[l-1] is maximized
        - so, for each r, we can try to find some l that maximizes pref_xor[r] ^ pref_xor[l-1]
            - in order to do this, observe that given a number x, the number y that maximizes (x XOR y)
            will have all bits flipped
            - if such a number y doesn't exist in the set we're searching over, then we'd want to flip as
            many as we can. how do we prioritize which ones to flip? prioritize flipping the largest bits.
            - therefore, we can keep track of seen prefix XORs (yes, individual integers, not strings)
            in a trie, where each level of the trie's nodes corresponds to a bit (with MSB closest to root)
            - then, it becomes easy to find the "farthest" previous prefix XOR from the current prefix XOR
    */

    // reads in input
    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;
    
    // iterates through prefix XOR sums, finding farthest prefix XOR for each using a bit trie (or 0/1 trie)
    PrefixTree trie;
    int pref_xor = 0, ans = 0;
    trie.insert(pref_xor);
    for (int i = 0; i < n; ++i) {
        pref_xor ^= x[i];
        ans = max(ans, trie.find_largest_xor(pref_xor));
        trie.insert(pref_xor);
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
