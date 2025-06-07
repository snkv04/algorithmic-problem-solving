import java.util.*;
import java.io.*;

public class LunaticNeverContent {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            TreeSet<Integer> diffs = new TreeSet<Integer>();
            for (int i = 0; i <= (n-1)/2; i++) {
                diffs.add(Math.abs(a[i]-a[n-1-i]));
            }
            int gcd = diffs.pollFirst();
            while (!diffs.isEmpty()) {
                gcd = gcd(gcd, diffs.pollFirst());
            }
            pw.println(gcd);
        }

        br.close(); pw.close();
    }

    static int gcd(int a, int b) {
        int max = Math.max(a, b);
        int min = Math.min(a, b);
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
