import java.util.*;
import java.io.*;

public class ForbiddenInteger {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int x = Integer.parseInt(line[2]);
            
            if (x!=1) {
                pw.println("YES");
                pw.println(n);
                for (int j=1; j<=n; j++) pw.print(1 + " ");
                pw.println();
            } else {
                if (k==1) {
                    pw.println("NO");
                } else if (k==2) {
                    if (n%2==1) {
                        pw.println("NO");
                    } else {
                        pw.println("YES");
                        pw.println(n/2);
                        for (int j = 1; j <= n/2; j++) {
                            pw.print(2+" ");
                        }
                        pw.println();
                    }
                } else {
                    // k >= 3
                    pw.println("YES");
                    if (n%3==0) {
                        pw.println(n/3);
                        for (int j= 1; j<=n/3;j++) pw.print(3+" ");
                        pw.println();
                    } else if (n%3==1) {
                        pw.println(((n-4)/3) + 2);
                        for (int j=1; j<=(n-4)/3; j++) pw.print(3+" ");
                        pw.println("2 2 ");
                    } else {
                        pw.println(((n-2)/3) + 1);
                        for (int j=1; j<=(n-2)/3; j++) pw.print(3+" ");
                        pw.println("2 ");
                    }
                }
            }
        }

        br.close(); pw.close();
    }
}
