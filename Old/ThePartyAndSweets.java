import java.util.*;
import java.io.*;

public class ThePartyAndSweets {
    static TreeMap<Long, Long> multiset;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        long n = sc.nextLong();
        long m = sc.nextLong();
        Long[] b = new Long[(int)n];
        for (int i = 0; i <= n-1; i++) b[i] = sc.nextLong();
        Long[] g = new Long[(int)m];
        for (int i = 0; i <= m-1; i++) g[i] = sc.nextLong();
        Arrays.sort(b); Arrays.sort(g);
        if (g[0] < b[(int)n-1]) {
            pw.print(-1);
            pw.close();
            return;
        }

        // long ans = 0;
        // multiset = new TreeMap<Long, Long>();
        // for (int i = 0; i <= n-1; i++) {
        //     ans += b[i] * m;
        //     add((int)(long)b[i], m-1);
        // }
        // pw.println(multiset);
        // pw.println(ans);
        // for (int i = (int)m-1; i >= 0; i--) {
        //     long max = g[i];
        //     pw.println("i="+i+", and floor is "+multiset.floorKey(max)+", so removing that and incrememnting ans by "+(max-multiset.floorKey(max)));
        //     ans += max - multiset.floorKey(max);
        //     remove(multiset.floorKey(max));
        //     pw.println("now, multiset is "+multiset);
        // }
        // pw.print(ans);

        long ans = 0;
        // multiset contains every value of the amount that boy i gives to girl j, for all
        // boys i and girls j. this multiset is implemented using a treemap as normal
        multiset = new TreeMap<Long, Long>();
        for (int i = 0; i <= n-1; i++) {
            ans += b[i] * m;
            add(b[i], m);
        }
        // pw.println(multiset);
        for (int i = (int)m-1; i >= 0; i--) {
            long toGive = g[i];
            // pw.println("i="+i+", and toGive="+toGive);
            while (!((multiset.get(multiset.lastKey())>=1 && multiset.lastKey()==toGive)
                || (multiset.get(multiset.lastKey())>1 && multiset.lastKey() < toGive))) {

                multiset.pollLastEntry();
            }
            // pw.println("multiset after scrolling to a usable value = "+multiset);
            // last sweet-giving entry can be increased to the current girl's maximum
            ans += toGive - multiset.lastKey();
            remove(multiset.lastKey());
            // pw.println("multiset after using the last one = "+multiset+"\n");
        }
        pw.print(ans);

        sc.close(); pw.close();
    }

    static void add(long num, long q) {
        if (multiset.containsKey(num)) {
            multiset.put(num, multiset.get(num)+q);
        } else {
            multiset.put(num, q);
        }
    }

    static void remove(long num) {
        multiset.put(num, multiset.get(num)-1);
        if (multiset.get(num)==0) multiset.remove(num);
    }
}
