import java.util.*;
import java.io.*;

public class SaveEnergy {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        double k = sc.nextLong();
        double d = sc.nextLong();
        double t = sc.nextLong();
        double[] cycle = new double[2];
        if (d<=k) {
            if (k%d == 0) {
                cycle = new double[] {k, 0};
            } else {
                cycle = new double[] {k, d-(k%d)};
            }
        } else {
            cycle = new double[] {k, d-k};
        }
        double timeCompleted = cycle[0] + cycle[1]/2;
        // pw.println(Arrays.toString(cycle));

        double ans = 0;
        double cycles = (long) (t / timeCompleted);
        ans += cycles * (cycle[0] + cycle[1]);
        double remaining = t - cycles * timeCompleted;
        ans += Math.min(remaining, cycle[0]);
        remaining -= Math.min(remaining, cycle[0]);
        ans += Math.min(remaining, cycle[1]/2)*2;
        pw.println(ans);

        sc.close(); pw.close();
    }
}
