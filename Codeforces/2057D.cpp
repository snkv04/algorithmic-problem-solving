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

struct SegmentTree {
private:
    int n;
    vector<array<ll, 3>> t; // min of segment, max of segment, max val of (a[i2]-i2)-(a[i1]-i1), where i2>=i1
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        // fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v][0] = t[v][1] = a[l];
            t[v][2] = 0;
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v][0] = min(t[2*v][0], t[2*v+1][0]);
        t[v][1] = max(t[2*v][1], t[2*v+1][1]);
        t[v][2] = max({
                t[2*v][2],
                t[2*v+1][2],
                t[2*v+1][1] - t[2*v][0]
        });
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return -1e9;
        }
        if (ql <= l && r <= qr) {
            return t[v][2];
        }

        int m = l + (r - l) / 2;
        return max(
                _query(2 * v, l, m, ql, qr),
                _query(2 * v + 1, m + 1, r, ql, qr)
        );
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v][0] = t[v][1] = val;
            t[v][2] = 0;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v][0] = min(t[2*v][0], t[2*v+1][0]);
        t[v][1] = max(t[2*v][1], t[2*v+1][1]);
        t[v][2] = max({
                t[2*v][2],
                t[2*v+1][2],
                t[2*v+1][1] - t[2*v][0]
        });
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

