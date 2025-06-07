import java.util.*;
import java.io.*;

public class KoxiaAndWhiteboards {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            Multiset boards = new Multiset();
            for (int i = 1; i <= n; i++) {
                boards.add(sc.nextInt());
            }
            for (int i = 1; i <= m; i++) {
                boards.remove(boards.mset.firstKey());
                boards.add(sc.nextInt());
            }

            long sum = 0;
            while (!boards.mset.isEmpty()) {
                int val = boards.mset.firstKey();
                boards.remove(val);
                sum += val;
            }
            pw.println(sum);
        }

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
