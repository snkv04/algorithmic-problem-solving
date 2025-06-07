import java.util.*;
import java.io.*;

public class MaximumMedian {
    static int n;
    static int k;
    static int[] a;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        k = Integer.parseInt(line[1]);
        a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(a);
        long low = 1, high = (long) Integer.MAX_VALUE - 1, answer = -1;
        while (low <= high) {
            long mid = (low + high) / 2;
            if (check(mid)) {
                low = mid + 1;
                answer = mid;
            } else {
                high = mid - 1;
            }
        }
        pw.print(answer);

        br.close(); pw.close();
    }

    static boolean check(long x) {
        int operations = k;
        for (int i = n/2; (i <= n-1) && (operations >= 0); i++) {
            operations -= Math.max(0, x - a[i]);
        }

        if (operations < 0) return false;
        else return true;
    }
}
