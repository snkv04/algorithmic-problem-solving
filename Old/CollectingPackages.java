import java.util.*;
import java.io.*;

public class CollectingPackages {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i<=t; i++) {
            int n = sc.nextInt();
            TreeSet<Point> packages = new TreeSet<Point>(new Arbiter());
            for (int j=1; j<=n; j++) { packages.add(new Point(sc.nextInt(), sc.nextInt())); }

            String ans = "";
            int prevx = 0;
            int prevy = 0;
            boolean works = true;
            for (int j = 1; j <= n; j++) {
                int distx = packages.first().x-prevx;
                int disty = packages.first().y-prevy;
                if (distx < 0 || disty < 0) {
                    works = false;
                    break;
                } else {
                    for (int k=1; k<=distx; k++) {
                        ans += "R";
                    }
                    for (int k=1; k<=disty; k++) {
                        ans += "U";
                    }
                    prevx = packages.first().x;
                    prevy = packages.first().y;
                    packages.remove(packages.first());
                }
            }

            if (works) {
                pw.println("YES");
                pw.println(ans);
            }
            else pw.println("NO");
        }

        sc.close(); pw.close();
    }

    static class Point {
        int x, y;

        public Point(int x, int y) {
            this.x =x;
            this.y=y;
        }
    }

    static class Arbiter implements Comparator<Point> {
        public int compare(Point p1, Point p2) {
            if (p1.x != p2.x) return Integer.compare(p1.x, p2.x);
            else return Integer.compare(p1.y, p2.y);
        }
    }
}
