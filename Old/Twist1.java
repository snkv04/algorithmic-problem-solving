import java.util.*;
import java.io.*;

public class Twist1 {
    static int n;
    static int[] a;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            n = Integer.parseInt(br.readLine());
            a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int max = -1;
            for (int i = 0; i <= n-1; i++) {
                max = Math.max(max, check(i, 0));
                max = Math.max(max, check(i, 1));
            }
            pw.println(max);
        }

        br.close(); pw.close();
    }

    static int check(int index, int increase) {
        int curr = a[index] + increase - 1;
        int len = 1;
        for (int i = index-1; i >= 0; i--) {
            if (a[i] == curr || a[i] == curr-1) {
                len++;
                curr--;
            } else if (a[i] < curr-1) {
                break;
            }
            // if current element (a[i]) is equal to curr, then do nothing
        }
        return len;
    }
}
