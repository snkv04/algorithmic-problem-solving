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

ll gcd(ll a, ll b) {
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

// // original solution
// void solve() {
//     ll xb, yb;
//     cin >> xb >> yb;
//     ll g = gcd(xb, yb);
//     ll dx = xb / g, dy = yb / g;
//     if (dx == xb && dy == yb) {
//         cout << "Yes\n";
//         return;
//     }

//     ll x1, y1, x2, y2;
//     cin >> x1 >> y1 >> x2 >> y2;
//     if (x1 <= dx && y1 <= dy && x2 >= dx * (g-1) && y2 >= dy * (g-1)) {
//         cout << "Yes\n";
//     } else {
//         cout << "No\n";

//         // round up bottom left and round down top right
//         ll xleft = ((x1 + dx - 1) / dx) * dx;
//         ll xright = (x2 / dx) * dx;
//         ll ybottom = ((y1 + dy - 1) / dy) * dy;
//         ll ytop = (y2 / dy) * dy;

//         // convert "y"s to "x"s
//         xleft = max(xleft, (ybottom / dy) * dx);
//         xright = min(xright, (ytop / dy) * dx);

//         if (xleft > xright || xleft > dx) {
//             cout << dx << " " << dy << "\n";
//         } else {
//             ll treex = xright + dx;
//             ll treey = (treex / dx) * dy;
//             cout << treex << " " << treey << "\n";
//         }
//     }
// }

// extended solution
void solve() {
    /*
    summary of how to solve this if there are multiple rectangles of trees being cut out:
    - first, we can observe that the trees on the line from (0, 0) to (xb, yb) are the only
    ones that could possible be in the way. they're on a straight line, so we only have to
    consider those
        - which ones are these? namely, what pattern do they all follow? if we reduce xb and yb
        to be coprime by dividing by their gcd, then each of these trees will have their coordinates
        be multiples of these coprime numbers, which we can choose to call dx and dy
    - this provides a simple brute-force algorithm: we maintain a set of all these trees. for each
    rectangle, we identify which trees will be overlapping with this rectangle, and remove them all
    from the set. this is O(n*m), where m is the number of trees on the path (so gcd(xb, yb), which
    can be up to 10^12) and n is the number of rectangles (which, idk, i set to be up to around 1e5)
    - however, what we're basically doing is having a series of points that we repeatedly remove a
    large contiguous segment from. with a quick flip of perspective, we're repeatedly adding contiguous
    points to a set. to speed this up, we can observe that each rectangle has a single segment of points
    that it overlaps (which might be empty), and then convert the operations to repeatedly adding these
    segments to a set, where the set only has nonoverlapping segments at any given time.
        - the segments are simply defined by a left and right, and since the trees we are about are all
        on a simple line, we can convert all y-values to x-values (i.e., for a given tree, extract the
        x-value based on the y-value, which is unique since none of the trees on the line share an x-value
        or a y-value), and then have the segments use these x-values
        - for example, if a rectangle covers the trees (6, 18), (8, 20), (10, 22), then the segment that it
        covers is [6, 10]. another option is to only use half-open intervals where each single unit in the
        x-axis has a size of dx, so that in this example the interval of trees would be [6, 12), but i chose
        not to do that this time
        - by the way, for a given rectangle, we can identify the segment of trees (indexed by their x-values)
        that it overlaps by finding the x-interval it covers, finding the y-interval it covers (converted to
        an x-interval so the two intervals can be easily compared), and then taking the overlap of the two
        intervals
    - this optimizes the process to O(n log n), since for each segment, it will be added <= 1 time and
    deleted-then-merged into another segment <= 1 time, while operations on the set are each O(log n) since
    we're using a sorted map to map from l to r for each segment
    */

    ll xb, yb;
    cin >> xb >> yb;
    ll g = gcd(xb, yb);
    ll dx = xb / g, dy = yb / g;
    if (dx == xb && dy == yb) { // no trees between (0, 0) and (xb, yb)
        cout << "Yes\n";
        return;
    }

    int n = 1; // should work up to around 1e5?
    // std::cin >> n;
    map<ll, ll> segments; // closed intervals indexing x
    while (n--) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // take the box and identify which stepping-stone trees on the line to (xb, yb) it covers

        // first, round up bottom left and round down top right
        ll xleft = ((x1 + dx - 1) / dx) * dx;
        ll xright = (x2 / dx) * dx;
        ll ybottom = ((y1 + dy - 1) / dy) * dy;
        ll ytop = (y2 / dy) * dy;

        // then, convert "y"s to "x"s
        xleft = max(xleft, (ybottom / dy) * dx);
        xright = min(xright, (ytop / dy) * dx);

        // now, add the segment of trees that it removes to the ordered list of segments
        if (xleft <= xright) {
            // merge with left side
            auto toleft = segments.lower_bound(xleft);
            if (toleft != segments.begin()) {
                --toleft;
                if (toleft->second >= xleft - dx) {
                    xleft = min(xleft, toleft->first);
                    xright = max(xright, toleft->second);
                    segments.erase(toleft);
                }
            }

            // merge with right side
            auto toright = segments.upper_bound(xright);
            if (toright != segments.end() && toright->first == xright + dx) {
                xright = max(xright, toright->second);
                segments.erase(toright);
            }

            // remove any segments that overlap with this one
            auto other = segments.lower_bound(xleft);
            while (other != segments.end() && other->first <= xright) {
                auto temp = other;
                ++other;
                xright = max(xright, temp->second);
                segments.erase(temp);
            }

            segments[xleft] = xright;
        }
    }

    // now, just validate if the first segment covers all trees between (0, 0) and (xb, yb)
    auto firstsegment = segments.begin(); // segments.lower_bound(dx);
    if (firstsegment != segments.end() && firstsegment->first == dx && firstsegment->second >= xb - dx) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
        if (firstsegment == segments.end() || firstsegment->first > dx) {
            cout << dx << " " << dy << "\n";
        } else {
            ll treex = firstsegment->second + dx;
            ll treey = (treex / dx) * dy;
            cout << treex << " " << treey << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
