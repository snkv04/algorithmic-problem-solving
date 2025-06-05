import java.util.*;
import java.io.*;

public class Alchemy2 {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static ArrayList<Integer> diffs;
    static int half, n;
    static int[][] memo;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        // this loops from the middle of the string (including the middle character if
        // n=|s| is odd and the right side middle character if n is even) to the end, and
        // for each of those, diffs[i] is 1 if the corresponding character in the string
        // from the opposite end isn't the same and is 0 if the corresponding character
        // is the same for the palindrome
        char[] s = br.readLine().toCharArray();
        n = s.length;
        diffs = new ArrayList<>();
        for (int i = n/2; i <= n-1; i++) {
            diffs.add(s[i]!=s[n-1-i]?1:0);
        }
        // pw.println(diffs);

        // solves the problem
        half = diffs.size();
        if (half == 1) {
            // if diffs[0]=0 and half=1, then either there is only 1 character (where there
            // can't be a mismatch) or there are 2 characters that are matching
            // however, if diffs[0]=1 and half=1, then there are 2 characters that are mismatched,
            // which can easily be fixed with one operation
            pw.println(diffs.get(0)==0?0:1);
        } else {
            // uses dp with memoization, passing the last index of the "diffs" ArrayList along
            // with the 2 diffs at the end and right before the end
            memo = new int[half][4];
            for (int i = 0; i < half; i++) Arrays.fill(memo[i], -1);
            pw.println(solve2(half-1, diffs.get(half-1), diffs.get(half-2)));
        }
    }

    // index = index (0-indexed) that is currently being considered, such
    //     that the diffs up to and including index-2 are all 0, and the diffs
    //     at index and index-1 can be anything (which are also the indices on
    //     which any operations at the current index are performed)
    // last = value of diffs at index
    // secondLast = value of diffs at index-1
    static int solve2(int index, int last, int secondLast) {
        if (index == 1) {
            // self-explanatorily splitting into cases when considering the last 2 digits,
            // just like the base cases of a recurrence relation
            if (last == 0 && secondLast == 0) return 0;
            else if (last == 0 && secondLast == 1) return 1;
            else if (last == 1 && secondLast == 0) return n%2==0 ? 2 : 1;
            else return 1;
        }
        if (memo[index][last+2*secondLast] != -1) {
            // if the value is memoized, then return it
            // the formula is used because there are 4 different combinations of
            // last and secondLast, which both are in {0, 1}, so they are mapped as such:
            // (last = 0, secondLast = 0) -> 0
            // (last = 1, secondLast = 0) -> 1
            // (last = 0, secondLast = 1) -> 2
            // (last = 1, secondLast = 1) -> 3
            return memo[index][last+2*secondLast];
        }

        int ans = -1;
        if (last == 0) {
            // since there is no reason to operate on the current index, we just take
            // the result of one index prior
            ans = solve2(index-1, secondLast, diffs.get(index-2));
        } else if (last == 1 && secondLast == 0) {
            // we operate on the current index, changing the values at index and index-1
            // we don't move left to take results of previous indices, though.
            // we take the better choice of keeping the 1 as a 1 or changing it to a 0,
            // while the 0 must be made into a 1 since if it was already matching then
            // now it can't be
            ans = 1 + Math.min(
                solve2(index, 1, 1),
                solve2(index, 0, 1)
            );
        } else {
            // last = 1 and secondLast = 1

            // both letters are different from their corresponding letters, so we
            // can either keep the one at index-1 different by changing it to a different
            // non-matching letter or make it matching; however, the letter at index
            // (represented by last) should be made to match, in order to move left faster.
            // this is effectively the same as moving left after adding the 1, since we
            // know "last" will become 0 so it ends up as one of the other cases after
            // moving left; this is why either of the two following code snippets will work

            /*
            ans = 1 + Math.min(
                solve2(index, 0, 1),
                solve2(index, 0, 0)
            );
            */
            ans = 1 + Math.min(
                solve2(index-1, 1, diffs.get(index-2)),
                solve2(index-1, 0, diffs.get(index-2))
            );
        }
        memo[index][last + 2*secondLast] = ans;
        return ans;
    }
}