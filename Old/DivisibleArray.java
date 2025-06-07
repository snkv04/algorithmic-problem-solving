import java.util.*;
import java.io.*;

public class DivisibleArray {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = new int[n];
            int sum = 0;
            for (int j = 0; j <= n-1; j++) {
                int index = j+1;
                a[j] = index;
                sum += index;
            }
            if (sum % n != 0) {
                int remainder = sum % n;
                a[0] += n-remainder;
            }

            for (int element : a) pw.print(element + " ");
            pw.println();
        }

        br.close(); pw.close();
    }
}
