import java.util.*;
import java.io.*;
/**
 * @author Sri Vangaru
 */
public class MrNoodle {
    static BufferedReader br;
    static PrintWriter pw;
    static int[] a;

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
        int n = Integer.parseInt(br.readLine());
        a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        // Arrays.sort(a);
        double max = Integer.MIN_VALUE; for (int num : a) max = Math.max(max, num);
        double l = max / 2 + 0.000000000001, r = 1e18, ans = -1;
        for (int i = 1; i <= 100; i++) {
            double mid = (l+r)/2;
            if (check(mid)) {
                ans = mid;
                r = mid;
            } else {
                l = mid;
            }
        }
        pw.println(ans);
    }

    static boolean check(double radius) {
        // pw.println("checking radius "+radius);
        double x = radius, y = 0, currAngle = 0;
        for (int i = 0; i <= a.length-1; i++) {
            int edge = a[i];
            double dtheta = 2 * Math.asin((double) edge / (2*radius));
            // if (dtheta < 0.000000000001) return true; // to deal with NaNs
            double nextAngle = currAngle + dtheta;
            // pw.println("next angle for edge "+edge+" is "+nextAngle);
            if (nextAngle > 2 * Math.PI) {
                // pw.println("it went too far");
                return false;
            }
            currAngle = nextAngle;
            x = radius * Math.cos(nextAngle);
            y = radius * Math.sin(nextAngle);
            // pw.println("after edge "+edge+", angle="+currAngle+", x="+x+", y="+y);
        }
        // pw.println("this radius was fine");

        return true;
    }
}
