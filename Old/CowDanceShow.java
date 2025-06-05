import java.util.*;
import java.io.*;

public class CowDanceShow {
    static int n, t_max;
    static int[] d;
    static TreeMap<Long, Integer> multiset;

    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("cowdance.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cowdance.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        t_max = Integer.parseInt(line[1]);
        d = new int[n];
        for (int i = 0; i <= n-1; i++) {
            d[i] = Integer.parseInt(br.readLine());
        }

        long left = 0, right = n, ans = -1;
        while (left <= right) {
            long mid = (left + right) / 2;
            if (check((int) mid)) {
                right = mid-1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        pw.print(ans);

        br.close(); pw.close();
    }

    static void add(long x) {
        if (multiset.containsKey(x)) {
            multiset.put(x, multiset.get(x) + 1);
        } else {
            multiset.put(x, 1);
        }
    }

    static void remove(long x) {
        multiset.put(x, multiset.get(x) - 1);
        if (multiset.get(x) == 0) {
            multiset.remove(x);
        }
    }

    static boolean check(int k) {
        multiset = new TreeMap<Long, Integer>();
        for (int i = 0; i <= k-1; i++) {
            add(d[i]);
        }
        for (int i = k; i <= n-1; i++) {
            if (multiset.firstKey() + d[i] <= t_max) {
                add(multiset.firstKey() + d[i]);
                remove(multiset.firstKey());
            } else {
                return false;
            }
        }
        return true;
    }
}
