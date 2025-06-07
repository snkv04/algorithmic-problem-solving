import java.util.*;
import java.io.*;

public class TeaWithTangerines {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int min = Integer.MAX_VALUE;
            for (int num : a) {
                if (num < min) min = num;
            }

            int answer = 0;
            for (int j = 0; j <= n-1; j++) {
                if (a[j] >= 2 * min) {
                    int divisor = 2 * min - 1;
                    if (a[j] % divisor == 0) answer += (a[j] / divisor) - 1;
                    else answer += a[j] / divisor;
                }
            }
            pw.println(answer);
        }

        br.close(); pw.close();
    }
}
