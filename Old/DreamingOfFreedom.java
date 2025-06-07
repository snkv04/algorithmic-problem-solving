import java.util.*;
import java.io.*;

public class DreamingOfFreedom {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int[] leastFactor = new int[1000001];
        for (int i = 2; i <= 50000; i++) {
            for (int j = i; j <= 1000000; j += i) {
                if (leastFactor[j] == 0) {
                    leastFactor[j] = i;
                }
            }
        }

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            if (n == 1 || m == 1) {
                pw.println("YES");
                continue;
            } else if ( n <= m) {
                pw.println("NO");
                continue;
            } else {
                pw.println(leastFactor[n]<=m&&leastFactor[n]!=0 ? "NO" : "YES");
            }
        }

        br.close(); pw.close();
    }

    static int gcd(int a, int b) {
        int min = Math.min(a, b);
        int max = Math.max(a, b);
        while (min != 0) {
            int temp = min;
            min = max % min;
            max = temp;
        }
        return max;
    }

    // // // //

    static class Multiset {
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }
}
