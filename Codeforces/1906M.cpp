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
    /*
    - problem:
        - we are given an N-sided policy, and each side has A_i points on it, with none of those points lying
        on the side's endpoints
        - how many non-degenerate triangles can be made from these points, if no triangle overlaps sides with
        another?
    - solution:
        - if we have a dominating side, whose number of points is at least twice the number of all other sides'
        points summed up, then we clearly can only get as many triangles as the rest of the points, because
        each of those points can be joined with 2 points from the dominating side and that's the best we can do
        - if we don't, then it turns out, we can actually get the optimal number of triangles (meaning that there
        will only be sum(A)%3 points remaining which are not placed into triangles). we can do this by repeatedly
        finding the max-num-points side, taking 2 points from it, and joining them with an adjacent side's single
        point
            - why does this greedy strategy work? well, how could it fail? it might fail by leaving too many
            points on a single side, only allowing degenerate triangles remaining whereas another triangle
            construction strategy would consume all of the points properly. at a high level, this greedy strategy
            avoids that by "flattening" the maximum value across the array down, so that all sides have their
            number of points get (roughtly) "evenly flattened down".
            - also, when i say "adjacent side", i'm referring to the next adjacent side where some point exists
            - an intuitive strategy that wouldn't work here is to pick a side/corner to start from, then evenly
            raise a layer of triangles starting from there: 1 left with 2 right, 2 left with 1 right, 1 left with
            2 right, 2 left with 1 right, etc. in this case, instead of picking some location and propagating our
            triangles out from there, we repeatedly pick the max-num-points side and make a triangle out of it
    */

    int n;
    cin >> n;

    ll sum = 0, mx = 0;
    while (n--) {
        int a_i;
        cin >> a_i;
        sum += a_i;
        mx = max(mx, (ll) a_i);
    }

    if (mx >= 2 * (sum - mx)) {
        cout << sum - mx << endl;
    } else {
        cout << sum / 3 << endl;
    }
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
