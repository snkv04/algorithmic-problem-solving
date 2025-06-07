import java.util.*;
import java.io.*;

public class DiscDistrict {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);
        
        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    public static void solve() throws IOException {
        long r = Integer.parseInt(br.readLine());
        long bestx = r+1, besty = 0;
        long bestdist = (long) (r+1) * (r+1);
        for (long y = 1; y <= r; y++) {
            double x = Math.sqrt((long)r*r - (long)y*y);
            long ceil = (long) Math.floor(x) + 1;
            if (ceil*ceil + y*y < bestdist) {
                bestx = ceil;
                besty = y;
                bestdist = ceil*ceil + y*y;
            }
        }
        // long x = r+1, y = 0;
        // long bestx = r+1, besty = 0;
        // while (y <= r) {
        //     y++;
        //     while (sqdist(x-1, y) > r*r) {
        //         x--;
        //     }
        //     if (sqdist(x, y) < sqdist(bestx, besty)) {
        //         bestx = x;
        //         besty = y;
        //     }
        // }
        pw.println(bestx+" "+besty);
    }

    static long sqdist(long x, long y) {
        return x*x + y*y;
    }

    static class Point {
        long x, y;

        public Point(long x, long y) {
            this.x = x;
            this.y = y;
        }
    }
}