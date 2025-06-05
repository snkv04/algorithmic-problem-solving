import java.util.*;
import java.io.*;

public class CandyBoxEasyVersion {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int q = Integer.parseInt(br.readLine());
        for (int i = 1; i <= q; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] count = new int[n+1];
            for (int candy : a) {
                count[candy]++;
            }
            Arrays.sort(count);
            long ans = 0;
            int minSoFar = Integer.MAX_VALUE;
            for (int j = n; j >= 1; j--) {
                minSoFar = Math.min(minSoFar-1, count[j]);
                ans += minSoFar;
                if (minSoFar <= 0) break;
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