void solve() {
    /*
     * we have an array and a series of queries, where each query just updates an element in the array
     * to a new value. what we want to do after each query (and just a single time before all queries)
     * is compute the maximum of (range - (length - 1)) across all segments of the array.
     *
     * solution:
     * - first we can clearly identify that the segment we care about will have the minimum on one side
     *   and the maximum on the other side, and if that's not the case then we can tighten the segment
     *   to optimize the end value that we care about from that segment
     * - now, there are two cases. either the minimum is on the left side and the maximum is on the right
     *   side, or vice versa. let's assume that the maximum is on the right etc., and the other case will
     *   be explained below
     * - now, we can take the expression that we want to maximize and, since the max is on the right side,
     *   we can write it as ((a[r] - a[l]) - (r - l))
     * - we can then rewrite this to ((a[r] - r) - (a[l] - l)), which is useful because it allows use to
     *   compute l and r indepdently. why does this matter? we are trying to maximize a difference, which
     *   means that we can maximize the first term and minimize the second term
     * - now, a promising approach would be to just find the maximum value of a[i]-i and the minimum value
     *   of that, and then subtract them. this can be done using a segment tree, and this additionally
     *   seems promising because the segment trees can be efficiently updated and queried for each of the
     *   queries in the problem
     * - however, the problem with this is that the maximum might not end up being the one on the right,
     *   which means that one of the two parts (calculating the range or calculating the length) might be
     *   inverted
     * - what really is the fix for this? well, all we have to ensure is that the first term (which depends
     *   on r) has its "r" value be to the right of the second term (which depends on l)
     * - let's identify what exactly we want to do. we want to, under the constraint that r >= l, find the
     *   maximum possible value of (a[r] - r) and the minimum possible value of (a[l]-l), and then just
     *   subtract them. how can we do that?
     * - well, observe the fact that segment trees are (obviously) not just used for computing such values
     *   over the whole array. if we want to find the maximum of (a[i]-i) over the whole array using a
     *   segment tree, then that is just a special case of the fact that the segment tree can do this for
     *   any possible segment of the array.
     * - so, for any given segment of the array, we can compute the maximum of (a[i]-i) where i is in that
     *   segment, the minimum of (a[i]-i), and the actual expression that we want (which ensures that r >= l).
     *   how to do that last part? well, it's simple. if we assume that it is true for both children nodes
     *   of a given node, then to calculate that value for a segment, it would be the max of that value from
     *   the left half, that value from the right half, and (max of a[i]-i for some i in the right half) minus
     *   (min of a[i]-i for some i in the left half). this is a really cool concept that imposes the order of
     *   r and l, and it does this from the ground up (starting from segments of length 1 to length 2, then to
     *   4 and 8 and any arbitrary length that isn't even a power of 2 because of how segment trees work!).
     * - now, what we have is the value we want to compue for any segment of the array, as well as the minimum
     *   of (a[i]-i) for any segment and the maximum of (a[i]-i) for any segment. this is all we need to answer
     *   the queries if r >= l.
     * - now, what if l >= r? what changes have to be made? this is also another cool concept. basically, imagine
     *   that we reverse the array. now, the situation is the exact same as before: the max is to the right and
     *   the min is to the left. so, we can keep the elements the same, but reverse the indices (so an index of
     *   i becomes n-1-i). however, since the goal is simply to represent the situation where the max is to the
     *   left, we can also formulate the original expression (that we want to maximize) as ((a[l]-a[r]) - (r-l)),
     *   and this simplifies down to ((a[l]+l)-(a[r]+r)). this can be intuitively found by just noticing that the
     *   maximum element will be located at index l so we can represent it as a[l]. either way, we'll have to do
     *   the order-enforcing trick like before.
     *   - in short, instead of worrying about whether the max is to the left or to the right, we can separate
     *     it into two cases: assume that the max is to the right and impose conditions which force that to be
     *     the case, and assume that it's to the left and impose conditions which force that to be the case
     *
     * generalizable ideas:
     * - if there's a formulation that depends on terms and then other terms that use those terms (like a[l]
     *   depending on l, in the context of the whole expression ((a[r]-a[l])-(r-l)), see if it's possible to
     *   separate out that expression into things that each depend only on one unknown (like l, or r) which
     *   can each be computed independently.
     * - when there are multiple possibilities that could each pop up while trying to optimize some function,
     *   separate out those cases concretely, and for each, impose some constraints if needed to ensure that
     *   that case occurs, then optimize the function.
     *   - in this case, the function to be optimized is ((max-min)-(r-l)) for some segment [l,r], the cases
     *     are whether the max is on the left or right, and the constraints being enforced are forcing the max
     *     to either be the left or the right through the way that the segment tree's segments are combined
     * - if there's one case to consider where something is on the left and something is on the right, if we
     *   then have to consider the other case, try just reversing the list and using the new indices and see
     *   if that works.
     * - sometimes, instead of having multiple segment trees where the information being held for a given segment
     *   is related across the different trees, try seeing if a single segment tree (or at least a fewer number
         of them) can be used by holding multiple pieces of information at each node (i.e., at each segment, since
         each node corresponds to a segment), and then customizing the "combine nodes" functionality that computes
         values for each node based on its children.
         - even more generally than this, if you have multiple instances of a data structure being used in a problem,
           see if it can be simplified (although, in some cases, this might end up making it more complex) to a situation
           where just one instance is used and the internal operations that occur on the data structure are customized
           to this specific problem in order to make it work.
         - how to know that all of these pieces of information are needed? well, a simple way is trial and error. if
           we were to just assume that the two child nodes had the answer for their segments, there would be no direct
           way to compute the answer for the parent node's segment, so we need the argmin(a[i]-i) and argmax(a[i]-i)
           (in other words, the locations of the elements that create that min and that max). now, if we only had those,
           then actually it wouldn't be enough, since the answer might come from entirely the right-side node or the
           left-side node. as a result, we need all 3 pieces of information.
       - a very cool way to imposed ordered information on a segment tree (e.g., ensure that some thing comes to the
         left of some other thing before some value is computed for the segment corresponding to a node) is to treat
         the left and right children nodes differently, and since the base case is that the segment is of length 1,
         the order can be intuitively imposed to any segment of length that's a power of 2 but, since it's a segment
         tree, the order is also retained for segments of any length.
       - keep in mind that although segment trees are easily capable of getting information about the whole array,
         that's just a simple special case of them, because they can actually be used to get information about any
         subarray of the array.
       - if you know that something is going to be at a certain index, then it can be rewriten as an expression of
         that index, such as rewriting max(a[l], a[l+1], ..., a[r-1], a[r]) as a[r] if we know that the max is on
         the right.
         - more generally, if you know that by applying a condition, a term simplifies to an expression of another
           variable, then separate the situation into cases and in the case where the condition applies, rewrite that
           term.
     * - when deciding where in the code to place some implementation of some logic, think about where would be the simplest
     *   place to put it. in this case, the logic for setting each array element's value to a[i]-i is in the main function,
     *   instead of in the segment tree's constructor, because doing it there is probably less prone to bugs.
     *
     * simplified solution using these generalizable ideas (meaning that some of those ideas above are now treated
     * as intuitive knowledge):
     * - we want to find the maximum value of a segment across all segments, both before any queries and after each
     *   query, where the value is defined as the range of values minus the length of the segment
     * - intuitively, by greedily optimizing for the length, the max and min are on opposite sides (or the same element,
     *   if the segment length is 1), so we can separate it into two cases where it goes l-r or r-l; they're analogous,
     *   so for the second case we can take the first case and literally just reverse the array
     * - let's examine the first case. we want to ensure that the min is on the left and the max is on the right,
     *   for any given segment. this means that the expression that we care about is ((a[r]-a[l]) - (r-l)), which
     *   is equivalent to ((a[r]-r) - (a[l]-l)), and so for any segment, we just take the max and min of a[i]-i and
     *   subtract them, while ensuring that the first term corresponds to an index i on the right of the index corresponding
     *   to the second term. this can be easily done with a segment tree.
     * - how do we enforce this ordering (in a segment tree)? assume that it's true for the two child nodes (more rigorously,
     *   assume that the maximum "value" of a segment is drawn from indices that satisfy the max being on the right), which
     *   will be true for the base case of a segment tree where there's only one element in the segment. after making that
     *   assumption, we can make the max value of the current node either be that of the left child, that of the right child,
     *   or the max a[i]-i from the right minus the min a[i]-i from the left. to to this, we'll have to keep track of those
     *   3 pieces of information (max of a[i]-i, min of a[i]-i, max value of range minus length which is the answer for that
     *   segment).
     *
     * couple of ideas for later:
     * - when going through a solution that i don't fully initially understand, break it down, see if the individual
     *   small ideas (that are put together in the main solution) can be stated in very simple generalizable terms,
     *   make those intuitive (which might, by the way, take some time of thinking about it), and then restate the
         solution in terms of those intuitive ideas
       - when i'm trying to make something intuitive for myself, repeatedly ask myself questions about what i don't
         yet understand until i figure out everything that i was previously confused by, then put it all together
     */

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> b = a, c = a;
    reverse(c.begin(), c.end());
    for (int i = 0; i < n; ++i) {
        b[i] -= i;
        c[i] -= i;
    }

    SegmentTree st(b);
    SegmentTree st2(c);
    for (int i = 0; i <= q; ++i) {
        if (i) {
            int p, x;
            cin >> p >> x;
            --p;
            st.update(p, (x-p));
            st2.update(n - 1 - p, x-(n-1-p));
        }
        cout << max(st.query(0, n - 1), st2.query(0, n - 1)) << endl;
    }
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
