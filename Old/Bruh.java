import java.util.*;
import java.io.*;

public class Bruh {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <=t; i++) {
            int n = sc.nextInt();
            int s = sc.nextInt();
            int k = sc.nextInt();
            TreeSet<Integer> closed = new TreeSet();
            for (int j=1; j<=k; j++) {
                closed.add(sc.nextInt());
            }
            int dist = -1;
            for (int x = 0; x <= 1001; x++) {
                if ((s+x<=n&&!closed.contains(x+s))||(s-x>0&&!closed.contains(s-x))) {
                    dist = x;
                    break;
                }
            }
            pw.println(dist);
        }

        sc.close(); pw.close();
    }
}
