import java.util.*;
import java.io.*;

public class KevinAndPermutation {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int half = n / 2;
            int[] permutation = new int[n];
            for (int j = 1; j <= half; j++) {
                permutation[(j-1) * 2] = half + j;
                permutation[(j-1) * 2 + 1] = j;
            }
            if (n % 2 == 1) permutation[n-1] = n;
            
            for (int element : permutation) pw.print(element + " ");
            pw.println();
        }

        br.close(); pw.close();
    }
}