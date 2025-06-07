import java.util.*;
import java.io.*;

public class MinMaxSort {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <=t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] loc = new int[n+1];
            for (int j = 0; j <= n-1; j++) {
                loc[p[j]] = j+1;
            }
            // pw.println(Arrays.toString(loc));

            int ans = 0;
            for (int j = n/2; j >= 1; j--) {
                if (!(loc[j] < loc[j+1] && loc[n+1-j] > loc[n-j])) {
                    ans = j;
                    break;
                }
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
