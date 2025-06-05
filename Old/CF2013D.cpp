#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::pair<T, T> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void solve() {
    /*
    observations:
    sum of whole array stays the same
    average of whole array stays the same
        given the average of some array, we have some element that's at most the average and some
            element that's at least the average
    we're basically pushing individual 1s to the right. what this means is that for a prefix of
        the array, we can make its sum less but not more. for a prefix of the array, we can spread
        out elements toward the right and not toward the left

    solution:
    imagine that the array is a bar graph, with each bar corresponding to the array's element at
    that index. then, each operation keeps the overall sum of the array the same, and it visually
    looks like moving a unit from one bar to the bar to the right. this can propagate, moving from
    a bar to another way to the right. even though it's possible, we wouldn't want to make any bars
    negative, since there's no point in making the minimum value of the array less than what it
    already is and the given minimum input value is 1. anyway, it's clear that there's no point in
    moving any units from a lower left bar to a higher right bar, since this just unnecessarily
    increases the gaps between elements. so, we can make our goal to make the array non-decreasing.
    we can do this by iterating from left to right, and each time we see an element that's less than
    the largest seen element to the left of the current element, we shift all of the units from the
    bars to the left so that it's even, and any remainder of units can be put on the right side of
    that "rectangle" of bars since we want the overall arrangement of the bars to be non-decreasing.
    to do this efficiently, by the way, we want to store these "rectangles" of bars whose heights are
    all the same in a single element, and this can be done by storing the monotonically non-decreasing
    bars as pairs for width and height.
    how do we know that making the graph non-decreasing is optimal?
    let's look at a few edge cases. first, if the min element is the first element and the max is the
    last, then there's clearly no point in doing any operations at all, since those would either do nothing
    or further expand the discrepancy. if the array is strictly decreasing at a constant rate, then we
    could simply try getting all of the bars to be even. having all the bars at the same height would
    decrease the distance between the min and max, right? well, if there are some bars to the left that are
    really low and some to the right that are really high, then we can't do anything about those when we
    can only move things from left to right. so, for each streak of decreasing bars, we can make those
    as close to equal as possible. however, we can actually generalize this, because instead of only
    looking at decreasing contiguous streaks from the input, we can ensure that each prefix that we
    look at is nondecreasing, and at each current element, if it's less than some elements of the prefix,
    then we can even out all portions that we can using the space we get from that small current element.
    this gets the bars to be as close to equal as possible under the restraints of the given operation.
    what's potentially generalizable to other problems here?
    the idea of condensing a monotonically nondecreasing array into a stack that holds counts. the idea
    of getting things as close to equal as possible with remainders, which still factor into the stack
    being non-decreasing, because having equal elements minimizes the difference between max and min.
    could modifying various adjacent bars to their average actually be disadvantageous?
    let's look at a case like 5,5,5,5,1,10. if we run the solution above, then this ends up in
    4,4,4,4,4,10. yes, it's true that 4 elements decrease their value while the max stays the same, but
    the minimum value (which is the one that most matters) increases, reducing the overall |max-min| of
    the array. in general, setting all the elements to their average (plus or minus 1, because of the
    remainder when dividing by the number of columns to distribute over) brings all the elements closer
    to the middle, reducing the range between the min and max. in other words, even in this case, it's
    optimal. keep in mind where the max and min that we want to bring to each other are, and if we divide
    into all cases (where the max is on the left and min is on the right, other way around, etc.), we
    can see that this works every time. maybe some values might change in ways that initially don't look
    good, but if we focus on the values holding the extrema (which are the parts of the current state
    of the array that most contribute to the final output), then it actually ends up working like we want.
    */

    // int n;
    // cin >> n;
    // vector<pair<ll, ll>> s;
    // s.push_back(make_pair(0, 1e18));
    // for (int i = 0; i < n; ++i) {
    //     ll ai;
    //     cin >> ai;
    //     ll cnt = 1, sum = ai, popped = 0;
    //     while (s.size() && s.back().second >= (sum / cnt)) {
    //         pair<ll, ll> top = s.back();
    //         s.pop_back();
    //         cnt += top.first;
    //         sum += top.second * top.first;
    //         ++popped;
    //     }

    //     // cout << "i = " << i << ", popped = " << popped << ", cnt="<<cnt<<", sum="<<sum<<"\n";
    //     // print_container(s, "after popping: ");
    //     ll rem = sum % cnt;
    //     s.push_back(make_pair((cnt - rem), sum / cnt));
    //     if (rem) {
    //         s.push_back(make_pair(rem, 1 + sum / cnt));
    //     }
    //     // print_container(s, "after pushing: ");
    // }

    // ll mx = s.back().second, mn = 1e18;
    // while (s.size()) {
    //     auto pair = s.back();
    //     s.pop_back();
    //     mn = min(pair.second, mn);
    // }
    // cout << mx - mn << "\n";

    /*
    alternate solution:
    we want to minimize the diff between max and min, so we can try to find the maximum min attainable
    as well as the minimum max attainable. to do this, just use binary search for each. to see if some
    value is a possible maximum, we can move from left to right, moving as much as needed from the current
    element to the next to ensure it's below the threshold, and check if the last element fits. similar
    for the min.
    what's possibly generalizable here?
    we are trying to take the elements and fit them all under some threshold. this process
    is similar to carrying over digits, where the leftovers from many elements will propagate
    to the next one until, after possibly many elements, we "run out of steam" and there is
    no leftover. therefore, if propagating the leftovers from left-to-right for instance, then
    we can kind of separate the entire array into "segments" of elements across which all elements
    in the segment are exactly the maximum threshold and the last element of the segment is a
    value less than the threshold.
    how can we know that the min max and max min are both achievable at the same time?
    this isn't a rigorous proof, but here's some intuition drawing on the pattern described
    in the answer to the previous question. we are binary searching on the smallest upper bound
    and largest lower bound for the elements to all fit between. at some point, if those get
    too close, then those "segments" will be squashed too wide and the overflows from the
    elements in the segment will no longer fit in the area between those two horizontal lines
    and will be pushed out of the array. if we only take a look at minimizing the upper bound,
    then if it gets too low, the last segment will overflow out of the bound too far high up.
    the construction of the array when bringing those two lines together eliminates the
    empty space between them as much as possible. that gives a nice visual picture. however,
    when optimizing each of those two horizontal lines separately, it should be notced that
    the construction of the array in those two cases (first from left-to-right and then
    from right-to-left) will probably not look the same, because in the first each segment
    has all elements except the last be pushed to the top, while in the second pass each
    segment has all elements except the first be pushed to the bottom.
    possibly useful ideas from the editorial(s):
    given that the operations boil down to shifting units from the left to the right, we
    know that a prefix will all fit under an upper bound if the sum of that prefix is leq
    the width times the upper bound.
    */

    // int n;
    // cin >> n;
    // vector<ll> a;
    // for (int i = 0; i < n; ++i) {
    //     ll ai;
    //     cin >> ai;
    //     a.push_back(ai);
    // }
    // ll minmax = -1, l = 0, r = 1e15;
    // while (l <= r) {
    //     ll mid = l + (r - l) / 2;
        
    //     vector<ll> copy = a;
    //     for (int i = 0; i < n-1; ++i) {
    //         if (copy[i] > mid) {
    //             ll rem = copy[i] - mid;
    //             copy[i+1] += rem;
    //             copy[i] -= rem; // optional
    //         }
    //     }

    //     if (copy[n-1] > mid) {
    //         l = mid + 1;
    //     } else {
    //         minmax = mid;
    //         r = mid - 1;
    //     }
    // }
    // ll maxmin = -1; l = 0; r = 1e15;
    // while (l <= r) {
    //     ll m = l + (r - l) / 2;

    //     vector<ll> copy = a;
    //     for (int i = n-1; i >= 1; --i) {
    //         if (copy[i] < m) {
    //             ll need = m - copy[i];
    //             copy[i-1] -= need;
    //             copy[i] += need; // optional
    //         }
    //     }

    //     if (copy[0] < m) {
    //         // mid too high
    //         r = m - 1;
    //     } else {
    //         maxmin = m;
    //         l = m + 1;
    //     }
    // }
    // cout << minmax - maxmin << "\n";

    /*
    another alternate solution:
    drawing from the previous solution, we can try minimizing the max and maximizing the min. however,
    we don't need binary search for this. we can find each of these values in its own linear pass.
    we know that the sum of the array stays equal for any operation. for a given prefix of the array,
    we can observe that the sum of the prefix either stays the same or decreases (by some value of 1
    moving from the prefix into the suffix). symmetrically, the sum of any suffix either stays the
    same or increases. remember how we would "even out" some set of contiguous elements by setting
    them to be the average, only if we could move things from left to right to get to that stage
    (since it's pointless and unhelpful to move something from an already lower value to an already
    higher value)? we can do something similar here, but there's a very subtle difference between this
    and the first solution that is subtle in concept but very different in implementation.
        let's first look at some context. we want to maximize the min, for example, but the issue is
    that some elements already being quite low compared to the stuff on its right can make the min
    really low. in other words, we are constrained by how far up we can make the min (which is intuitive,
    since we are trying to maximize it). if we have a bunch of elemtns with approximately the same
    value and something really low to the right, then we can relax that low value up a little by moving
    some elements into it, but if we have a really low value to the left then we can't do anything
    about it. we noted that each prefix can only move down in sum, so for each prefix, if we can
    only decrease the sum, what's the maximum min value it can have?
        here's the difference between this and the first solution. in the first solution, we only
    turned blocks of elements into their average (with the remainders causing some elements to be
    higher) if they could allow that, meaning that the block was previously nonincreasing. with this,
    we'll look at prefixes, and say that the maximum possible min value for that prefix is the average
    of the whole prefix. then, to find the actual maximum-possible minimum value, we take the min across
    all of those. why is this allowed? well, the idea is that there is at least one value that's less
    than or equal to the average, so if we do this, then since the thing we are actually targeting is
    the min, the min will be correct anyway (since lower values to the left won't have been brought up
    in previously-looked-at prefixes when scanning left to right). in other words, for a low value toward
    the right, the higher values to the left will be included in the prefix so then we can use those to
    smooth out that really low value, but for a low value to the left, there will be a prefix that
    doesn't yet include the higher values to the right so it can't be smoothed out yet. even though,
    for the case of the right-side low value, it's incorrect to say that the maximum possible min
    value is the average of ALL the elements in the prefix, it IS correct to say that it will be the
    minimum between the average of ALL the elements in the prefix and the max possible min value for
    the previous prefix. what do those two cases really represent? if there was a low value to the
    left (either from a really low value on the first element or a previous prefix with a low average),
    then the former case would be lower and the latter doesn't even matter, but if all previous prefixes
    had a higher max-possible-min than the average of this prefix, then that means that THIS CURRENT
    ELEMENT is the one dragging everything down, and the lower value will be the average value of
    the whole prefix. THAT'S the key idea here. intuitively, it seems like that average formula doesn't
    always apply, but in the cases where it doesn't, we're not even using that formula for the final
    computed value; the one that's lower (and gets taken as the min) is the previous prefix's value
    for the maximum possible minimum value.
    why are we using prefixes (and suffixes) in the first place?
    basically, it's kind of like DP; if we compute the maximum-possible-minimum for the first k elements,
    then we can do that until we arrive at the last element and then that applies for the whole array.
    how is this generalizable?
    when doing an operation that takes in multiple arguments, such as min() or max(),
        consider in WHICH CASES either argument will end up propagating to be the result
        of the operation. in this problem, if there's a left value less than the current
        value (and we are taking left values to assume that we have already done as many
        operations as needed to smooth out the stuff to the left, because we know that
        doing that does not stop us from constructing an optimal scenario at the current
        step), then that value would be less than the average across the whole prefix so
        even though we couldn't smooth out the whole prefix and take the average so the
        average function is wrong we could still use the average function, and also if
        the current value is the minimum value across the hwole prefix, then we can take
        the average (and it can possibly be less than or equal to the min seen from the prefix).
        this means that in the scenarios where each respective argument propagates to be
        the final return value, the overall min would still follow this formulation as
        a simple min function. in other words, and in simpler terms, even though that
        formula can be coded as checking cases, it can be shortened to be more readable
        (though possibly harder to understand the intuition behind) by just using a
        simple min function.
    when trying to find the maximum of some value, one common way is to initialize the
        max to some original value then repeatedly set it to the max of itself and the
        next thing being looked at. this effectively takes the max across all of those
        things. another way to do this in a situation where we are trying to take the
        max of something but are being restricted by constraints is initializing the max
        to a large value then repeatedly relaxing how large we can keep it (i.e., reducing
        it) each time we place a constraint on it. these two methods operate in separate
        situations. the main visible difference between them is that in the first, we
        are taking a max at each step, while in the second, we're taking a min at
        each step even though we're trying to find the max, but this is basically just
        because we're placing constraints on the maximum value possible.
    how could i come to this on my own?
    well, we know we want to maximize the min and minimize the max, possibly at the
    same time. how could we maximize the min? since operations increase the thing on
    the right, we will move from left to right as, for each prefix, we know all of the
    amount that we are working with (to propagate rightward). okay, now for a given
    prefix, what do we actually want to do? we know that we want it to be nondecreasing,
    as if it isn't then we can make the solution no worse by causing it to be nondecreasing.
    also, for a given set of elements, the best case (where the min and max are closest)
    is when all of the elements are equal, but if there's a remainder then we can put
    the ones which are 1 larger on the right side of that section. now, for a given prefix,
    the maximum we can get its minimum to be if the lowest element (after all operations
    on the left) on the left is less than the current element would be that lowest element,
    while if the lowest element is the current element then we can smooth it out by getting
    the average across the prefix and the minimum would be that average, UNLESS the previous
    prefix minimum is already lower than than (in which case, we can't really do anything
    about that). if there is a remainder when dividing by the length of the prefix, then
    the maximum minimum would be the average without the +1 (while for the maximum when
    going from the right side, the minimum maximum would be the rounded-up average). the
    same logic can be applied when finding the minimum maximum with appropriate symmetrical
    changes. this algorithm actually optimizes both problems at once. the final answer is
    just the difference between the two optimized values.
    */

    int n;
    cin >> n;
    vector<ll> a(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll maxmin = a[0], minmax = a[n-1];
    ll sum = a[0];
    for (int i = 1; i < n; ++i) {
        sum += a[i];
        // the if condition here isn't needed. it's necessary for it to be
        // true for the average term to be lower than the previous maxmin,
        // so it will be true anyway if the average formula has any impact
        // on the answer, but it's not actually sufficient (look at the first
        // 3 elements of the 5th test case)
        // if (a[i] < maxmin) {
            maxmin = min(maxmin, sum / (i + 1));
        // }
    }
    sum = a[n-1];
    for (int i = n-2; i >= 0; --i) {
        sum += a[i];
        // if (a[i] > minmax) {
            minmax = max(minmax, (sum + n - i - 1) / (n - i));
        // }
    }
    // cout << "minmax = " << minmax << ", maxmin = " << maxmin << "\n";
    cout << minmax - maxmin << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
