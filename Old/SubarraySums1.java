import java.util.*;
import java.io.*;

public class SubarraySums1 {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        long x = Long.parseLong(line[1]);
        long[] a = Arrays.stream(br.readLine().split(" ")).mapToLong(Long::parseLong).toArray();
        long[] prefix = new long[n];
        prefix[0] = a[0];
        for (int i = 1; i <= n-1; i++) {
            prefix[i] = prefix[i-1] + a[i];
        }

        int left=0, right=0, result = 0;
        while (right <= n-1) {
            long sum = prefix[right];
            if (left != 0) sum -= prefix[left-1];

            if (sum < x) {
                right++;
            } else if (sum > x) {
                if (left == right) {
                    left++; right++;
                } else left++;
            } else {
                result++;
                left++;
                right++;
            }
        }
        pw.print(result);

        br.close(); pw.close();
    }
}
