import java.util.*;
import java.io.*;

public class RestoreTheArray {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        int t = Integer.parseInt(br.readLine());
        for (int i =1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] b = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] a = new int[n];
            for (int j = 0; j <= n-1; j++) {
                if (j == 0) a[j] = b[j];
                else if (j==n-1) a[j] = b[j-1];
                else a[j] = Math.min(b[j], b[j-1]);
            }

            for (int j=0; j<=n-1; j++) {
                System.out.print(a[j]+" ");
            }
            System.out.println();
        }
        br.close(); pw.close();
    }
}
