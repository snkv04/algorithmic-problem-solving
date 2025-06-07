import java.util.*;
import java.io.*;

public class Flowers {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int t = Integer.parseInt(line[0]);
        int k = Integer.parseInt(line[1]);

        int[] memo = new int[100001];
        memo[0] = 1;
        for (int i = 1; i <= 100000; i++) {
            memo[i] = memo[i-1];
            if (i-k>=0) memo[i] += memo[i-k];
            memo[i] %= (int) (1e9+7);
        }
        // pw.println(Arrays.toString(memo));
        int[] prefsums = new int[100001];
        prefsums[1] = memo[1];
        for (int i = 2; i <= 100000; i++) {
            prefsums[i] = prefsums[i-1] + memo[i];
            prefsums[i] %= 1000000007;
        }

        while (t-->0) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            int start = prefsums[a-1];
            int end = prefsums[b];
            if (end < start) {
                end += (int)(1e9+7);
            }
            pw.println(end-start);
        }
        
        br.close(); pw.close();
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
