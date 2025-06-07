import java.util.*;
import java.io.*;

public class StableGroups {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        long k = sc.nextLong();
        long x = sc.nextLong();
        Long[] a = new Long[n];
        for (int i = 0; i <= n-1; i++) a[i] = sc.nextLong();
        Arrays.sort(a);

        ArrayList<Integer> segmentEnds = new ArrayList<Integer>();
        for (int i = 1; i <= n-1; i++) {
            if (a[i] - a[i-1] > x) {
                segmentEnds.add(i-1);
            }
        }
        segmentEnds.add(n-1);

        ArrayList<Long> gaps = new ArrayList<Long>();
        for (int i = 0; i <= segmentEnds.size()-2; i++) {
            int end = segmentEnds.get(i);
            gaps.add(a[end+1]-a[end]);
        }
        Collections.sort(gaps);
        // pw.println(segmentEnds);
        // pw.println(gaps);
        
        long ans = segmentEnds.size();
        for (long gap : gaps) {
            long need = (gap-1)/x;
            if (k-need < 0) {
                break;
            } else {
                k -= need;
                ans--;
            }
        }
        pw.println(ans);

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
