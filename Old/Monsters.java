import java.util.*;
import java.io.*;

public class Monsters {
    static TreeMap<Integer, Integer> multiset;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            multiset = new TreeMap<Integer, Integer>();
            for (int i = 1; i <= n; i++) add(sc.nextInt());
            // pw.println(multiset);

            long ans = 0;
            for (int i = 1; i <= multiset.lastKey(); i++) {
                if (multiset.containsKey(i)) {
                    continue;
                } else {
                    int next = multiset.higherKey(i);
                    ans += next-i;
                    add(i);
                    remove(next);
                }
            }
            pw.println(ans);
        }

        sc.close(); pw.close();
    }

    static void add(int x) {
        if (multiset.containsKey(x)) {
            multiset.put(x, multiset.get(x)+1);
        } else {
            multiset.put(x, 1);
        }
    }

    static void remove (int x) {
        multiset.put(x, multiset.get(x)-1);
        if (multiset.get(x)==0) multiset.remove(x);
    }
}
