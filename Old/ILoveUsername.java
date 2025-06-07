import java.util.*;
import java.io.*;

public class ILoveUsername {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt((Integer::parseInt)).toArray();
        int max = a[0];
        int min = a[0];
        int ans = 0;
        for (int i = 1; i <= n-1; i++) {
            if (a[i] < min) {
                ans++;
                min = a[i];
            }
            if (a[i] > max) {
                ans++;
                max = a[i];
            }
        }
        pw.println(ans);

        br.close(); pw.close();
    }
}
