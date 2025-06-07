import java.util.*;
import java.io.*;

public class MEXAndArray {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            int[] a = new int[n];
            for (int i = 0; i <= n-1; i++) a[i] = sc.nextInt();

            int sum = 0;
            for (int i = 0; i <= n-1; i++) {
                int num0s = 0;
                for (int j = i; j <= n-1; j++) {
                    if (a[j]==0) num0s++;
                    sum += j-i+1 + num0s;
                }
            }
            System.out.println(sum);
        }

        sc.close();
    }
}