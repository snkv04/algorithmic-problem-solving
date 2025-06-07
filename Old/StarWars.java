import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class StarWars {
    static BufferedReader br;
    static PrintWriter pw;
    static double[][] ships;
    static int n;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        for (int i = 1; i <= t; i++) {
            solve(i);
        }

        br.close(); pw.close();
    }

    static void solve(int testCase) throws IOException {
        /*
         * Suppose that the cruiser, c, is in a fixed location (xc, yc, zc). Straight from the
         * problem, we can see that p_c * p_i must be greater than or equal to the Manhattan
         * distance between the cruiser and ship i for all ships 1 ≤ i ≤ n. Imagine a field
         * around each ship in the shape of an octahedron. Each ship's octahedron has its
         * maximum Manhattan distance "radius" set to p_c * p_i. Any such value of p_c will be
         * valid if there exists a point in 3-dimensional space where every single one of the
         * fields overlap, because the cruiser could just be placed right there. However,
         * finding the intersection between N different octahedron solids is really annoying.
         * How could we do it faster?
         * Well, fortunately, it can be observed that having a point which every octahedron
         * overlaps is equivalent to checking if every pair of octahedrons overlap each other.
         * This can be seen from the 2D case where we are looking at diamonds instead of
         * octahedrons in the shape of the inequality |x| + |y| <= some_value. Due to
         * all of the diamonds having the same slope for their corresponding sides, it can't
         * be the case that 3 diamonds cover at least one point without every pair of them
         * overlapping, and it can't be the case that every pair of them overlaps without there
         * existing a point contained in all of them. The best part is that checking if two
         * octahedrons overlap is very easy, since you can just visually see that the Manhattan
         * distance between the two centers must be less than or equal to the sum of the "radii"
         * of the two octahedrons.
         * So, we can just binary search directly on the answer.
         */

        n = Integer.parseInt(br.readLine());
        ships = new double[n][4];
        for (int i = 0; i <= n-1; i++) {
            ships[i] = Arrays.stream(br.readLine().split(" ")).mapToDouble(Double::parseDouble).toArray();
        }

        double l = 1e-9, r = 1e9, pc = -1;
        for (int i = 1; i <= 70; i++) {
            double mid = (l+r)/2;
            if (check(mid)) {
                pc = mid;
                r = mid;
            } else {
                l = mid;
            }
        }
        pw.println("Case #"+testCase+": "+pc);
    }

    static boolean check(double pc) {
        for (int i = 0; i <= n-1; i++) {
            for (int j = i+1; j <= n-1; j++) {
                double r1 = ships[i][3] * pc, r2 = ships[j][3] * pc;
                double taxiDist = Math.abs(ships[i][0]-ships[j][0])
                    + Math.abs(ships[i][1]-ships[j][1])
                    + Math.abs(ships[i][2]-ships[j][2]);
                if (taxiDist > r1 + r2) {
                    return false;
                }
            }
        }
        return true;
    }
}
