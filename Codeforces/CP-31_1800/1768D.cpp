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

struct DSU {
    DSU(int n) : n(n), comp_size(n, 1) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;
        else return parent[node] = find(parent[node]);
    }

    void join(int node1, int node2) {
        int root1 = find(node1), root2 = find(node2);
        if (root1 != root2) {
            if (comp_size[root1] >= comp_size[root2]) {
                parent[root2] = root1;
                comp_size[root1] += comp_size[root2];
            } else {
                parent[root1] = root2;
                comp_size[root2] += comp_size[root1];
            }
        }
    }

    int size(int node) {
        return comp_size[find(node)];
    }

private:
    int n;
    std::vector<int> parent, comp_size;
};

void solve() {
    /*
    - problem:
        - we have a permutation, and in each operation, we can swap two elements
        - what is the minimum number of swapping operations we need to perform to ensure there's
        exactly 1 inversion in the permutation?
    - solution:
        - 1 inversion means that two adjacent elements are out of place and everything else is sorted
        - so, we can iterate through all of the n-1 possible permutations with 1 inversion, and count
        the number of swaps needed to transform the array into that permutation
            - we do this by swapping those 2 elements, and counting the number of swaps needed to simply
            transform the array into the identity (sorted) permutation
            - counting the number of swaps can be done by counting the number of cycles
            - counting the number of cycles in each new graph can be done efficiently by counting the
            number of cycles initially, then observing that if we swap 2 elements, the number of cycles
            will increase by 1 if they're already in the same cycle and decrease by 1 if they're not in
            the same cycle
    - details:
        - suppose you want to sort an array or sort a permutation. here's a way of thinking about that:
        we basically assign each element of the array an ID (which is equal to itself), and sort the
        elements keyed on their ID. ("keyed on" just means that in the final array, what we care about
        is that the IDs are sorted.)
        now, suppose we want an array to have a particular ordering. a way of doing that is assigning
        each element to an ID equal to its desired index in the final array, and then sorting the array
        keyed on ID. if the IDs are just the indices in the final array, then sorting by ID just moves
        everything into the desired order.
        - the mapping from
        [5, 4, 3, 2, 1] --> [1, 2, 4, 3, 5]
        and from
        [5, 3, 4, 2, 1] --> [1, 2, 3, 4, 5]
        is the exact same. this means that the same operations (on indices) can be used to carry out
        either mapping. in other words,
        starting from a random ordering, then sorting all elements and reconfiguring some of them,
        leads to the same changes in indices as
        reconfiguring the elements, assigning the indices afterward, then sorting all elements.
        - to get the number of swaps needed to sort a permutation, just observe that it's equal to the
        (sum across (each cycle c) of (size of c minus 1)), which is equivalent to (n - num of cycles)
    */

    // reads in the permutation and places all values into [0, n - 1]
    int n;
    cin >> n;
    vector<int> p(n);
    cin >> p;
    for (int i = 0; i < n; ++i) --p[i];

    // counts the number of cycles at the very beginning using the initial permutation
    int cycles = 0;
    vector<bool> visited(n, false);
    vector<int> cycle_id(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            ++cycles;
            int curr = i;
            while (!visited[curr]) {
                visited[curr] = true;
                cycle_id[curr] = i;
                curr = p[curr];
            }
        }
    }

    // iterates through each final permutation that has a single swap,
    // finding the number of swaps needed to transform the initial permutation into it
    // by pretending to swap those 2 elements and
    // efficiently finding the number of swaps to transform the virtual new permutation into the identity
    int ans = n;
    for (int i = 0; i < n - 1; ++i) {
        if (cycle_id[i] == cycle_id[i + 1]) {
            ans = min(ans, n - (cycles + 1));
        } else {
            ans = min(ans, n - (cycles - 1));
        }
    }
    cout << ans << endl;
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
