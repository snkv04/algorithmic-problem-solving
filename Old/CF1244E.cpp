#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void solve() {
    // /*
    // we can binary search on the distance. how do we know if a distance is good? well, that
    // gets a little more into things. first off, if we are able to simultaneously maximize the
    // minimum element and minimize the maximum element, then that by default means that we are
    // minimizing the distance between the minimum and maximum elements. we can calculate the
    // number of operations needed to bring all elements up to above a certain threshold easily
    // if we assume that the thresholds we care about are on the given elements (after first sorting
    // the given array), because it's just a simple prefix sum computation. same thing for bringing
    // all elements to below a certain max for each max value that we care about. now, why would
    // we assume that we only care about intervals where at least one of the ends are on a value
    // in the input array? assume both ends (where each interval is a possible min and max value)
    // are each between some certain values in the given array. we can move the interval over in
    // whichever direction requires less operations added than subtracted until one of the ends
    // hits a value in the input array. in other words, if some interval with both ends not on
    // any value from the input array takes some certain number of operations, then we can construct
    // another interval WITH THE SAME LENGTH with at least one end on a value in the array by
    // using at most the number of operations we already used, meaning that if the original one
    // was valid, then an interval with at least one end on the input is also valid. this simplfies
    // things. now, we can just binar search on the length of the [min, max] interval, and for
    // each, we check over all possible left-side values and all possible right-side values. we
    // can't just do one of those two; why? because the distances between adjacent values in the
    // sorted input array are not uniform, so the rate of operations you need as you move the
    // minimum value to the right may not be distributed the same as the rate of operations you
    // need as you move the maximum value to the left. anyway, for a given left-side value, we
    // can find what index satisfies our fixed right-side value using another nested binary search,
    // and then we can use the prefix sums computed earlier to check the number of operations.
    // same for the right-side.

    // the problem asks to minimize the distance from min to max, and we instead try to maximize
    // the min and minimize the max. how can this be generalized? maybe, if there is something to
    // optimize, break it down into the separate aspects that can each contribute to the optimal
    // solution of the original target, and see if they can all be achieved at once or individiually
    // in some order that prioritizes more important ones.
    // */

    // int n;
    // ll k;
    // cin >> n >> k;
    // vector<int> a(n, 0);
    // for (int i = 0; i < n; ++i) {
    //     cin >> a[i];
    // }
    // sort(a.begin(), a.end());
    
    // vector<ll> tomin(n, 0), tomax(n, 0);
    // tomin[0] = 0;
    // for (int i = 1; i < n; ++i) {
    //     tomin[i] = tomin[i-1] + ((ll) i * (a[i] - a[i-1]));
    // }
    // tomax[n-1] = 0;
    // for (int i = n-2; i >= 0; --i) {
    //     tomax[i] = tomax[i+1] + ((ll) (n-1-i) * (a[i+1] - a[i]));
    // }

    // ll l = 0, r = 1e9-1, mindist = -1;
    // while (l <= r) {
    //     ll mid = (l + r) / 2;
    //     bool works = false;
    //     for (int i = 0; i <= n-1; ++i) {
    //         ll aj = a[i] + mid;
    //         ll l2 = i, r2 = n-1, j = -1;
    //         while (l2 <= r2) {
    //             ll mid2 = (l2 + r2) / 2;
    //             if (a[mid2] >= aj) {
    //                 j = mid2;
    //                 r2 = mid2 - 1;
    //             } else {
    //                 l2 = mid2 + 1;
    //             }
    //         }

    //         if (j == -1) {
    //             if (tomin[i] <= k) {
    //                 works = true;
    //                 break;                        
    //             }
    //         } else {
    //             ll ops = tomin[i] + tomax[j];
    //             ll additional = (a[j] - aj) * (ll) (n-1 - j + 1);
    //             ops += additional;
    //             if (ops <= k) {
    //                 works = true;
    //                 break;
    //             }
    //         }
    //     }
    //     for (int j = n-1; j >= 0 && !works; --j) {
    //         ll ai = a[j] - mid;
    //         ll l2 = 0, r2 = j, i = -1;
    //         while (l2 <= r2) {
    //             ll mid2 = (l2 + r2) / 2;
    //             if (a[mid2] <= ai) {
    //                 i = mid2;
    //                 l2 = mid2 + 1;
    //             } else {
    //                 r2 = mid2 - 1;
    //             }
    //         }

    //         if (i == -1) {
    //             if (tomax[j] <= k) {
    //                 works = true;
    //                 break;
    //             }
    //         } else {
    //             ll ops = tomin[i] + tomax[j];
    //             ll additional = (i + 1) * (ll) (ai - a[i]);
    //             ops += additional;
    //             if (ops <= k) {
    //                 works = true;
    //             }
    //         }
    //     }

    //     if (works) {
    //         mindist = mid;
    //         r = mid - 1;
    //     } else {
    //         l = mid + 1;
    //     }
    // }
    // cout << mindist << "\n";

    /*
    alternative solution:
    initialize the min and max, moving them inward by greedily selecting whichever one
    you can move farthest inward with the fewest operations. the two sides can be sorted
    by whichever one is moving the fewest number of elements. then, at the end, if we can't
    move either side completely to the next inward element, then use the remaining operations
    from the original k to move whichever side is cheaper.

    why is it better to just focus on moving the side with fewer elements to move? well,
    what are the components of this "moving" operation? suppose we're moving the minimum
    to a greater value. the components are the number of elements and the distance. the
    distance is the part that we actually care about, since we want to minimize max-min and
    moving min far will minimize this value. now, to answer the question: to move the same
    distance, the one with more elements to move will take strictly more operations.
    this is always true across all operations, and each operation will not negatively impact
    any future operations, so we can follow this greedy strategy.

    well, why will each operation not negatively impact future operations? the target, or
    objective, is to minimize the value of |max-min|. all that we can do is move the min
    or max inward, and doing one step of this with the minimum possible operations will
    allow for the most possible future operations. we can justify that this greedy strategy
    won't create a suboptimal path for future operations by recognizing that each successive
    operation will only require more and more elements to be moved over, so then it won't be
    the case that we'll see some greedily less effective operation earlier on that leads to
    a later very efficient operation that ends up with a globally optimal solution, like is
    often the case in dynamic programming. this algorithm basically is like having two
    options for operations constantly, where each one continuously either gets more costly
    or remains the same cost. in other cases, where each operation might get better or worse,
    i think a greedy solution like this wouldn't work.

    one tiny caveat to point out in the implementation, which i previously made a mistake with:
    i said we want to move whichever side requires moving the less elements, but if that side
    doesn't work, then we don't want to instead move the other side, we simply want to instead
    break out of the loop and enter the final pipeline where we calculate the remaining moves
    that we have. suppose we have to move 3 elements on the right for a distance of 20 whereas
    we have to move 4 elements on the right for a distance of 1, and we have 30 operations left.
    we don't want to move the right, and we instead want to break out of the loop, because that
    final stretch of moving the left as far right as possible before printing the solution will
    reduce the final value more than we will get from moving the right just because we can
    move the right at that current moment. in other words, in a more general way, when one condition
    fails and you choose to take the "else" branch, check to see if that else branch is viable
    (meaning you can perform that operation) and optimal (meaning you should perform that operation).
    in this case, i just had to place more strict conditions to actually check for exactly what
    i wanted when moving the l to the right and r to the left, and choosing to break out of the
    loop at the correct time (when neither of those conditions were met).

    in fact, the way this works means that we alternatingly move the left side then the right side in,
    so the operations can actually be replaced by doing them both at once until we can't anymore, but
    that fact doesn't affect the correctness of this existing solution.

    okay, now how could i come up with this quicker solution than the one with two nested binary searches?
    (it can actually be implemented with no binary searches by reversing the order of some loops and taking
    the minimum working distance found, but that's not that important.) basically, for the first solution,
    we know that we want to minimize the |max-min| and that minimizing that is the same as if we are able
    to simultaneously maximize the min and minimize the max, so we can run binary search on the final dist
    and check if each distance works by using the operations most optimally with the idea of bringing up
    elements to the min and bringing down elements to the max. for the second solution, we know that we
    want to minimize the value of |max-min|, so we can move the max and min inward as much as possible. it
    relies on the idea that as we move each side further inward, we'll have to push along more and more
    elements each time, so pushing in the outward elements greedily until we can't anymore is fine since
    those elements have the least elements to push inward, and we can choose to either alternate between
    the left and right sides being pushed in (since one of them will always have the least elements to
    push in) or just do them both at once since they increase the number of elements at the same rate in
    accordance with the indices in the array, even if the distances that they have to be pushed on the
    left vs. the right are uneven. in simpler terms, to come up with this solution, recognize that we
    always get the GREATEST OUTPUT (in terms of reducing the |max-min| difference) by using the operations
    to move the outermost indices to the next inner indices, so we can construct a simple greedy algorithm
    out of that instead of doing that more "standard" binary search method.
    */
    int n; ll k;
    cin >> n >> k;
    vector<ll> a;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        a.push_back(ai);
    }
    sort(a.begin(), a.end());
    // print_container(a, "a = ");

    ll l = 0, r = n-1;
    while (l < r && k > 0) {
        ll ld = a[l+1] - a[l], rd = a[r] - a[r-1]; // left diff, right diff
        ll le = l + 1, re = n - r; // left elements, right elements
        ll lops = ld * le, rops = rd * re;
        if (min(lops, rops) <= k) {
            if (le <= re && lops <= k) {
                k -= lops;
                ++l;
            } else if (re <= le && rops <= k) {
                k -= rops;
                --r; 
            } else {
                break;
            }
        } else {
            break;
        }
    }
    if (l == r) {
        cout << "0\n";
    } else {
        ll le = l+1, re = n-r;
        ll elems = min(le, re);
        ll steps = k / elems;
        cout << max((ll) 0, a[r] - a[l] - steps) << "\n";
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
