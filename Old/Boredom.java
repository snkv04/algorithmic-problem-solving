import java.util.*;
import java.io.*;

public class Boredom {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int[] count = new int[100002];
        for (int i = 0; i <= n-1; i++) count[sc.nextInt()]++;
        long[] memo = new long[100001];
        for (int i = 1; i <= 100000;i ++) {
            long twobefore = i==1 ? 0 : memo[i-2];
            memo[i] = Math.max(((long)i)*count[i] + twobefore, memo[i-1]);
        }
        pw.print(memo[100000]);

        sc.close(); pw.close();
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
