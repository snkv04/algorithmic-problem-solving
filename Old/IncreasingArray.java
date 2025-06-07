import java.util.*;
import java.io.*;

public class IncreasingArray {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        long result = 0;
        for (int i = 1; i <= n-1; i++) {
            int diff = Math.max(0, a[i-1] - a[i]);
            result += diff;
            a[i] += diff;
        }
        pw.print(result);

        br.close(); pw.close();
    }
}
