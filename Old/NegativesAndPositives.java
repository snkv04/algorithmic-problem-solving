import java.util.*;
import java.io.*;

public class NegativesAndPositives {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            long sum = 0;
            int numNegs = 0;
            for (int i = 0; i <= n-1; i++) {
                sum += Math.abs(a[i]);
                if (a[i] < 0) numNegs++;
            }
            if (numNegs%2==0) {
                pw.println(sum);
            } else {
                int min = Integer.MAX_VALUE;
                for (int i = 0; i <= n-1; i++) {
                    min = Math.min(min, Math.abs(a[i]));
                }
                sum -= 2 * min;
                pw.println(sum);
            }
        }

        br.close(); pw.close();
    }
}
