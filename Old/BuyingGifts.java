import java.util.*;
import java.io.*;

public class BuyingGifts {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            String[] line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            int maxa = a;
            int maxb = b;
            while (n-->1) {
                line = br.readLine().split(" ");
                a = Integer.parseInt(line[0]);
                b = Integer.parseInt(line[1]);
                if (a < maxa && b < maxb) continue;
                if (Math.abs(Math.max(maxa, a) - maxb) <= Math.abs(Math.max(maxb, b) - maxa)) {
                    maxa = Math.max(maxa, a);
                } else {
                    maxb = Math.max(maxb, b);
                }
            }
            pw.println(Math.abs(maxa - maxb));
        }

        br.close(); pw.close();
    }
}
