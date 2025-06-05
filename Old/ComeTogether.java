import java.util.*;
import java.io.*;

public class ComeTogether {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <= t; i++) {
            int xa = sc.nextInt();
            int ya = sc.nextInt();
            int xb = sc.nextInt() - xa;
            int yb = sc.nextInt() - ya;
            int xc = sc.nextInt() - xa;
            int yc = sc.nextInt() - ya;
            if (xb>=0 && xc >=0 || (xb<0 && xc<0)) {
                if (yb>=0 && yc >= 0 || yb<0 && yc<0) {
                    pw.println(1 + Math.min(Math.abs(xb), Math.abs(xc)) + Math.min(Math.abs(yb), Math.abs(yc)));
                } else {
                    pw.println(1 + Math.min(Math.abs(xb), Math.abs(xc)));
                }
            } else {
                // opposite sides horizontally
                if (yb>=0 && yc>=0 || (yb<0 && yc<0)) {
                    pw.println(1 + Math.min(Math.abs(yb), Math.abs(yc)));
                } else {
                    pw.println(1);
                }
            }
        }

        sc.close(); pw.close();
    }
}
