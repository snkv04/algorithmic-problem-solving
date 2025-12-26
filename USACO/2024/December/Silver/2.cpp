#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

void solve() {
    /*
    concise solution summary:
    - we want to greedily remove trees toward the left of each interval, so first compute the max we can
    remove from each interval. then, when iterating through all points (trees and interval endpoints) from
    left to right, keep track of the most restrictive restriction at the current point, and remove a tree
    if we don't break it (so, as a result, we are greedily removing the earliest ones we can). to do this
    efficiently, the restriction for each interval should be in terms of total amount removed until current
    point, so as a result, we can just do one quick check using the total amount we've removed until the
    current point.

    overall solution idea:
    - in general, if we are passing through intervals from left to right (given some vague notion of
    "left to right", meaning that at a high level it doesn't matter if we are sorting by left or right
    endpoint), then for any given interval, among the points (trees) in that interval, we'd prefer to
    remove the trees toward the left.
        - suppose we had some intervals where each one requires a minimum number of points, and we want
        to maximize the total number of points we place. we can just place all points; that's a trivial
        problem.
        - suppose we had some intervals where each one only allows a maximum number of points, and we
        want to minimize the total number of points we place. again, we have a trivial solution; we 
        place no points, because that's the global minimum and it meets all of the intervals' conditions.
        - suppose we have some intervals where each one requires a minimum number of points, and we want
        to minimize the total number of points we place (where in this problem, "placing" a point is
        adding a tree). to do this, if we iterate over all intervals in increasing order of right-side
        endpoint, we want our points that we place to be as far right in each interval as possible while
        placing as few as possible. the reason for this is that we want each point to count toward fulfilling
        as many of the requirements as possible.
        - suppose we have some intervals where each one only allows a maximum number of points, and
        we want to maximize the total number of points we place (where in this problem, "placing" a point
        is equivalent to cutting down a tree). to do this, if we iterate over all intervals in increasing
        order of right-side endpoint, we want our points that we place to be as far left as possible. the
        reason for this is that we want each point to count toward as few restrictions as possible, so that
        we can place as many points as possible.
    - so, for each interval, we first precompute the number of trees we can REMOVE. this is just the
    original number of trees in the interval minus the number of them that we have to keep.
    - then, we iterate through all the trees and interval endpoints (though it just so happens to be
    the case that we literally don't have to do any processing at a right endpoint, since the later
    priority queue logic will recognize if we passed a restriction's right endpoint), and for each one,
    we make sure to first keep track of all restrictions (in a way that allows us to look at the most
    restrictive one, or in other words, the one that allows us to remove the least number of trees),
    and then (if we are at a tree) cut it down if we don't bypass any restrictions.
        - in simple terms, we cut down trees as early as possible for each interval.

    questions:
    - why do we focus on cutting down trees and not adding them in? if we iterate over intervals from
    left to right (for instance, let's assume the thing that is being sorted from left to right is
    the right endpoint), then when we add trees, we want to fill them in from the right side so that
    we get the rightmost trees. this makes us move overall from left to right, and then do an internal
    right-to-left pass for each interval. instead, if we want everything to be done in one pass, then
    by simply flipping the logic, assuming we are again moving through intervals from left to right,
    we want to remove the leftmost trees for each interval. so, we can do this in the same overall
    left-to-right pass, removing as many trees as we can before we can't anymore due to some interval
    saying we can't remove any more.
    - how do we keep track of how many trees we've removed in an interval? we keep track of how many
    overall trees we've removed, and for each interval, we also know the number of trees we've removed
    before its left endpoint.
        - this is basically prefix sum logic: the number of things in an interval to the left of our
        current pointer is equal to the total number of things to the left of our current pointer minus
        the number of things to the left of the left point of the interval (assumign the current pointer
        is in the interval).
        - we don't have to, at every event we encounter, update the number of trees we've cut down for
        EACH interval the event/point is covered by. it's sufficient to keep track of the number of trees
        we've cut down by the time of the current event as well as the number of trees we've cut down before
        the beginning of each interval, so then if we want to check the number of trees we cut down in any
        given interval, we can subtract those two values. we also don't have to check every interval; the
        prioqueue will tell us which one to check.
    - how do we stop the "number of trees removed in all intervals covering this point" counter from
    resetting? like suppose we have a long interval where we can only remove 5 trees, and the interval fully
    contains 10 different smaller intervals where we can only remove 1 tree from each of them. to avoid cutting
    down 10 trees within the 5-limit interval, we don't explicitly say "we can only cut down a total of 5 trees
    across this entire interval", we say "at any point in this entire interval, the total number of trees we've
    cut down since the very beginning cannot exceed (num_trees_before_left_of_interval + 5)". in other words,
    our limit is in the space of absolute values, not relative values, which is beneficial, because we never
    actually have to go back and check the restriction of each interval that is covering our current pointer;
    we just have to compare the number of trees cut down at our current pointer with the absolute value restriction
    from the prioqueue.
    */

    int n, k;
    cin >> n >> k;
    vector<int> x(n); for (int i = 0; i < n; ++i) cin >> x[i]; sort(x.begin(), x.end());
    vector<array<int, 3>> segments(k); for (int i = 0; i < k; ++i) for (int j = 0; j < 3; ++j) cin >> segments[i][j];
    sort(segments.begin(), segments.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[1] < b[1];
    });
    for (int i = 0; i < k; ++i) {
        auto &seg = segments[i];
        int l = seg[0], r = seg[1], t = seg[2];

        int lo = 0, hi = n-1, left = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (x[mid] >= l) {
                left = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        lo = 0; hi = n-1; int right = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (x[mid] <= r) {
                right = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        seg[2] = right - left + 1 - t;
    }
    // cout << "x = " << x << endl;
    // cout << "segments = " << segments << endl;

    vector<array<int, 4>> events; // (x-value, if tree or not, right side if not tree, limit if not tree)
    for (int xi : x) events.push_back({xi, 1, 0, 0}); // want trees after intervals, if x-value is same
    for (auto seg : segments) events.push_back({seg[0], 0, seg[1], seg[2]});
    sort(events.begin(), events.end());
    // cout << "events = " << events << endl;

    int ans = 0;
    priority_queue<pair<int, int>> restrictions; // (limit for max total trees cut, right-side endpoint of restriction)
    for (auto e : events) {
        int x = e[0];
        while (restrictions.size() && restrictions.top().second < x) restrictions.pop();

        if (e[1]) {
            // simply checks total amount removed, which is efficient compared to checking
            // the within-interval amounts for every interval covering this point
            if (restrictions.empty() || ans < -restrictions.top().first) {
                ++ans;
            }
        } else {
            restrictions.push(make_pair(-(ans+e[3]), e[2]));
        }
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
