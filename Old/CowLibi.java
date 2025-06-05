import java.util.*;
import java.io.*;

public class CowLibi {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int g = Integer.parseInt(line[0]);
        int n = Integer.parseInt(line[1]);
        TreeSet<XYT> grazes = new TreeSet<XYT>(new Comp());
        for (int i = 0; i <= g-1; i++) {
            line = br.readLine().split(" ");
            int x = Integer.parseInt(line[0]);
            int y = Integer.parseInt(line[1]);
            int t = Integer.parseInt(line[2]);
            grazes.add(new XYT(x, y, t));
        }

        int count = 0;
        for (int i = 1; i <= n; i++) {
            line = br.readLine().split(" ");
            int x = Integer.parseInt(line[0]);
            int y = Integer.parseInt(line[1]);
            int t = Integer.parseInt(line[2]);
            XYT cow = new XYT(x, y, t);
            XYT lastGraze = grazes.floor(cow);
            XYT nextGraze = grazes.ceiling(cow);
            if ((lastGraze != null && !canReach(cow, lastGraze))
                || (nextGraze != null && !canReach(cow, nextGraze))) {

                count++;
            }
        }
        pw.println(count);

        br.close(); pw.close();
    }

    static class XYT {
        long x, y, t;

        public XYT(long x, long y, long t) {
            this.x = x;
            this.y = y;
            this.t = t;
        }

        // public String toString() {
        //     return "(x="+x+",y="+y+",t="+t+")";
        // }
    }

    static class Comp implements Comparator<XYT> {
        public int compare(XYT a, XYT b) {
            return Long.compare(a.t, b.t);
        }
    }

    public static boolean canReach(XYT a, XYT b) {
        // the fact that Math.pow() results in a loss of precision is actually bs
        long squareDistance = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
        long squareTime = (a.t-b.t)*(a.t-b.t);
        return squareDistance <= squareTime;
    }
}
