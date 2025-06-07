import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class FenceBowling {
    static BufferedReader br;
    static PrintWriter pw;
    static int b, w, l;

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
        String[] line = br.readLine().split(" ");
        b = Integer.parseInt(line[0]);
        w = Integer.parseInt(line[1]);
        l = Integer.parseInt(line[2]);

        double lo = 0.000001, hi = Math.PI / 2 - 0.000001, ans = -1;
        for (int i = 1; i <= 100; i++) {
            double mid = (lo + hi) / 2;
            if (check(mid)) {
                ans = mid;
                lo = mid;
            } else {
                hi = mid;
            }
        }
        pw.println(Math.toDegrees(ans));
    }

    public static boolean check(double angle) {
        double x = 0.5 * w, y = 0, m = Math.tan(angle);
        boolean goingRight = true;
        int bounces = 0;
        while (true) {
            if (bounces == b) {
                double newX = (double) w / 2;
                double newY = m * (newX - x) + y;
                return newY <= l;
            }
            double newX;
            newX = goingRight ? w : 0;
            double newY = m * (newX - x) + y;
            x = newX; y = newY;
            m *= -2;
            bounces++;
            goingRight = !goingRight;
        }
    }
}
