import java.util.*;
import java.io.*;

public class LeftOut {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("leftout.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("leftout.out")));

        int n = Integer.parseInt(br.readLine());
        char[][] grid = new char[n][n];
        for (int i = 0; i <= n-1; i++) {
            char[] line = br.readLine().toCharArray();
            for (int j = 0; j <= n-1; j++) {
                grid[i][j] = line[j];
            }
        }

        for (int i = 0; i <= n-1; i++) {
            if (grid[i][0] != 'L') {
                for (int j = 0; j <= n-1; j++) {
                    grid[i][j] = swap(grid[i][j]);
                }
            }
        }
        for (int j = 1; j <= n-1; j++) {
            if (grid[0][j] != 'L') {
                for (int i = 0; i <= n-1; i++) { grid[i][j] = swap(grid[i][j]); }
            }
        }

        // for (int i = 0; i <= n-1; i++) {
        //     pw.println(grid[i]);
        // }

        int totalCount = 0;
        int[] rowCount = new int[n]; // 0 index won't be used
        int[] colCount = new int[n];
        for (int i = 1; i <= n-1; i++) {
            for (int j=1; j<=n-1; j++) {
                if (grid[i][j] == 'R') {
                    totalCount++;
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }

        if (totalCount == 0) {
            pw.println(-1);
        } else if (totalCount == 1) {
            int ansRow = -1;
            for (int i = 1; i <= n-1; i++) {
                if (rowCount[i] == 1) {
                    ansRow = i;
                    break;
                }
            }
            int ansCol = -1;
            for (int i = 1; i <= n-1; i++) {
                if (colCount[i] == 1) {
                    ansCol = i;
                    break;
                }
            }
            pw.println((ansRow+1) + " " + (ansCol+1));
        } else if (totalCount == n-1) {
            // if none of the rows or columns have n-1 Rs, then these n-1 Rs are
            // spread out across the grid, meaning it's not possible
            boolean done = false;
            for (int i = 1; i <= n-1 && !done; i++) {
                if (rowCount[i] > 1 && rowCount[i] < n-1) {
                    pw.println(-1);
                    done = true;
                    break;
                } else if (rowCount[i] == n-1) {
                    pw.println((i+1) + " 1");
                    done = true;
                    break;
                }
            }
            // now checking columns
            for (int j = 1; j <= n-1; j++) {
                if (colCount[j] > 1 && colCount[j] < n-1) {
                    pw.println(-1);
                    done = true;
                    break;
                } else if (colCount[j] == n-1) {
                    pw.println("1 " + (j+1));
                    done = true;
                    break;
                }
            }
            if (!done) pw.println(-1);
        } else if (totalCount == (n-1)*(n-1)) {
            pw.println("1 1");
        } else {
            pw.println(-1);
        }

        br.close(); pw.close();

        // first, assume that there is no problematic cow. then, since this means that purely by
        // row-flipping and column-flipping operations we can arrive at a strictly homogeneous grid,
        // this means that all of the rows are either equal to each other or mirrors of each other.
        // we could flip the ones that are opposite so that all the rows are equal, and then all
        // of the columns are either all Ls or all Rs. we can just flip all the R columns into
        // L columns, and then the grid is all Ls. now, at the end there, if any of the cows are Rs,
        // then that is the problematic cow which is the answer and we can't get a homogeneous grid.
        // we want to get to this case to determine where the cow is, so if we first flip every row
        // to make the first element an L and then flip every column to make the first element an L,
        // then assuming there is no problematic cow, this should get us to reach the homogeneous
        // grid.
        // if the problem cow is not in the top row or left column, then we can find its indices.
        // if it is, then recall that we made all the rows and columns flip to get the top and left
        // to Ls, meaning that this is the same case as if every cow in that row except for the
        // one on the left is a problem cow (an R), so to get the one with the earliest column
        // index, just pick the first one. use the same logic but graphically transposed for
        // columns filled with Rs except the first element. now, if there are no R cows, then
        // none of the cows can be flipped to make a perfect picture (although I don't think
        // this can happen in this problem). if all of the cows other than the top and left are Rs,
        // then rows and columns can be flipped to make the very very top left cow the R, making
        // that the answer. these all fall under cases where there is 1 total R, N-1 total Rs (for
        // either a full row or full column minus the first element), 0 total Rs, and (N-1)^2 Rs.
        // if there are any other values of total cows, then there are multiple problem cows that
        // cannot be gotten rid of just by flipping rows and columns. for example, 3 Rs scattered
        // around in different rows/columns cannot all be fixed in one go. even if they're all in
        // 1 row, if there aren't N-1 (excluding the left cow), then there are multiple cows
        // that can't be fixed by flips of rows or columns. notice that the case of (RRRRLRR) or
        // something like that can't happen, because the left would be made an L earlier, meaning
        // that this is equivalent to the case of just one R (LLLLRLL) in the middle of the grid
        // where everything else is homogeneous.
        // to understand the method of flipping everything at the start so all the top row and
        // left column are Ls, notice that the actual values of the cows (L or R) don't matter,
        // as only their values relative to everything else do. so to get that homogeneous grid,
        // first assume that everything will work (end up homogeneous) and see that if a row
        // doesn't begin with the same letter as the one above it, then to get it to be the same
        // row as the one above it, we have to flip it. this is assuming that the row is either
        // equal to or opposite to the one above, and if it isn't we'll find it after the next
        // step. now, all the columns are (should be) either all Ls or all Rs, and then we flip
        // some to make them all equal. (at the beginning, L was simply chosen as the general
        // color for convenience.) now, everything should be equal to all Ls, and if there are
        // any Rs, then we can use the algorithm above (which takes into consideration the one
        // problem cow case) to get the answer.
    }

    static char swap(char lr) {
        if (lr == 'L') return 'R';
        else return 'L';
    }
}
