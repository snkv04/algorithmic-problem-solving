class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        /*
        basically, for each height, we want to store on the stack the leftmost
        non-blocked index with that height or greater, so then the heights on
        the stack will be monotonically increasing (not non-decreasing)

        generalizable ideas:
        - why store the height with its index in a pair on the stack? in the case
        that a height gets "shrunk" due to a bar with less height towards its
        right side, then the index will remain the same but the height will
        become smaller. therefore, for a given index, we want to see what its
        non-blocked height is, which might not be its original height
        - why keep popping elements until we can't anymore, instead of checking if the
        one we're about to pop is the last one we'll need to pop and not popping if
        it's the last one? this is kind of straightforward; if we want to see if the
        top element on the stack is the last one we need to pop, then that requires
        checking to see what the second-to-top element looks like, which isn't
        possible. so, we just remove all elements of the top of the stack while we
        still need to, and then always end up pushing a new element to the top of the
        stack for each iteration, even if the same outcome would have been reached
        by just updating the top element of the stack (possibly to have a new height
        value) and not pushing anything.
        - what's the difference between this and a traditional monotonic stack use
        case? if we have a monotonically increasing stack, then it can be used to
        see, for each index, the index of the next element to the right (or left)
        that is less than or equal to that element. in this problem, we still are
        interested in, for each index i, the next index j to the right such that
        h[j] < h[i] (because as soon as that happens, then we can no longer use index
        i with a height of j since the full height gets "blocked"), but the difference
        is that we are fine with "shrinking" the height at index i (on the stack)
        down to h[j] instead of it being h[i]. as such, we will update the height for
        index i on the stack to h[j] (which, again, is achieved by popping off the
        original element from index i and pushing a new pair at index j, as it's easy
        to implement if we want a new pair to be pushed at every index).
        - how are equal heights dealt with? only the leftmost one matters (as we want
        to maximize the area of the rectangle), so that's why the logic of keeping the
        leftmost index does not change in the case we are dealing with i, j where
        h[i] == h[j]. we also keep the same logic of calculating the area between the
        indices i and j, but in reality, this calculation does not matter, because a
        larger rectangle will be found for a new element with index k (where i < j < k)
        where h[k] < h[i].
        */

        int ans = 0, n = heights.size();
        stack<pair<int, int>> stk;  // (index, height)
        for (int i = 0; i <= n; ++i) {
            int height = i == n ? -1 : heights[i];
            int index = i;
            while (stk.size() && stk.top().second >= height) {
                index = stk.top().first;
                ans = max(ans, stk.top().second * (i - stk.top().first));
                stk.pop();
            }
            stk.push(make_pair(index, height));
        }
        return ans;
    }
};
