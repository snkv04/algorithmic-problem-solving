import java.util.*;
import java.io.*;

public class MadokaAndTheElegantGift {
    static int n, m;
    static char[][] grid;
    static boolean[][] visited;
    static TreeSet<Point> component;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            n = Integer.parseInt(line[0]);
            m = Integer.parseInt(line[1]);
            grid = new char[n][m];
            for (int i = 0; i <= n-1; i++) {
                grid[i] = br.readLine().toCharArray();
            }

            boolean works = true;
            visited = new boolean[n][m];
            for (int i = 0; i <= n-1 && works; i++) {
                for (int j = 0; j <= m-1; j++) {
                    component = new TreeSet<Point>();
                    // pw.println("starting at i="+i+", j="+j);
                    dfs(i, j);
                    // pw.println("now components is "+component);
                    if (!check()) {
                        works = false;
                        break;
                    }
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }

    static class Point implements Comparable<Point> {
        int i, j;

        public Point(int i, int j) {
            this.i = i;
            this.j = j;
        }

        public int compareTo(Point other) {
            if (this.i != other.i) return Integer.compare(this.i, other.i);
            else return Integer.compare(this.j, other.j);
        }

        public String toString() {
            return "(i="+i+", j="+j+")";
        }
    }

    static void dfs(int i, int j) {
        // System.out.println("in method starting dfs at i,j "+i+" "+j);
        // System.out.println("i="+i+", j="+j);
        // System.out.println((i<0) + " "+(i>=n)+" "+(j<0)+" "+(j>=n));
        if (i<0 || i >= n || j<0 || j>=m) return;
        if (visited[i][j]) return;
        if (grid[i][j]=='0') return;

        visited[i][j] = true;
        component.add(new Point(i, j));
        dfs(i, j+1);
        dfs(i, j-1);
        dfs(i-1, j);
        dfs(i+1, j);
    }

    static boolean check() {
        // checks if the component of points is a rectangle
        if (component.size() == 0) return true;

        int starti = component.first().i;
        int startj = component.first().j;
        int endj = startj-1;
        while (component.first().i == starti) {
            if (component.first().j != endj+1) return false;
            else {
                endj = component.pollFirst().j;
            }
            if (component.isEmpty()) return true;
        }
        if (component.isEmpty()) return true;

        while (true) {
            for (int j = startj; j <= endj; j++) {
                if (component.isEmpty()) return false;
                if (component.first().i != starti+1) return false;
                if (component.first().j != j) return false;
                component.pollFirst();
            }
            starti++;
            if (component.isEmpty()) return true;
        }
    }
}
