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

void solve() {
    // reads in and processes the input
    ll x, k;
    cin >> x >> k;
    vector<queue<pair<ll, ll>>> segments(k);  // (minimum sum, overall sum)
    priority_queue<pair<ll, int>> pq;  // (minimum sum, index of queue from list of queues)
    for (int i = 0; i < k; ++i) {
        // reads in the list as a queue
        int l;
        cin >> l;
        queue<int> q;
        while (l--) {
            int qi;
            cin >> qi;
            q.push(qi);
        }

        // takes the free elements at the start that have no cost
        ll sum = 0;
        while (q.size() && q.front() >= 0) {
            sum += q.front();
            q.pop();
        }
        x += sum;

        // breaks up the queue into segments holding "cost" and "delta"/"benefit" attributes
        sum = 0;
        ll mn = 0;
        while (q.size()) {
            // processes the single element by placing it into the current segment
            sum += q.front();
            mn = min(mn, sum);
            q.pop();

            // ends the segment if needed, preparing for a new one
            if (sum > 0 && (q.empty() || q.front() < 0)) {
                segments[i].push(make_pair(mn, sum));
                sum = 0;
                mn = 0;
            }
        }
        
        // only push on the first pair from THIS queue to the OVERALL priority queue
        if (segments[i].size()) pq.push(make_pair(segments[i].front().first, i));
    }

    // repeatedly increases x by taking segments
    while (pq.size() && pq.top().first + x >= 0) {
        // pops the least cost segment from the prioqueue (maximum negative cost)
        auto [mn, idx] = pq.top();
        pq.pop();

        // gets that segment from the list of queues, placing the next segment into the
        // prioqueue if one exists
        assert(segments[idx].front().first == mn);
        ll sum = segments[idx].front().second;
        segments[idx].pop();
        if (segments[idx].size()) {
            pq.push(make_pair(segments[idx].front().first, idx));
        }

        // adds that segment's sum to x
        x += sum;
    }
    cout << x << endl;
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
