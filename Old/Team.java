import java.util.*;
import java.io.*;

public class Team {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (sc.nextInt() + sc.nextInt() + sc.nextInt() >= 2) count++;
        }
        pw.print(count);

        sc.close(); pw.close();
    }
}
