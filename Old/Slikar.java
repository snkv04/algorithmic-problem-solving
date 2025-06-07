import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class Slikar {
    static BufferedReader br;
    static PrintWriter pw;
    static int[][] grid;

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
        /*
         * for each square, store the number of cells wrong if all cells in that square are
         *      painted completely white, completely black, or using josip's process (for a
         *      square of size one, this means the error is 0)
         * this should be available for every possible size. so, we can have a 4d array memo
         *      where memo[i][j][k][l] = the number of cells wrong in the k*k-sized square
         *      with its top left on cell (i, j), if using the painting method l, where
         *      l is in {0 -> painting with all 0s, 1 -> painting with all 1s,
         *      2 -> using josip's method}
         * for l == 2, we can use some recursion-like process, and for l == 0 || l == 1,
         *      we can use a 2d prefix sum array
         * 
         * algorithm (complexity O(n^2)):
         * first make the prefix sum matrix. have it accumulate the number of 1s, and the number
         *      of 0s can be retrieved by subtracting the 2D prefix sum from the area of the query
         * for each square side length k from 1 to log_2(n), do the following:
         *      for each square of that side length (which will require making i and j both skip
         *              across the matrix with steps of size k), do the following:
         *          for l == 0, calculate memo[i][j][k][l]
         *          for l == 1, calculate it
         *          for l == 2, given that a subsquare is referring to a square of size (k/2)*(k/2)
         *                  within the bounds of the current square, go through all 4*3*1*1=12
         *                  selections of black and white subsquares (where the remaining 2 subsquares
         *                  use josip's weird method), select the one with minimum error and set
         *                  memo[i][j][k][l] to that
         * now, starting from the largest possible square (the one of size log_2(n)*log_2(n) with its
         *          top-left corner at (i=0, j=0)):
         *      find the permutation of black/white/indeterminate 4 subsquares with minimum cost
         *      for that found permutation, paint the white subsquare white, the black black, and
         *              add the 2 indeterminate subsquares to the queue
         * print out the final matrix
         */

        // Reads input.
        int n = Integer.parseInt(br.readLine());
        String[] _grid = new String[n]; for (int i = 0; i <= n-1; i++) _grid[i] = br.readLine();
        if (n == 1) {
            pw.println(0);
            pw.println(_grid[0]);
            return;
        }
        grid = new int[n][n];
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= n-1; j++) {
                grid[i][j] = _grid[i].charAt(j) - '0';
            }
        }

        // Constructs 2d prefix sums.
        int[][] prefix = new int[n][n];
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= n-1; j++) {
                prefix[i][j] = grid[i][j]
                    + (j-1>=0 ? prefix[i][j-1] : 0)
                    + (i-1>=0 ? prefix[i-1][j] : 0)
                    - (i-1>=0&&j-1>=0 ? prefix[i-1][j-1] : 0);
            }
        }

        // Calculates all error values and stores the results (though the array's usage
        // gets sparser the greater k is).
        int logn = 0; while ((1 << logn) < n) logn++;
        int[][][][] memo = new int[n][n][logn+1][3];
        for (int k = 0; k <= logn; k++) {
            int step = 1 << k;
            for (int i = 0; i < n; i += step) {
                for (int j = 0; j <= n-1; j += step) {
                    // If we're looking at a single square, the results are easy to calculate.
                    if (k == 0) {
                        memo[i][j][k][0] = grid[i][j];
                        memo[i][j][k][1] = 1 - grid[i][j];
                        memo[i][j][k][2] = 0;
                        continue;
                    }

                    // Calculates results for using all 0s or all 1s.
                    int endi = i + step-1, endj = j + step-1;
                    int ones = prefix[endi][endj]
                        - (endj-step>=0 ? prefix[endi][endj-step] : 0)
                        - (endi-step>=0 ? prefix[endi-step][endj] : 0)
                        + (endi-step>=0&&endj-step>=0 ? prefix[endi-step][endj-step] : 0);
                    memo[i][j][k][0] = ones;
                    memo[i][j][k][1] = step*step - ones;

                    // Calculates best-case results of looking at all "permutations" of the 4 subsquares.
                    Point[] points = {
                        new Point(i, j),
                        new Point(i + step/2, j),
                        new Point(i, j + step/2),
                        new Point(i + step/2, j + step/2),
                    };
                    int best = Integer.MAX_VALUE;
                    // Point bestwhite = null, bestblack = null;
                    int sum = 0; for (Point p : points) sum += memo[p.i][p.j][k-1][2];
                    for (int white = 0; white <= 3; white++) {
                        for (int black = 0; black <= 3; black++) {
                            if (white == black) continue;

                            Point w = points[white], b = points[black];
                            int curr = sum - memo[w.i][w.j][k-1][2] + memo[w.i][w.j][k-1][0]
                                - memo[b.i][b.j][k-1][2] + memo[b.i][b.j][k-1][1];
                            if (curr < best) {
                                best = curr;
                                // bestwhite = w;
                                // bestblack = b;
                            }
                        }
                    }
                    memo[i][j][k][2] = best;
                }
            }
        }
        // for (int i = 0; i <= n-1; i++) {
        //     for (int j = 0; j <= n-1; j++) {
        //         for (int k = 0; k <= logn; k++) {
        //             pw.println("memo[i="+i+"][j="+j+"][k="+k+"] = "+Arrays.toString(memo[i][j][k]));
        //         }
        //     }
        // }

        // Goes through all possible subsquares, either painting them or delegating the process to
        // smaller subsquares as needed.
        Queue<String> q = new LinkedList<>();
        q.add("0 0 "+logn);
        int ans = 0;
        while (!q.isEmpty()) {
            String[] split = q.poll().split(" ");
            int i = Integer.parseInt(split[0]), j = Integer.parseInt(split[1]), k = Integer.parseInt(split[2]);
            int size = (1 << (k-1)); // k will be >= 1
            Point[] points = {
                new Point(i, j),
                new Point(i + size, j),
                new Point(i, j + size),
                new Point(i + size, j + size),
            };
            int best = Integer.MAX_VALUE;
            Point bestwhite = null, bestblack = null; HashSet<Integer> others = new HashSet<>();
            int sum = 0; for (Point p : points) sum += memo[p.i][p.j][k-1][2];
            for (int white = 0; white <= 3; white++) {
                for (int black = 0; black <= 3; black++) {
                    if (white == black) continue;

                    Point w = points[white], b = points[black];
                    int curr = sum - memo[w.i][w.j][k-1][2] + memo[w.i][w.j][k-1][0]
                        - memo[b.i][b.j][k-1][2] + memo[b.i][b.j][k-1][1];
                    if (curr < best) {
                        best = curr;
                        others = new HashSet<>(); for (int idx = 0; idx <= 3; idx++) others.add(idx);
                        others.remove(white); others.remove(black);
                        bestwhite = w; bestblack = b;
                    }
                }
            }
            ans += memo[bestwhite.i][bestwhite.j][k-1][0] + memo[bestblack.i][bestblack.j][k-1][1];
            
            paint(bestwhite.i, bestwhite.j, size, 0);
            paint(bestblack.i, bestblack.j, size, 1);
            if (k > 1) {
                for (int other : others) {
                    Point p = points[other];
                    q.add(p.i+" "+p.j+" "+(k-1));
                }
            }
        }

        pw.println(ans);
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= n-1; j++)
                pw.print(grid[i][j]);
            pw.println();
        }
    }

    static void paint(int toplefti, int topleftj, int size, int color) {
        // pw.println("painting "+(color==0?"white":"black")+" from ("+toplefti+", "
        //     +topleftj+") to ("+(toplefti+size-1)+", "+(topleftj+size-1)+")");
        for (int i = toplefti; i <= toplefti+size-1; i++) {
            for (int j = topleftj; j <= topleftj+size-1; j++) {
                grid[i][j] = color;
            }
        }
    }

    static class Point {
        int i, j;

        public Point(int i, int j) {
            this.i = i;
            this.j = j;
        }

        // int x, y;

        // public Point(int x, int y) {
        //     this.x = x;
        //     this.y = y;
        // }
    }
}
