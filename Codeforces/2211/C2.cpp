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

template <typename T>
struct Multiset {
    void add(T object) {
        counts[object] += 1;
    }

    void remove(T object) {
        if (counts.find(object) == counts.end()) {
            throw std::logic_error("Object not found in multiset");
        }

        counts[object] -= 1;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    void add(T object, long long delta) {
        assert(delta >= 0);
        counts[object] += delta;
    }

    void remove(T object, long long delta) {
        assert(delta >= 0);
        if (counts.find(object) == counts.end() || counts[object] < delta) {
            throw std::logic_error("Not enough instances of object in multiset");
        }

        counts[object] -= delta;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    long long count(T object) {
        if (counts.find(object) == counts.end()) {
            return 0;
        } else {
            return counts[object];
        }
    }
    
    bool empty() {
        return counts.empty();
    }

    std::unordered_map<T, long long> counts;
};

template <typename T>
bool is_superset(Multiset<T> &a, Multiset<T> &b) {
    for (auto [k, v] : b.counts) {
        if (a.count(k) == 0) {
            return false;
        }
    }
    for (auto [k, v] : a.counts) {
        if (b.count(k) && b.count(k) > v) {
            return false;
        }
    }
    return true;
}

void solve_by_checking_a_and_b() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    cin >> a >> b;

    bool valid = true;
    for (int i = 0; i < n; ++i) {
        if (b[i] != -1 && b[i] != a[i]) {
            valid = false;
            break;
        }
    }
    if (valid) {
        cout << "YES\n";
        return;
    }

    // finds classes modulo k where there's at least one index in the class where a[j] != b[j]
    set<int> bad, good;
    for (int i = 0; i < k; ++i) {
        valid = true;
        for (int j = i; j < n; j += k) {
            if (b[j] != -1 && a[j] != b[j]) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            bad.insert(i);
        } else {
            good.insert(i);
        }
    }

    // deals with good classes (no misalignments)
    for (int i : good) {
        // gathers all values from a and b
        set<int> avals, bvals;
        for (int j = i; j < n; j += k) {
            avals.insert(a[j]);
            if (b[j] != -1) bvals.insert(b[j]);
        }

        // if all of a's values are constant and b doesn't have anything filled in, then we don't need to
        // fill in b; otherwise, we fill in b
        if (avals.size() >= 2 || bvals.size() >= 1) {
            for (int j = i; j < n; j += k) {
                b[j] = a[j];
            }
        }
    }

    // deals with bad classes (at least one misalignment)
    for (int i : bad) {
        // all of a and b need to have constant values
        set<int> avals, bvals;
        for (int j = i; j < n; j += k) {
            avals.insert(a[j]);
            if (b[j] != -1) bvals.insert(b[j]);
        }
        if (avals.size() >= 2 || bvals.size() >= 2) {
            cout << "NO\n";
            return;
        }

        // propagate b's constant value to all indices in the class
        assert(bvals.size() == 1);
        int bval = *bvals.begin();
        for (int j = i; j < n; j += k) {
            b[j] = bval;
        }
    }

    Multiset<int> ma, mb;
    for (int i = 0; i < k; ++i) {
        ma.add(a[i]);
        if (b[i] != -1) mb.add(b[i]);
    }
    cout << (is_superset(ma, mb) ? "YES" : "NO") << "\n";
}

void solve_by_checking_a() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    cin >> a >> b;

    // classifies the modular classes based on a's values; more straightforward, but a tiny bit
    // less intuitive
    for (int i = 0; i < k; ++i) {
        // gets a's values in this class
        set<int> avals;
        for (int j = i; j < n; j += k) {
            avals.insert(a[j]);
        }

        if (avals.size() >= 2) {
            // a differs values among this class; all values of b need to match a
            for (int j = i; j < n; j += k) {
                if (b[j] != -1 && b[j] != a[j]) {
                    cout << "NO\n";
                    return;
                }
                b[j] = a[j];
            }
        } else {
            // a's values are constant; b's values need to also be constant
            set<int> bvals;
            for (int j = i; j < n; j += k) {
                if (b[j] != -1) bvals.insert(b[j]);
            }
            if (bvals.size() >= 2) {
                cout << "NO\n";
                return;
            }

            // if b has any value set in stone for this class, it needs to propagate among
            // all indices in the class
            if (bvals.size() == 1) {
                int bval = *bvals.begin();
                for (int j = i; j < n; j += k) {
                    b[j] = bval;
                }
            }
        }
    }

    Multiset<int> ma, mb;
    for (int i = 0; i < k; ++i) {
        ma.add(a[i]);
        if (b[i] != -1) mb.add(b[i]);
    }
    cout << (is_superset(ma, mb) ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        // solve_by_checking_a_and_b();
        solve_by_checking_a();
    }

    return 0;
}
