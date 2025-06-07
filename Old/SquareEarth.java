import java.util.*;
import java.io.*;

public class SquareEarth {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int x1 = Integer.parseInt(line[1]);
        int y1 = Integer.parseInt(line[2]);
        int x2 = Integer.parseInt(line[3]);
        int y2 = Integer.parseInt(line[4]);
        // if (x1==x2 && y1==y2) {
        //     pw.print(0);
        //     pw.close();
        //     return;
        // }

        // int x = 0, y = 0, points = 0, dist = 0;
        // if (x1==0 && y1==0 || x2==0 && y2==0) {
        //     points = 1;
        // }
        // for (int i = 1; i <= n && points!=2; i++) {
        //     if (points==1) dist++;
        //     y ++;
        //     if (x1==x&&y1==y || x2==x&&y2==y) points++;
        // }
        // for (int i = 1; i <= n && points!=2; i++) {
        //     if (points==1) dist++;
        //     x++;
        //     if (x1==x&&y1==y || x2==x&&y2==y) points++;
        // }
        // for (int i = 1; i <= n && points!=2; i++) {
        //     if (points==1) dist++;
        //     y--;
        //     if (x1==x&&y1==y || x2==x&&y2==y) points++;
        // }
        // for (int i = 1; i <= n && points!=2; i++) {
        //     if (points==1) dist++;
        //     x--;
        //     if (x1==x&&y1==y || x2==x&&y2==y) points++;
        // }
        // pw.print(Math.min(dist, 4 * n - dist));
        boolean found1=false, found2=false;
        int dist1=0, dist2=0;
        if (x1==0) {
            found1=true;
            dist1=y1;
        } else dist1 = n;
        if (x2==0) {
            found2=true;
            dist2 = y2;
        } else dist2 = n;

        if (y1==n && !found1) {
            found1=true;
            dist1+=x1;
        } else if (!found1) dist1 += n;
        if (y2==n && !found2) {
            found2=true;
            dist2+=x2;
        } else if (!found2) dist2 += n;

        if (x1==n && !found1) {
            found1=true;
            dist1 += n-y1;
        } else if (!found1) dist1 += n;
        if (x2==n && !found2) {
            found2 = true;
            dist2 += n-y2;
        } else if (!found2) dist2 += n;

        if (y1 == 0 && !found1) {
            found1 = true;
            dist1 += n-x1;
        } else if (!found1) dist1 += n;
        if (y2==0 && !found2) {
            dist2 += n-x2;
        } else if (!found2) dist2 += n;

        int dist = Math.abs(dist2-dist1);
        pw.print(Math.min(dist, 4 * n - dist));

        br.close(); pw.close();
    }
}
