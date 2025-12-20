class Solution {
    vector<vector<int>> children;
    vector<vector<vector<int>>> mem;
    vector<vector<vector<bool>>> possible;
    vector<bool> visited;
    int budget;

    void merge_knapsacks(vector<bool> &p1, vector<int> &m1, vector<bool> &p2, vector<int> &m2) {
        vector<bool> p3 = p1;
        vector<int> m3 = m1;
        for (int i = 0; i <= budget; ++i) {
            if (p1[i]) {
                for (int j = 0; i + j <= budget; ++j) {
                    if (p2[j]) {
                        // check if it's the first time setting the max value
                        // of that weight
                        if (p3[i+j]) {
                            m3[i+j] = max(
                                m3[i+j],
                                m1[i] + m2[j]
                            );
                        } else {
                            p3[i+j] = true;
                            m3[i+j] = m1[i] + m2[j];
                        }
                    }
                }
            }
        }
        p1 = p3;
        m1 = m3;
    }

    void dfs(
        int node, const vector<int> &present, const vector<int> &future
    ) {
        visited[node] = true;
        for (int next : children[node]) {
            if (!visited[next]) {
                dfs(next, present, future);
            }
        }

        // looks at if we do/don't have the discount available at the node
        for (int j = 0; j < 2; ++j) {
            int cost = (j == 0) ? present[node] : (present[node] / 2);
            int profit = future[node] - cost;

            // considers the case where we do buy the node
            vector<int> memifbuying = mem[node][j];
            vector<bool> possifbuying = possible[node][j];
            if (cost <= budget) {
                possifbuying[cost] = true;
                memifbuying[cost] = profit;
                for (int next : children[node]) {
                    merge_knapsacks(
                        possifbuying,
                        memifbuying,
                        possible[next][1],
                        mem[next][1]
                    );
                }
            }

            // considers the case where we don't buy the node
            vector<int> memifnotbuying = mem[node][j];
            vector<bool> possifnotbuying = possible[node][j];
            possifnotbuying[0] = true;
            memifnotbuying[0] = 0;
            for (int next : children[node]) {
                merge_knapsacks(
                    possifnotbuying,
                    memifnotbuying,
                    possible[next][0],
                    mem[next][0]
                );
            }

            // merges the two cases together
            for (int currcost = 0; currcost <= budget; ++currcost) {
                possible[node][j][currcost] = possible[node][j][currcost] ||
                                              possifbuying[currcost] ||
                                              possifnotbuying[currcost];
                mem[node][j][currcost] = max({
                    mem[node][j][currcost],
                    memifbuying[currcost],
                    memifnotbuying[currcost]
                });
            }
        }
    }

public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        /*
        - for a given node, the original cost ("present" value) might
        exceed the budget, while the half-cost doesn't exceed the budget.
        this could, in theory, be fixed by increasing a pseudo-budget to
        account for all costs (where if a cost exceeds approximately double
        the budget, then half of its cost will exceed the budget, so we don't
        have to consider it, but in other cases, both the cost and half-cost
        will definitely be accounted for). however, that can TLE. instead,
        we can change the DP state; instead of looking at each (node, did
        or didn't buy, total cost accrued) state, we can look at a (node,
        has or doesn't have discount, total cost accrued) state.
            - more generally, in the previous solution, we are splitting DP 
            states based on which action we take at a node, while in this 
            solution, we are splitting DP states based on what conditions are 
            met at a node. it is true that for a single DP state, we look at 
            multiple possible actions to take anyway, so the second solution 
            might always seem to be better, but it's pretty problem-dependent.
            the second one is just better in this problem because the 
            calculating the result of the subproblem where we halve the cost 
            is dependent upon the result of the subproblem where we don't 
            halve the cost, and so to make sure that the situation where we 
            don't halve the cost is ALWAYS computed, we have to increase the 
            budget, which causes TLE. in the current solution, these states do 
            not depend on each other; in other words, when we compute the 
            result of one situation, it doesn't use the result of the other 
            situation. specifically, the max profit for a given node when
            we have a discount at that node doesn't depend on the max profit 
            for that node when we don't have a discount.

        generalizable ideas for the future:
        - if we are making some assumptions about the DP state, then MAKE SURE 
        that those assumptions are encoded into the math properly. for 
        example, if we are assuming that we ARE definitively buying something 
        (at some nonzero cost), then the "possible" value for the state 
        corresponding to cost=0 shouldn't be set to true by default. as always,
        be careful about all the base cases.
            - sure, it's possible that the information from the case where we 
            do buy ends up getting merged with the information from the case 
            where we don't buy. however, the results from when we definitely 
            DO buy should reflect the fact that we are buying, and to make 
            sure that that is accurate, we shouldn't allow the cost=0
            state to have possible=true (except if the cost of what we're 
            buying is 0) when we specifically make the assumption that we ARE 
            buying.
        - when doing knapsack DP, it is common that we want to update several
        things at once, so to make sure that none of those updates impact the
        other ones, the default solution is to make a new table (or row of a
        table) so that the results we are drawing from to get our new results
        are not also the ones being updated. to save space, we can use the same
        table, as long as we iterate over the updates in a way that does not
        use a new value from a subproblem that we want the old value from to
        compute the value for an update. KEEP THAT IN MIND. the reason why we
        want j to be increasing in the merge_knapsacks() method is specifically
        because if j is decreasing, then the VERY LAST subproblem that we USE
        to update m1[i] for some value of i is (m1[i-j]+m2[j])=(m1[i]+m2[0]),
        which is a problem because we've been updating m1[i] the entire time.
        keep in mind that if we want to use old values to update new values,
        then we simply want to make sure that we aren't accidentally
        overwriting the old values with new values (at least not until we no
        longer need those old values). in general, this concept of keeping
        old and new values separate is pretty important in programming, for
        the consistency of data.
        - in knapsack DP, if the value of an object being put into the knapsack
        can be negative, then it is the case that the default max value for a
        given weight can be better than the max value for a given weight after
        trying to update it, so it doesn't update. (for example, we set the max
        value for weight 5 as 0 when we haven't actually achieved a case where
        the weight is 5, then when we put in an object of weight 5 and value -7,
        we keep the max value for weight 5 as 0, even though there hasn't yet
        existed a case with weight 5 and value 0. the max value for weight 5
        should be -7.) for this reason, and i'm pretty sure i've already said
        this before, it is very important to make sure that if you are trying
        to optimize something, then the default value of that something should
        be leq (or geq) the first value that it's possible to set it to. that's
        why setting the max value to -inf is better than 0.
            - however, setting the initial max value to 0 works, if we have
            the `possible` table keeping track of if a weight has been achieved.
            then, we just have to separately treat the cases where a weight is
            having its value updated for the first time and updated for the second
            or later time; in the former case, we simply overwrite the default
            value, while in the latter case, we can take the max of the existing
            value and the new value.
            - by the way, it might be tempting to think that since we initially
            set `memifbuying[cost] = profit;` instead of
            `memifbuying[cost] = max(memifbuying[cost], profit);`, we cover all
            cases where the value could be negative at the given node, and then
            we don't have to worry about the default value ever being better than
            the first value we find for some given weight. however, there are cases
            this misses: getting a negative value for some weight from a child node.
            remember, even if a condition (desirable or undesirable) isn't met in
            the initial state, it could be met after later updates. consider all
            cases (though easier said than done).
        */

        // - mem[i][j][k] = maximum profit from the subtree rooted at node i
        // where we spent exactly k, where the discount is not available if
        // j == 0 and is available if j == 1
        // - possible[i][j][k] = whether or not it is possible to have spent 
        // exactly k in the subtree rooted at node i, when the discount isn't 
        // available if j == 0 and is available if j == 1
        this->budget = budget;
        children.clear();
        children.resize(n);
        for (auto edge : hierarchy) {
            children[edge[0] - 1].push_back(edge[1] - 1);
        }
        mem = vector<vector<vector<int>>>(
            n,
            vector<vector<int>>(
                2,
                vector<int>(
                    budget + 1,
                    0
                    // -1e9
                )
            )
        );
        possible = vector<vector<vector<bool>>>(
            n,
            vector<vector<bool>>(
                2,
                vector<bool>(
                    budget + 1,
                    false
                )
            )
        );

        // solve
        int root = -1;
        visited = vector<bool>(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, present, future);
                root = i;
            }
        }

        int ans = 0;
        for (int i = 0; i <= budget; ++i) {
            ans = max(ans, mem[root][0][i]);
        }
        return ans;
    }
};
