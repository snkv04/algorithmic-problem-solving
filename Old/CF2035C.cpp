#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /*
    observations:
    if n = 2^k, then n is even, so the last element is or'd. however,
        there is only one element that has the kth bit.
    if n is odd, then there are always at least two numbers with the
        most significant bit, even if n = 2^k + 1. that's enough to
        propagate it through the last elements.
    if two elements are adjacent, the first is even-indexed and the
        second is odd-indexed, and one of them only has a subset of
        the other's bits turned on, then the order in which they appear
        doesn't matter
    in general, the earlier elements matter less than the later ones.
        also, in general, the higher-order bits matter more than the
        lower-order bits.

    explanation:
    basically, the way it works is that we want to save as many bits as possible. note that
    we can never have the final value of k be equal to any number that has a bit higher than
    the highest bit of n. we can break this into two cases: when n is odd (the lowest bit is
    at 0-index 0 from the right) or when n is even (the lowest bit is at 0-index 1 from the
    right).
    for the odd case, it's clear that the last element will be causing a bitwise AND. this
    means that whatever k accumulates to after the first n-1 elements will be restricted by
    the bits of the last element, and vice versa (bits of last element are restricted by k
    from previous elements). if we suppose n is the last element, then the final value of
    k cannot be greater than n, because the bits of k before that element would be intersected
    with the bits of n, which means the result must be less than or equal to n. in fact, this
    lets us see that the result of the AND between two nonnegative integers A and B must be
    less than or equal to min(A, B), and in a similar manner, the result of the OR between
    any two nonnegative integers A and B must be greater than or equal to max(A, B). also,
    if n is not the last element then some value <= n would be, and so the final value must
    be <= n. so, the maximum value of k in this instance is n, so we can optimistically
    attempt to make it n. let the last value be n. then, the accumulated value of k before
    the last value must ensure that all of the bits of n are activated. OR operations
    activate new bits and maintain existing bits, while AND operations maintain intersections
    and deactivate all other bits. one way to activate all the bits of n is to OR 1, AND 3
    (so then the rightmost bit remains from being activated by 1), OR n-1 (so all of the
    bits of n other than the rightmost bit become activated), AND n (so all the bits of n
    that are already activated are maintained). this shows that the final value of k is
    no more than n, since it would be restricted by the last value, but also no less than
    n, since it made sure that all bits of n were activated then maintained.
    for the even case, either we only have a single bit active (meaning that n is a power
    of 2) or at least 2 bits active, though the rightmost bit would never be active in
    either case. let's deal with them separately:
    if we only have a single bit active, then assuming n=2^p, n-1 will have all bits up
    to bit p-1 active. the best possible case would be to have all bits up to p be active
    in the final k, so we can try to make that the case. since the last element is at an
    even index, we can't just use n-1 to directly activate all the other bits right before
    it since we need to maintain all those bits with another element. remember that the
    operations follow an activate/maintain cycle (or, from another perspective, a
    maintain/activate cycle). so, we can do OR 1 (to activate the rightmost bit), AND 3
    (to maintain the rightmost bit), OR n-2 (to activate all bits up to bit p-1 except
    the rightmost bit, where the rightmost bit is already there), AND n-1 (to maintain
    all bits up to bit p-1), OR n (to activate the leftmost bit).
    if we have more bits active but we're still dealing with an even n, then if we let
    p = floor(log2(n)), then for the last 3 bits, we can do OR n-1 (to activate bit p,
    not caring about the other bits), AND n (to maintain bit p, not caring about the
    other bits), OR 2^p (to activate all the other bits to the right of bit p).

    how to know that we should break it into the cases of n is even and n is odd?
    one way is to recognize that we are looking for the cumulative value after many alternating
    operations, and so we can break down the cases into the two possible operations that occur
    last. we can also try looking at the test cases and notice that for odd cases, k=n, and for
    even cases, k = 2^(floor(log(n))+1)-1, but this is a little bit less obvious. the general
    idea, of course, is to just try a variety of different ideas. when would it really be wrong
    to break it into these specific cases? if the most efficient option was to split the inputs
    into cases across some other criterion, then those could still apply into both categories
    created after splitting between odd/even. this means that it is, regardless, worth at least
    attempting to split based on the criterion of parity, and then this step can be dropped later
    if needed. how to come to the idea of splitting the even case into the cases of either
    being a power of 2 or not? once realizing that we are dealing with an "activate bits / maintain
    bits" cycle which kind of involves building up to having all the necessary bits activated,
    then it can become clearer that the number of bits available in n changes how we approach
    the sequence of the final elements in the list that is outputted.

    how to know the number of elements that we'll need, beyond which all of the other elements
    don't matter? how to know that it's not too high or too low?
    sometimes all the elements are needed, sometimes it's only 2 or 3, and in this case it was
    3, 4, or 5 depending on the case. it's definitely unsettling when not knowing this, because
    then it feels like i'm on the wrong track if using too many or too few elements for the
    algorithm. the obvious answer is just to use as many elements as needed, and to drop the
    uncertainty, just be fully mentally willing to try various different things until i'm out
    of ideas. another clue is that n is always >= 5, so maybe it might be necessary to use
    5 elements in order to consider every single case, but that sometimes might also not be
    true, since some threshold number of elements may be needed to cover the general case
    when the input is sufficiently large but below that are all special cases.

    how do we know the upper bounds of the final k value?
    some of it is making an optimistic guess and then fitting a solution to meet that guess.
    some of it is derived from looking at the test cases and formulating a hypothesis.
    the reasoning using the idea of bitwise ANDing placing restrictions on the bits also
    plays a part.

    how do we know the other elements don't matter?
    this is relatively simple: since k is the accumulated value after all the elements, then
    only the value at the end matters. so, if we can just use a handful of elements to obtain
    the end result, then the others won't matter. of course, this is just a guess based on
    similar patterns in past problems, and if it didn't work then we would need to look into
    methods to solve it using all of the elements.

    how to come up with these orders of elements?
    we know we're dealing with an activate/maintain cycle regarding the operations that
    each consecutive element applies. with the even but not power of 2 case, for example,
    we know that there are multiple elements with bit p available but only 1 element with
    all the bits to the right of bit b available, so we activate-maintain the leftmost bit
    and then simply activate the remaining bits, which works since the last element is OR'd.
    with the even and power of 2 case, there's only 1 element with the leftmost bit (bit p)
    active, so it should be activated on the last element; so, the rationale is to first 
    activate-maintain the rightmost bit, activate the remaining bits up to p-1, maintain
    all bits up to p-1 including the rightmost bit (maintaining everything that has been
    activated so far cumulatively), then activate bit p. for the odd case, there will
    definitively be at least 2 elements with bit p active (supposing p = floor(log2(n))),
    so we can activate-maintain the rightmost bit, activate all other bits of n, and then
    maintain all bits of n using n.

    what patterns can be applied to other problems?
    it is true that the pattern of alternating between activating bits through the OR
    operation and maintaining them with the AND operation is quite specific to this problem,
    but there are some things that are generalizable. first, the properties of the outputs
    of these operations could be important to keep in mind, namely that the AND is leq the
    minimum of the two inputs and the OR is geq the max of the two inputs. also, when trying
    out ideas, it can be worth it to split the possibilities into the most intuitive cases,
    since backtracking to another idea later is always possible (though, obviously, i should
    be trying to make this whole process quick so as to not waste too much time in contests
    trying out incorrect ideas). additionally, in this problem, up to 5 elements are needed
    to form the part of the sequence that matters in the output depending on the case, and
    that is more than some other problems needed; however, there could also be other problems
    for which more of the input matters. it's a clue that n is geq 5, so then at most 5 elements
    would be needed to fit in with the pattern in all cases, but there are also problems that
    have a similar pattern but the input can be arbitrarily small, so then the small inputs
    are simply special cases. for example, in this problem, if n=5, then it wouldn't even fall
    into a case where 5 elements are necessary, but if n was lower at 4, then it would need 5
    elements to fit into the pattern, and so if the problem stated n>=4, then that wouldn't
    mean that the pattern was wrong as it simply wouldn't solve the small cases but would still
    be able to generalize to all inputs within that case (i.e., where n is a power of 2) outside
    of the special cases. basically, don't be too wary about using too many or too few parts of
    the input when saying that the rest of the input doesn't matter, because i can backtrack
    to other ideas after trying it out. also, as that example shows, don't instantly discount
    the value of a pattern i find just because there is a single or select few counterexamples,
    because those could just be special cases (or form an entirely separate case on their own)
    that don't disqualify that pattern from properly dealing with a large class of inputs.
    */

    int n;
    cin >> n;
    unordered_set<int> remaining;
    for (int i = 1; i <= n; ++i) remaining.insert(i);
    
    if (n % 2) {
        cout << n << "\n";
        for (int num : vector<int>({1, 3, n-1, n})) {
            remaining.erase(num);
        }
        for (int num : remaining) cout << num << " ";
        cout << "1 3 " << n-1 << " " << n << "\n";
    } else {
        int pow = 0, copy = n;
        while (copy > 1) {
            ++pow;
            copy /= 2;
        }

        cout << (1 << (pow+1))-1 << '\n';
        if (n == (1 << pow)) {
            for (int num : vector<int>({1, 3, n-2, n-1, n})) {
                remaining.erase(num);
            }
            for (int num : remaining) {
                cout << num << " ";
            }
            cout << "1 3 " << n-2 << " " << n-1 << " " << n << "\n";
        } else {
            for (int num : vector<int>({n-1, n, (1<<pow)-1})) {
                remaining.erase(num);
            }
            for (int num : remaining) {
                cout << num << " ";
            }
            cout << n-1 << " " << n << " " << (1<<pow)-1 << "\n";
        }
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
