#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(idx=" << p.first << ", val=" << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const deque<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // why do we have 3 different copies of the array? the one on the right is so that for each element,
    // if there EXISTS an element lower than it that would come on its right at some point in the cyclic
    // rotation, then this array on the right simulates that cyclic behavior. the one on the left is so
    // that for each element, if there EXIST elements that would all follow the same jump pattern as it
    // on the left at some point in the cyclic rotation (but might be to the right in the original array),
    // then this array on the left simulates that cyclic behavior. only the one on the middle has its jumps
    // actually get recorded, but to correctly record them, we need elements on the right (to know when
    // the jump ends) and elements on the left (to see how many times, or for how many different elements,
    // the jump happens).
    vector<ll> delta(n+1, 0);
    deque<int> d;
    for (int i = 3*n-1; i >= 0; --i) {
        // flushes out indices that are too far to the right
        while (d.size() && d.back() > i+n) {
            d.pop_back();
        }

        // pops off elements to maintain the monotonically strictly increasing property
        int val = a[i%n];
        while (d.size() && val <= a[d.front() % n]) {
            // check if there is a drop that STARTS in one of the original buckets (so, [n, 2*n-1])
            // and ends either in the original buckets (second array) or the third array of buckets
            if (d.size() >= 2 && d.front() >= n && d.front() <= 2*n-1) {
                int start_day = d[1] - d[0];
                int num_days = d.front() - i;
                delta[start_day] -= a[d[0]%n] - a[d[1]%n];
                delta[start_day + num_days] += a[d[0]%n] - a[d[1]%n];
                // cout << "drop from " << make_pair(d[0], a[d[0]%n]) << " to " << make_pair(d[1], a[d[1]%n]) << " starts on day " << start_day << " and ends on day " << (start_day + num_days - 1) << endl;
            }

            // pops from top of stack
            d.pop_front();
        }

        // pushes current index
        d.push_front(i);

        // deque<pair<int, int>> temp; for (int j = 0; j < d.size(); ++j) temp.push_back(make_pair(d[j], a[d[j]%n]));
        // cout << "i = " << i << ", deque = " << temp << endl;
    }
    // 4 5 1 2 3 | 4 5 1 2 3

    for (int i = 1; i <= n; ++i) delta[i] += delta[i-1];
    delta[0] = accumulate(a.begin(), a.end(), 0LL);
    for (int i = 1; i <= n; ++i) {
        delta[i] += delta[i-1];
        cout << delta[i] << '\n';
    }
}
