import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class AwwMan {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] split = br.readLine().split(" ");
        long n = Long.parseLong(split[0]), m = Long.parseLong(split[1]);
        split = br.readLine().split(" ");
        long a = Long.parseLong(split[0]), b = Long.parseLong(split[1]), d = Long.parseLong(split[2]);
        a--; b--; // using 0-indexing
        long trip;
        if (a < b) {
            trip = b-a;
        } else {
            trip = n - (a-b);
        }

        long end = (a + d + 2 * trip) % n;
        // pw.println("a="+a+", b="+b+", d="+d+", trip="+trip+", end="+end);
        pw.println((end>=n-m)?"NO":"YES");
    }
}
