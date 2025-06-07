import java.util.*;
import java.io.*;

public class TheManWhoBecameAGod {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int sum = 0;
            int[] diffs = new int[n-1];
            for (int i = 0; i <= n-2; i++) {
                int diff = Math.abs(a[i+1]-a[i]);
                sum += diff;
                diffs[i] = diff;
            }
            Arrays.sort(diffs);
            for (int i = n-2; i >= n-k; i--) {
                sum -= diffs[i];
            }
            pw.println(sum);
        }

        br.close(); pw.close();
    }
}
