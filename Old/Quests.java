import java.util.*;
import java.io.*;

public class Quests {
    static int n, d;
    static long c;
    static Integer[] a;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            n = sc.nextInt();
            c = sc.nextLong();
            d = sc.nextInt();
            a = new Integer[n];
            for (int i = 0; i <= n-1; i++) a[i] = sc.nextInt();
            Arrays.sort(a);

            long left = 0, right = Integer.MAX_VALUE;
            int ans = -1;
            while (left <= right) {
                long mid = (left + right) / 2;
                if (check(mid)) {
                    ans = (int) mid;
                    left = mid+1;
                } else {
                    right = mid-1;
                }
            }
            pw.println(ans==-1?("Impossible"):(ans==Integer.MAX_VALUE?"Infinity":ans));
        }

        sc.close(); pw.close();
    }

    static boolean check(long k) {
        int mod = (int) k+1;
        long coins = 0;
        for (int i = 0; i <= d-1; i++) {
            int ind = n - 1 - (i%mod);
            if (ind >= 0) {
                coins += a[ind];
            }
            if (coins >= c) return true;
        }
        return false;
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
