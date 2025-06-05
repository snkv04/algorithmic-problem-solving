import java.util.*;
import java.io.*;

public class Convention {
    static int n, m, c;
    static int[] t;

    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("convention.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("convention.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        c = Integer.parseInt(line[2]);
        t = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(t);
        long low = 0, high = (long) Integer.MAX_VALUE, ans = -1;
        while (low <= high) {
            long mid = (low + high) / 2;
            if (check(mid)) {
                high = mid-1;
                ans = mid;
            } else {
                low = mid+1;
            }
        }
        pw.println(ans);
        // for (int i = 1; i <= 20; i++) {
        //     pw.println("i="+i+", check(i)="+check(i));
        // }

        br.close(); pw.close();
    }

    static boolean check(long x) {
        int i = 0;
        // will still visit every cow once so still O(n)
        for (int bus = 1; (bus <= m) && (i <= n-1); bus++) {
            long earliest = (long) t[i];
            long latest = earliest + x;

            int count = 1;
            while (i <= n-1 && t[i] <= latest && count <= c) {
                i++;
                count++;
            }
        }

        if (i == n) return true;
        else return false;
    }
}