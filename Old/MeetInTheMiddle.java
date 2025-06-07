import java.util.*;
import java.io.*;

public class MeetInTheMiddle {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;

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
        String[] asdf = br.readLine().split(" ");
        int n = Integer.parseInt(asdf[0]);
        long x = Integer.parseInt(asdf[1]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

        int[] firstHalf = new int[n/2], secondHalf = new int[(n+1)/2];
        for (int i = 0; i <= n-1; i++) {
            if (i < n/2) firstHalf[i] = a[i];
            else secondHalf[i-n/2] = a[i];
        }
        // pw.println(Arrays.toString(firstHalf));
        // pw.println(Arrays.toString(secondHalf));

        Multiset sums1 = makeSums(firstHalf), sums2 = makeSums(secondHalf);
        // pw.println(sums1.mset); pw.println(sums2.mset);
        long ans = 0;
        for (Map.Entry<Long, Integer> entry : sums1.mset.entrySet()) {
            if (sums2.mset.containsKey(x - entry.getKey())) {
                ans += (long) entry.getValue() * sums2.mset.get(x-entry.getKey());
            }
        }
        pw.println(ans);
    }

    static Multiset makeSums(int[] arr) {
        Multiset sums = new Multiset();
        // sums.add(0);
        int len = arr.length;
        for (int i = 0; i < (1<<len); i++) {
            long sum = 0;
            for (int j = 0; j <= len-1; j++) {
                // pw.println("i="+i+", j="+j+", i&(1<<j)="+(i&(1<<j)));
                if ((i&(1<<j)) > 0) sum += arr[j];
            }
            sums.add(sum);
        }
        return sums;
    }

    // // // //

    static class Multiset { // ordered multiset
        HashMap<Long, Integer> mset = new HashMap<>();

        public void add(long x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(long x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(long x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }
}
