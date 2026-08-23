#include <bits/stdc++.h>
using namespace std;

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

    std::map<T, long long> counts;
};

void solve() {
    int n, k, L, R;
    cin >> n >> k >> L >> R;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int r = -1;
    Multiset<int> vals1;
    while (vals1.counts.size() < k && r + 1 < n) {
        ++r;
        vals1.add(a[r]);
    }
    if (vals1.counts.size() < k) {
        cout << 0 << endl;
        return;
    }

    Multiset<int> vals2;
    vals2.counts = vals1.counts;
    int l1 = 0, l2 = 0;
    long long ans = 0;
    while (r < n) {
        while (vals1.counts.size() > k) {
            vals1.remove(a[l1]);
            ++l1;
        }

        while (vals2.counts.size() > k) {
            vals2.remove(a[l2]);
            ++l2;
        }
        while (vals2.counts[a[l2]] > 1) {
            vals2.remove(a[l2]);
            ++l2;
        }

        int len1 = min(R, r - l1 + 1);
        int len2 = max(L, r - l2 + 1);
        ans += max(0, len1 - len2 + 1);

        ++r;
        if (r < n) {
            vals1.add(a[r]);
            vals2.add(a[r]);
        }
    }
    cout << ans << endl;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
