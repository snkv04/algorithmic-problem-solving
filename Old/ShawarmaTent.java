import java.util.*;
import java.io.*;

public class ShawarmaTent {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int sx = Integer.parseInt(line[1]);
        int sy = Integer.parseInt(line[2]);
        int l=0, r=0, u=0, d=0;
        for (int i = 1; i <= n; i++) {
            line = br.readLine().split(" ");
            int x = Integer.parseInt(line[0]);
            int y = Integer.parseInt(line[1]);
            if (x < sx) l++;
            if (x>sx) r++;
            if (y<sy) d++;
            if (y>sy) u++;
        }
        int max = Math.max(Math.max(l, r), Math.max(u, d));
        pw.println(max);
        if (l == max) {
            pw.print(sx-1 + " " + sy);
        } else if (r==max) {
            pw.print(sx+1 + " " + sy);
        } else if (u==max) {
            pw.print(sx + " " + (sy+1));
        } else {
            pw.print(sx+" "+(sy-1));
        }

        br.close(); pw.close();
    }
}
