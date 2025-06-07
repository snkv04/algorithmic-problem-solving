import java.util.*;
import java.io.*;

public class RobotBreakout {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int queries = sc.nextInt();
        for (int q = 1; q <= queries; q++) {
            int n = sc.nextInt();
            // bounds are inclusive
            int leftbound = (int) -1e5;
            int rightbound = (int) 1e5;
            int upbound = (int) 1e5;
            int downbound = (int) -1e5;
            boolean works = true;
            for (int i = 1; i <= n; i++) {
                int x = sc.nextInt();
                int y = sc.nextInt();
                if (sc.nextInt() == 0) {
                    leftbound = Math.max(leftbound, x);
                }
                if (sc.nextInt() == 0) {
                    upbound = Math.min(upbound, y);
                }
                if (sc.nextInt() == 0) {
                    rightbound = Math.min(rightbound, x);
                }
                if (sc.nextInt() == 0) {
                    downbound = Math.max(downbound, y);
                }

                if (rightbound < leftbound || upbound < downbound) {
                    works = false;
                    // have to keep taking inputs but they don't matter anymore
                }
            }
            if (works) {
                pw.println("1 " + leftbound + " " + downbound);
            } else pw.println(0);
        }

        sc.close(); pw.close();
    }
}
