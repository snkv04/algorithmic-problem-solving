import java.util.*;
import java.io.*;

public class BadPrices {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i =1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int min = Integer.MAX_VALUE;
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int ans = 0;
            for (int j = n-1; j>=0; j--) {
                if (a[j] > min) ans++;
                if (a[j] < min) min = a[j];
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
