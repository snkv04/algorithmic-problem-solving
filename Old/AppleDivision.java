import java.util.*;
import java.io.*;

public class AppleDivision {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] apples = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        long minDiff = Long.MAX_VALUE;
        for (int i = 0; i <= (1<<n)-1; i++) {
            // ArrayList<Integer> group1 = new ArrayList<>();
            // ArrayList<Integer> group2 = new ArrayList<>();
            long sum1 = 0, sum2 = 0;
            for (int j = 0; j <= n-1; j++) {
                if ((i & 1<<j) == 1<<j) sum1 += apples[j];
                else sum2 += apples[j];
            }
            minDiff = Math.min(Math.abs(sum1-sum2), minDiff);
        }
        pw.println(minDiff);

        br.close(); pw.close();
    }
}
