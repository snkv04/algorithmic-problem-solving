import java.util.*;
import java.io.*;

public class OddSubarrays {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int count = 0;
            int max = a[0];
            for (int i = 1; i <= n-2; i++) {
                if (a[i] < max) {
                    count++;
                    max = a[i+1];
                } else {
                    max = Math.max(max, a[i]);
                }
            }
            if (a[n-1] < max) count++;
            pw.println(count);
        }

        br.close(); pw.close();
    }
}
