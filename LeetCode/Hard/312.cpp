class Solution {
    vector<vector<int>> mem;

private:
    int dfs(int i, int j, vector<int> &nums) {
        if (mem[i][j] != -1) return mem[i][j];

        int result = 0;
        int last = i == 0 ? 1 : nums[i-1];
        int next = j == nums.size() - 1 ? 1 : nums[j+1];
        for (int k = i; k <= j; ++k) {
            int k_result = nums[k] * last * next;
            if (k != i) k_result += dfs(i, k-1, nums);
            if (k != j) k_result += dfs(k+1, j, nums);
            result = max(result, k_result);
        }
        mem[i][j] = result;
        return result;
    }

public:
    int maxCoins(vector<int>& nums) {
        /*
        generalizable ideas for the future:
        - if we set mem[i][j] to be equal to the maximum value we can get
        from the interval [i, j], then we need to figure out how to compute
        it. we can't compute it (easily, or quickly) by iterating over the
        first balloon that we pop in the interval, and this is because then
        the left and right interval will depend on each other, and we don't
        know which is the leftmost balloon in the right interval at the time
        that the rightmost balloon in the left interval is popped (and vice
        versa). to keep track of that, we might as well just do a brute-force
        solution with recursion. the way to compute it easily here is to instead
        iterate over the LAST balloon that we pop in the interval. by doing
        this, we implicitly make the assumption that all other balloons were
        popped while the current balloon is still present, so then the right
        interval and left interval are completely independent subproblems
        because they don't touch each other.
            - it is of note that this only works because each balloon only
            considers the direct left and direct right balloon. if our coins
            are dependent on nums[i-2] or nums[i+2] for popping balloon i, then
            we would run into the same problem where iterating over a single
            balloon that stays alive while the left and right problems have
            all their balloons popped would not be sufficient to separate the
            left and right subproblems. however, if in that hypothetical
            problem, we could only pop 2 adjacent balloons at once, then that
            would be enough to separate the left and right subproblems into
            being independent, because: the width of the thing we are iterating
            over (the separator) is equal to the width of the operation that
            could possibly connect the left to the right, so they don't touch.
            - we are also making the assumption the balloons outside of the
            interval [i, j] have not been popped. why? first off, for the final
            problem, it is valid; the sentinel balloons with value 1 are never
            popped themselves. also, we make that assumption because when we
            iterate over the "separator" balloon, the left and right subproblems
            both depend on that separator being there (since it is the last one
            to be popped in the whole interval [i, j]). in simple terms, if we
            are to ever "use" a subproblem to calculate the answer to a problem,
            then the conditions in which we invoke that subproblem ensure that
            the balloons to the left and right of it are intact. one way to think
            about it is this: given an interval [i, j], instead of picking a
            balloon to use and assuming that all balloons outside of that interval
            are also used, then needing to use the remaining balloons in the
            interval, we pick a balloon to use, assuming that all balloons outside
            of that interval are intact and all other balloons in that interval
            have already been exploded (while that picked balloon remained intact).
        */

        int n = nums.size();
        mem = vector<vector<int>>(n, vector<int>(n, -1));
        return dfs(0, n-1, nums);
    }
};
