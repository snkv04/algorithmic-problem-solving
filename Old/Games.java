import java.util.*;
import java.io.*;

public class Games {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int[] h = new int[n];
        int[] g = new int[n];
        for (int i = 0; i <= n-1; i++) {
            h[i] = sc.nextInt();
            g[i] = sc.nextInt();
        }
        
        int count = 0;
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= n-1; j++) {
                if (i==j) continue;
                if (h[i]==g[j]) count++;
            }
        }
        pw.println(count);

        sc.close(); pw.close();
    }
}
