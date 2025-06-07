import java.util.*;
import java.io.*;

public class MagnesiumSupplementation {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] asdf = br.readLine().split(" ");
        long n = Long.parseLong(asdf[0]), k = Long.parseLong(asdf[1]), p = Long.parseLong(asdf[2]);
        HashSet<Long> factors = new HashSet<>();
        for (int i = 1; i <= Math.min(k, (int)Math.sqrt(n)); i++) {
            if (n%i==0) {
                factors.add((long)i);
                factors.add(n/(long)i);
            }
        }
        // pw.println(factors);

        PriorityQueue<Long> pq = new PriorityQueue<>();
        for (long f : factors) {
            if (f <= k && n / f <= p) {
                pq.add(f);
            }
        }
        
        pw.println(pq.size());
        while (!pq.isEmpty()) pw.println(pq.poll());
    }
}