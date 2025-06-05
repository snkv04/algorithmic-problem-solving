import java.util.*;
import java.io.*;

public class ChoosingTeams {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int k = sc.nextInt();
        int[] remaining = new int[n];
        int count = 0;
        for (int i = 0; i <= n-1; i++) {
            remaining[i] = 5 - sc.nextInt();
            if (remaining[i] >= k) count++;
        }
        pw.println(count/3);

        sc.close(); pw.close();
    }
}
