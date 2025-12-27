#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    /*
    - in the regular "select max number of non-overlapping intervals" problem, where the intervals are fixed,
    we want to greedily select the earliest ending one, specifically because that always gives the most options
    for future intervals to be selected. it's similar in this problem: each interval has some specified location
    but can be moved as far as we want to the left as long as the start point is nonnegative, so we iterate
    through intervals in increasing order of latest possible end time (in specific, the part where we do this is
    when we are looping through the intervals to see if we should add them to our set or not), and as a result,
    we create the most possible options for future intervals. in fact, if we are on the k'th interval in order
    of s_i+t_i, then the set of intervals we've chosen won't necessarily end at s_k+t_k, but at some point <=s_k+t_k,
    creating even more space for future intervals (to the right).
        - be more specific: what do i mean when i say "create the most possible options"? if we have iterated
        over 7 different intervals, then compared to any other ordering, if we had iterated over the 7 intervals
        with the earliest possible latest-possible-end-time, then there will be the most space to the right of
        all of those 7 intervals, meaning that there will be more (or the same) options for future intervals
        compared to if we had done another ordering. in other words, the "flexibility" or "number of options" we
        create by going with this ordering is based on the set of intervals we can pick in the future.
    - how is the fact that we can move intervals to the left important? greedily, we would want to move them
    as far to the left as possible, so in the end, our intervals will all be pushed up against each other with
    the leftmost one being pushed against 0.
    - one of the key observations is that, for a given current interval, if we are iterating over the intervals
    in increasing order of rightmost-possible right endpoint, and if we include the current interval, then
    (1) the sum of taken lengths should be leq the rightmost-possible right endpoint (where we just use the
    sum because we assume we can simply push everything to the left), and (2) that condition must hold true
    for all previous intervals as well. once we have that, we can simply use the greedy set-cardinality-maximizing
    strategy to get as many intervals as possible
    
    generalizable ideas:
    - if you are doing a problem where you want to construct some solution, then check if the following is true:
    for any constructed solution, you can make another solution that is just as optimal or more optimal using
    some different structure. if that is true, then just try to always construct a solution with that structure,
    because always using that structure will let you reach the optimal solution (since there can't be another
    solution that's better which can't be mapped to one with that structure)
    - this pattern appears in multiple problems: we want to construct a set whose size (by number of elements)
    is maximized, so no element is more valuable to take than any other. therefore, we can iterate through the
    elements we can take, and our strategy is greedy: if we can take the current one then we do, and if we can’t
    then see if we can reduce our cost (without reducing our set size) by dropping one of the elements we’ve taken
    and replacing it with the current one. it’s optimal because:
        - if we can take it, then we do, which is the best we can do
        - if we can't take it, then we don't reduce our current value toward the quantity we are trying to
        maximize (the set's size), but we do increase the possibility of getting more elements in the future
        by reducing the cost (through dropping the costliest element)
        - if we need to drop more than 1 element to add the current one in, then adding the current one in
        is simply suboptimal (because the size of our set strictly decreases)
    */

    int n;
    cin >> n;
    vector<pair<ll, ll>> jobs;
    for (int i = 0; i < n; ++i) {
        pair<ll, ll> p;
        cin >> p.first >> p.second;
        jobs.push_back(p);
    }
    sort(jobs.begin(), jobs.end(), [](const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
        return p1.first + p1.second < p2.first + p2.second;
    });

    ll timesum = 0;
    priority_queue<ll> used;
    for (auto job : jobs) {
        used.push(job.second);
        timesum += job.second;
        if (timesum > job.first + job.second) {
            timesum -= used.top();
            used.pop();
        }
    }
    cout << used.size() << endl;
}

int main() {
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}