import java.util.*;
import java.io.*;

public class SleepyCowHerding {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("herding.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("herding.out")));

        int n = Integer.parseInt(br.readLine());
        TreeMap<Integer, Integer> positions = new TreeMap();
        for (int i = 0; i <= n-1; i++) {
            positions.put(Integer.parseInt(br.readLine()), -1);
        }
        int i = 0;
        for (Integer pos : positions.keySet()) {
            positions.put(pos, i);
            i++;
        }
        // pw.println(positions);

        int penultimateCow = positions.lowerKey(positions.lastKey());
        int secondCow = positions.higherKey(positions.firstKey());
        if ((penultimateCow - positions.firstKey() == n-2 // first n-1 cows consecutive
            && positions.lastKey() - positions.lowerKey(positions.lastKey()) >= 3) // last 2 cows have gap >= 2
            || (positions.lastKey() - positions.higherKey(positions.firstKey()) == n-2 // last n-1 cows consecutive
                && positions.higherKey(positions.firstKey()) - positions.firstKey() >= 3)) { // gap first 2 cows is >= 2
            pw.println(2);
        } else {
            int maxCows = 0;
            for (int pos : positions.keySet()) {
                // the value of each entry is the number of cows before that cow
                int lastInWindow = positions.floorKey(pos+n-1);
                int cows = positions.get(lastInWindow) - positions.get(pos) + 1;
                if (cows > maxCows) {
                    maxCows = cows;
                }
            }
            pw.println(n-maxCows);
        }

        int prefixGaps = penultimateCow - positions.firstKey() + 1 - n + 1;
        int suffixGaps = positions.lastKey() - secondCow + 2 - n;
        pw.println(Math.max(prefixGaps, suffixGaps));

        br.close(); pw.close();

        // one of the first observations i had, which is pretty obvious, is that if
        // there is an interval filled cows but there's one gap, then all it
        // takes for them to be consecutive is for one cow to move and fill that gap.
        // similarly, if there are three cows and two of them have a one cow cap, then
        // the third needs to be placed in that spot and the answer is just one move.
        // if there are three cows and all of them are far away (i.e. the gaps between
        // them are all >= 2 cows), then one of them simply needs to be moved to exactly
        // two spots away from another cow (without breaking the endpoint rule) and the
        // last one needs to be placed into the gap formed, meaning the answer for 3
        // cows is always 1 or 2. so the number and size of gaps between the n cows
        // is evidently very important.
        // basically, we want to take all of the n cows and fit them into a length n
        // interval using the least number of operations, where an operation is defined
        // as in the problem. intuitively, we would want to find the length n window
        // that already holds the most cows in it, so that we can then move the other
        // cows into the window while making sure to account for any edge cases with
        // respect to the definition of an "operation".
        // we wouldn't want the n-sized window to start at an empty point on the number
        // line, as that would just automatically decrease the potential cows in the
        // window, so we just check all the n-sized windows starting at each cow and
        // count the number of cows in the window. if the cows are spread out a lot, then
        // this works perfectly, because then we can just move all the cows outside
        // the window into it, even if the window ends on an empty space, since n >= 3.
        // now, if the window ends on an empty space and there are 2 or more cows
        // outside of it, then we can move those 2 (or more) in, guaranteed, by using
        // the first observation above. however, if the window ends on an empty space
        // and there is only one cow outside the space, then we need more consideration.,
        // first off, that means that the first n-1 cows are all consecutive except for
        // the last one. if the space is only size 1 (like 11111101, where 1 is a cow
        // on the number line and 0 is an empty spot), then we can move the first cow
        // into the gap and the algorithm from before still works (where the window
        // being chosen starts on the second cow and ends on the last, but the algorithm
        // doesn't need to distinguish between this and the last cow illegally moving
        // into the empty space). however, if the space is size 2 or more (1111110001),
        // then that lone cow cannot move on its own due to the endpoint rule, and a
        // cow from the beginning needs to move (0111110101) to make space for the
        // lone cow to move in (011111110). this is guaranteed to require 2 moves,
        // and the size of the space doesn't matter as long as all the first n-1
        // cows are consecutive and the space is >= 2. the reverse can be applied if
        // the last n-1 cows are consecutive and the first cow is alone.
        // something to learn from this is to identify what the end goal is and figure
        // out how the start and end situations relate. in this case, we know the end
        // will be guaranteed to be n consecutive cows, so that can help in using
        // intuition to figure out the optimal way to get from the start to the end.
    }
}
