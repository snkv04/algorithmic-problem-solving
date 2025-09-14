/*
if we have n floors and k eggs, then the floor we're looking for could be
anywhere. it does not matter where the floor is, since we know that we just
want to know where the floor is WITH CERTAINTY (as mentioned in the problem
statement). so, if we have 1 egg, then we have to check all floors. if we have
no floors, it takes no drops to find out that f = 0, since that means that
floors 1...inf will break the egg, but no such floors exist so this is vacuously
true.
if we have n floors and k eggs, then we want to see, across all possible
operations we could make (floors we could drop an egg from), what is the
lowest number of operations we need to find out the floor f with certainty?
so, we just iterate over all possible operations. for each operation, the
egg can either break or not break, but we don't know which will happen so we
must consider both options (i.e., take the worst case of the two). that's the
brute-force solution.
now, how can we optimize the brute-force solution? well, for each state (n, k),
we are searching over all places in the interval [1, n] to drop the egg in
order to take whichever of those states has the best possible worst-case (i.e.,
the minimum number of drops needed). we are trying to optimize the number of
operations across a bunch of other states. well, could we do this faster? note
that the "broke" option for each floor "i" that we're checking (looking at the
state (i-1, eggs-1)) will increase in its number of operations as i increases,
while the "didn't break" option for each floor (the state (n-i, eggs)) will
decrease in its number of operations as i increases. if we are trying find some
value "i", the floor to check, that minimizes the maximum of these two states,
then this is a unimodal function. that means we can perform binary/ternary
search on this floor, finding the best floor based on its worst-case value
for the number of operations required. keep in mind that the thing we are
performing binary search on (which floor to choose to minimize the operation
count) is wholly separate from checking right/left for a fixed floor (check if
egg breaks vs. egg doesn't break).
for the binary search condition itself, we're basically finding an inflection
point, right? so the best floor is either the last one at which the "didn't
break" side is >= the "broke" side, or the next floor (which is the first floor
at which the "didn't break" side is < the "broke" side).
*/

class Solution {
private:
    vector<vector<int>> dp;

    int recurse(int floors, int eggs) {
        if (floors <= 0) return 0;
        if (eggs == 1) return floors;
        if (dp[floors][eggs] != 1e9) return dp[floors][eggs];
        
        // binary search across floors (could also use ternary search)
        int left_floor = 1, right_floor = floors;
        int best_floor = -1, best_ops = 1e9;
        while (left_floor <= right_floor) {
            int mid_floor = left_floor + (right_floor - left_floor) / 2;
            int if_broke = recurse(mid_floor - 1, eggs - 1);
            int if_no_break = recurse(floors - mid_floor, eggs);

            if (if_no_break >= if_broke) {
                best_floor = mid_floor;
                best_ops = 1 + if_no_break;
                left_floor = mid_floor + 1;
            } else {
                right_floor = mid_floor - 1;
            }
        }

        int best_ops_count = min(
            1 + max( // checking best_floor
                recurse(best_floor - 1, eggs - 1),
                recurse(floors - best_floor, eggs)
            ),
            (best_floor == floors) // checking next floor
                ? static_cast<int>(1e9)
                : (1 + max(
                    recurse(best_floor, eggs - 1),
                    recurse(floors - best_floor - 1, eggs)
                )
            )
        );
        dp[floors][eggs] = best_ops_count;
        return dp[floors][eggs];
    }

public:
    int superEggDrop(int k, int n) {
        dp = vector<vector<int>>(n+1, vector<int>(k+1, 1e9));
        return recurse(n, k);
    }
};
