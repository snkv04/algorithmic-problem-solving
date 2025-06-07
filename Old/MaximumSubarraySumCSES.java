import java.util.*;
import java.io.*;

public class MaximumSubarraySumCSES {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] x = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        long[] maxEndingHere = new long[n];
        long max = x[0];
        maxEndingHere[0]=x[0];
        for (int i = 1; i <= n-1; i++) {
            maxEndingHere[i] = Math.max(maxEndingHere[i-1] + x[i], x[i]);
            max = Math.max(maxEndingHere[i], max);
        }
        pw.println(max);

        br.close(); pw.close();
    }
}