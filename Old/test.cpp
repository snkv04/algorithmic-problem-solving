#include <iostream>
#include <set>
#include <typeinfo>
#include <queue>

using namespace std;
using ll = long long;

struct DSU {
private:
    vector<int> parent;
    vector<int> size;
    int n;

public:
    int find(int node) {
        if (parent[node] == node) return node;
        else {
            parent[node] = find(parent[node]);
            return parent[node];
        }
    }

    void unite(int a, int b) {
        int c = find(a), d = find(b);
        if (c != d) {
            parent[d] = c;
            size[c] += size[d];
            size[d] = size[c];
        }
    }

    DSU(int size) {
        n = size;
        parent.resize(size);
        (this->size).resize(size);
        for (int i = 0; i < n; ++i) {
            this->size[i] = 1;
            parent[i] = i;
        }
    }
};

bool is_prime(int n) {
    for (int d = 2; d <= sqrt(n); ++d) {
        if (n % d == 0) return false;
    }
    return true;
}

ll gcd(ll a, ll b) {
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll r = A % B;
        A = B;
        B = r;
    }
    return A;
}

int main() {
//    // Dynamically allocate memory for an integer
//     int* ptr = new int(42); // Allocate and initialize to 42

//     cout << "Value: " << *ptr << endl; // Output: Value: 42

//     *ptr = 40;
//         cout << "Value: " << *ptr << endl; // Output: Value: 42


//     delete ptr; // Free the allocated memory
//     cout << "Value: " << *ptr << endl; // Output: Value: 42
//     ptr = nullptr; // Avoid dangling pointer
//     cout << "Value: " << *ptr << endl; // Output: Value: 42

    // int a[10];
    // for (int i = 0; i < 10; ++i) {
    //     // a[i] = i;
    //     cout << a[i] << " ";
    // }
    // cout << "\n";

    // int b, c;
    // cout << "b = " << b << "c = " << c << "\n";

    // string s;
    // getline(cin, s);
    // cout << "s = |" << s << "|\n";

    // multiset<int> m;
    // for (int i = 0; i < 5; ++i) {
    //     m.insert(i);
    //     m.insert(i);
    // }

    // cout << m.size() << '\n';

    // for (const auto &i : m) {
    //     cout << i << " ";
    //     // cout << "\n";
    // }

    // int a;

    // vector<int> v;
    // for (int i = 0; i < 20; ++i) {
    //     v.push_back(i);
    // }
    // // for (int i = 0; i < 20; ++i) {
    // //     std::cout << v[i] << " ";
    // // }
    // // std::cout << "\n";
    // vector<int>::iterator it = v.begin();
    // while (it != v.end()) {
    //     cout << *it << " ";
    //     it += 4;
    // }

    // vector<int> v = {2, 2, 2, 0};
    // while (true) {
    //     for (int i = 0; i < 4; ++i) cout << v[i] << " ";
    //     cout << "\n";
    //     if (!next_permutation(v.begin(), v.end())) {
    //         break;
    //     }
    // }
    // cout << "afterward: "; for (int i = 0; i < 4; ++i) cout << v[i] << " "; cout << '\n';

    // cout << (1 << 30) << "\n";
    // cout << (1 << 31) << '\n';
    // cout << ((1 << 31) - 1) << '\n';
    // cout << (1 << 32) << '\n';
    // cout << (1LL << 32) << '\n';
    // cout << (1LL << 62) << '\n';
    // cout << (1LL << 63) << '\n';
    // cout << (1LL << 63) - 1 << '\n';

    /*
   1 9 0 S
+  8 0 P 9
------
 1 0 0 9 Q
    */

    // string a, b;
    // cin >> a >> b;
    // cout << a.compare(b) << '\n';
    // string remaining;
    // getline(cin, remaining);
    // cout << "remaining = |" << remaining << "|\n";

    // array<int, 5> a = {1, 2, 3}, b = {1, 2, 3};
    // cout << (a == b) << "\n";

    // map<pair<ll, ll>, pair<ll, ll> > counts;

    for (int i = 1; i <= 10; ++i) {
        for (int j = i+1; j <= 10; ++j) {
            int g = gcd(i, j);
            int f = i * j / g / g;
            if (is_prime(f)) {
                cout << "i = " << i << ", j = " << j << ", f = " << f << "\n";
            }
        }
    }


    return 0;
}
