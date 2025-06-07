import java.util.*;
import java.io.*;

public class HighestHill {
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
        int n = Integer.parseInt(br.readLine());
        long[] h = Arrays.stream(br.readLine().split(" ")).mapToLong(Long::parseLong).toArray();
        long[] minLeft = new long[n], minRight = new long[n];
        long min = h[0];
        for (int i = 0; i < n; i++) {
            if (i == 0 || h[i] < h[i-1]) {
                min = h[i];
            }
            minLeft[i] = h[i] - min;
        }
        min = h[n-1];
        for (int i = n-1; i >= 0; i--) {
            if (i == n-1 || h[i] < h[i+1]) {
                min = h[i];
            }
            minRight[i] = h[i] - min;
        }

        long best = 0;
        for (int i = 0; i < n; i++) {
            best = Math.max(best, Math.min(minLeft[i], minRight[i]));
        }
        pw.println(best);
    }
}