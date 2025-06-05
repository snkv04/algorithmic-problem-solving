import java.util.*;
import java.io.*;

public class AngryCows {
    static int n, k;
    static int[] x;

    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("angry.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        k = Integer.parseInt(line[1]);
        x = new int[n];
        for (int i = 0; i <= n-1; i++) x[i] = Integer.parseInt(br.readLine());
        Arrays.sort(x);
        long low = 0, high = (long) Integer.MAX_VALUE, ans = -1;
        while (low <= high) {
            long mid = (low + high) / 2;
            if (check(mid)) {
                high = mid - 1;
                ans = mid;
            } else {
                low = mid + 1;
            }
        }
        pw.print(ans);

        br.close(); pw.close();
    }

    static boolean check(long num) {
        int i = 0;
        // will look at each bale only once for each tested value, so still O(n)
        for (int cow = 1; (cow <= k) && (i <= n-1); cow++) {
            long range_min = (long) x[i];
            long range_max = range_min + (2 * num);

            while (i <= n-1 && x[i] <= range_max) {

                i++;
            }
        }

        if (i == n) return true;
        else return false;
    }
}
