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
    /*
    observations:
    - suppose we didn't have to worry about adjacent elements merging together at all.
    how many operations would it take to create an element that's given in that input
    array? well, we could directly put it in 1 operations. if it's even, we could also
    put it in 2 operations. in fact, we can break the element down into 2^m * n, where
    m is any integer and n is odd, and then we can create the element in 2^m operations
    of putting the integer n on the same side repeatedly. can we do fewer operations?
    yes, because if we visualize the mergings of the elements as a tree where the root
    node is the final element, then instead of repeatedly adding leaves, we can add
    higher up nodes at any time. for simplicity, we can basically traverse across the
    leaf nodes from left to right (or right to left) to make this image of using higher-up
    nodes more easily understood. now, we know that we can create the element using
    anywhere from 1 to 2^m operations, inclusive.
    - once we've added a good number of elements to the array, the elements in the middle
    cannot be changed at all, unless the elements at the edge coalesce and end up merging
    into something from the middle. in other words, we start at some element, then move
    outwards. this means we basically worry about ONE ELEMENT AT A TIME, because once some
    element is finalized, the ones that are more inward cannot be changed. so, a simplified
    way to build this is to start from one element (since we need to start the array somewhere),
    then move left and right from that point, and building those leftward and rightward
    elements by traversing the individual construction trees (referring to the trees in
    the previous point) for each of those elements in left-to-right or right-to-left order
    - now, suppose we're building a single element from its cut-in-half (recursively) building
    blocks from left to right. it won't be impacted by the element to the right, since once
    we start building the element to the right then the current element would be finished,
    but it might be impacted by the element to the left since that could be one of the building
    blocks of the current element, meaning that while building the current element we could
    inadvertently merge the a number with the element to the left. how can we avoid this (and
    we should avoid it as it would make the final array not be equal to what we want it to be)
    by missing out on the fewest number of operations? for example, if we have a 6 on the left
    side of a 48, then instead of doing 16 inputs of 3 to build the 48, we'd have to do
    1 input of 12 and then 12 inputs of 3. so, on the side of the tree that is adjacent to
    the element that we are trying to avoid merging with, we use the lowest possible node
    that's greater than that adjacent element (which would just be that adjacent one times 2)
    and then we can proceed to use the smallest possible building block (the leaf) for all the
    other operations
    - this gives us a "number of operations available" value both for building to the left
    and building to the right for each element (where the building process is kind of like
    a leftmost/rightmost derivation of a sentence in a grammar). we can also compute the
    total number of unrestricted operations for each element by counting the number of
    leaves in the tree. now, we could simply iterate through all possible starting points,
    and sum up the operations among the left-traversing segment on the left of the starting
    point and the right-traversing segment on the right. those sums can be precomputed with
    prefix sums (or segment trees if too lazy to construct the prefix sum arrays)
    - for each starting point, we have a maximum number of operations. if we need less
    operations, we can remove those from any of the elements in the array. so, for each
    starting point, we only need to check if the number of operations that we have "available"
    is greater than or equal to k

    simple explanation of the algorithm:
    - for each element, compute the number of operations available if building it in the
    left and in the right direction, as well as the total number of operations available
    to build that element with.
    - now, iterate over all the possible starting elements, and find the number of operations
    there would be access to if building that element as slowly as possible, all left-side
    elements from right to left as slowly as possible, and all right-side elements from
    left to right as slowly as possible. now, if, for any of these starting elements, the
    number of operations available is greater than or equal to k, then the answer is YES,
    otherwise it's NO since we won't have enough operations (under any starting element)
    to build the given final array with k total operations.
    - to find the number of operations available for an element when building it in the
    rightward direction (the leftward direction would be symmetric), first find the maximum
    number p such that 2^p is a divisor of that element, and let the number of operations
    be equal to 2^p. now, if the element to the left isn't one of the integers on the path
    of repeatedly dividing the current element by 2 until it's been done p times, then
    nothing needs to be subtracted from the number of operations, otherwise we do need to
    subtract some number of operations, which is described in the following. consider the
    perfect (full and complete) binary tree with each leaf node being equal to the
    current element divided by 2^p and with the root node being the current element, so that
    there are 2^p leaf nodes. now consider a subtree with its root equal to 2 times the
    element to the left. the thing that we are subtracting is the number of leaves in
    this subtree minus 1, because we're effectively replacing that entire subtree with a
    single node through changing the operations that we're applying to the array.

    generalizeable ideas?
    - instead of worrying about all the elements together, find a way to construct the
    array so that we only are concerned with a single element at a time
    - the start of the construction can be at any point in the array, and after putting
    that one in, we move outward left and right from there
    - instead of directly finding the way to make the array with exactly k operations, we
    find the range of numbers of operations that we're able to do (for various start elements),
    then see if k is in that range
    - when we're given the end state and are asked if it's possible to get to that end
    state through some transformations, first try considering the simplest paths from the
    start state to the end state
    */

    int n, k;
    cin >> n >> k;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> all(n), left(n), right(n);
    for (int i = 0; i < n; ++i) {
        vector<int> levels = {a[i]};
        while (levels[levels.size() - 1] % 2 == 0) {
            levels.push_back(levels[levels.size() - 1] / 2);
        }
        all[i] = left[i] = right[i] = (1 << (levels.size() - 1));

        if (i > 0) {
            for (int j = 0; j < levels.size(); ++j) {
                if (levels[j] == a[i-1]) {
                    // it's impossible for j to be 0, since in the input, a[i] != a[i-1]
                    right[i] -= (1 << (levels.size() - 1 - (j - 1))) - 1; // wipes out subtree, replaces with single leaf
                    break;
                }
            }
        }
        if (i < n-1) {
            for (int j = 0; j < levels.size(); ++j) {
                if (levels[j] == a[i+1]) {
                    left[i] -= (1 << (levels.size() - 1 - (j - 1))) - 1;
                    break;
                }
            }
        }
    }
    // print_container(all, "all = ");
    // print_container(left, "left = ");
    // print_container(right, "right = ");

    ll leftpre[n], rightpre[n];
    for (int i = 0; i < n; ++i) {
        // direction of prefix sum doesn't really matter between these arrays, other than
        // simplicity of implementation
        if (i == 0) {
            leftpre[i] = left[i];
            rightpre[i] = right[i];
        } else {
            leftpre[i] = leftpre[i-1] + left[i];
            rightpre[i] = rightpre[i-1] + right[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        ll operations = all[i];
        if (i > 0) operations += leftpre[i-1];
        if (i < n-1) operations += rightpre[n-1] - rightpre[i];

        if (operations >= k) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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
