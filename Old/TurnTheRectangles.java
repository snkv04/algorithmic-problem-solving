import java.util.*;
import java.io.*;

public class TurnTheRectangles {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int last = Integer.MAX_VALUE;
        boolean works = true;;
        for (int i = 0; i <= n-1; i++) {
            int w = sc.nextInt();
            int h = sc.nextInt();
            int curr = -1;
            if (w<=last) {
                curr = w;
            }
            if (h <= last) {
                if (curr==-1) curr = h;
                else curr = Math.max(w, h);
            }
            if (curr==-1)  {
                works = false;
                break;
            } else {
                last = curr;
            }
        }
        pw.print(works?"YES":"NO");

        sc.close(); pw.close();
    }
}
