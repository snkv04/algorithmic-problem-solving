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

template <int N>
struct TrieNode {
    array<TrieNode*, N> children;
    bool end;
};

template <int N>
struct Trie {
    TrieNode<N> root;

    Trie() : root() {}

    void insert(vector<int> &arr) {
        TrieNode<N> *curr = &root;
        for (int i = 0; i < arr.size(); ++i) {
            if (curr->children[arr[i]] == nullptr) {
                curr->children[arr[i]] = new TrieNode<N>();
            }
            curr = curr->children[arr[i]];
        }
        curr->end = true;
    }

    int longest_common_prefix(vector<int> &arr) {
        int length = 0;
        TrieNode<N> *curr = &root;
        while (length < arr.size()) {
            if (curr->children[arr[length]] == nullptr) {
                break;
            } else {
                curr = curr->children[arr[length++]];
            }
        }
        return length;
    }
};

void solve() {
    /*
    - keep in mind that an array of things will be default-initialized (initialized to garbage values),
    not value-initialized (initialized to "0" values). so, when constructing a trie where each node
    (especially the root node) has an array of pointers to children, make sure that the root of the trie
    (or just every node, but definitely at least the root) is initialized properly. if not, all of its
    children pointers will be garbage addresses, not nullptr.
    */

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    Trie<10> trie;
    for (int i = 0; i < n; ++i) {
        vector<int> inv(m);
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            --a[i][j];
            inv[a[i][j]] = j;
        }
        trie.insert(inv);
    }

    for (int i = 0; i < n; ++i) {
        cout << trie.longest_common_prefix(a[i]) << " ";
    }
    cout << "\n";
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
