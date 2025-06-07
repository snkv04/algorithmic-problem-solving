import java.util.*;
import java.io.*;

public class MooyoMooyo {
    static boolean[][] visited;
    static int[][] grid;
    static int n;

    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("mooyomooyo.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("mooyomooyo.out", false)));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        int k = Integer.parseInt(line[1]);
        grid = new int[n][10];
        for (int i = 0; i <= n-1; i++) {
            char[] gridLine = br.readLine().toCharArray();
            for (int j = 0; j <= 9; j++) {
                grid[i][j] = Character.getNumericValue(gridLine[j]);
            }
        }
        
        boolean foundAtLeast1 = true;
        while (foundAtLeast1) { // nothing is changed in the grid on the last loop
            foundAtLeast1 = false;

            // makes all components with size >= k equal to 0s
            visited = new boolean[n][10];
            for (int i = 0; i <= n-1; i++) {
                for (int j=0; j<=9; j++) {
                    TreeSet<Point> set = dfs(i, j);
                    if (set.size() >= k && grid[set.first().r][set.first().c] != 0) {
                        foundAtLeast1 = true;
                        for (Point point : set) {
                            grid[point.r][point.c] = 0;
                        }
                    }
                }
            }

            // drags everything down to fill the 0s
            for (int c = 0; c <= 9; c++) {
                int zeros=0;
                for (int r = n-1; r >= 0; r--) {
                    if (grid[r][c] == 0) {
                        zeros++;
                    } else {
                        if (zeros != 0) {
                            grid[r+zeros][c] = grid[r][c];
                            grid[r][c] = 0;
                        }
                    }
                }
            }
        }

        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= 9; j++) {
                pw.print(grid[i][j]);
            }
            pw.println();
        }

        br.close(); pw.close();
    }

    static class Point implements Comparable<Point> {
        int r, c;

        public Point(int i, int j) {
            r = i;
            c = j;
        }

        public String toString() {
            return "(r="+r+",c="+c+")";
        }

        public int compareTo(Point other) {
            if (this.r != other.r) return Integer.compare(this.r, other.r);
            else return Integer.compare(this.c, other.c);
        }
    }

    static TreeSet<Point> dfs(int i, int j) {
        TreeSet<Point> result = new TreeSet<Point>();
        Stack<Point> s = new Stack<Point>();
        s.add(new Point(i, j));
        // int count = 0;
        while (!s.isEmpty()) {
            Point node = s.pop();
            if (!visited[node.r][node.c]) {
                visited[node.r][node.c] = true;
                result.add(new Point(node.r, node.c));

                if (node.r+1 <= n-1 && !visited[node.r+1][node.c] && grid[node.r][node.c]==grid[node.r+1][node.c])
                    s.add(new Point(node.r+1, node.c));
                if (node.r-1 >= 0 && !visited[node.r-1][node.c] && grid[node.r][node.c]==grid[node.r-1][node.c])
                    s.add(new Point(node.r-1, node.c));
                if (node.c+1 <= 9 && !visited[node.r][node.c+1] && grid[node.r][node.c]==grid[node.r][node.c+1])
                    s.add(new Point(node.r, node.c+1));
                if (node.c-1 >= 0 && !visited[node.r][node.c-1] && grid[node.r][node.c]==grid[node.r][node.c-1])
                    s.add(new Point(node.r, node.c-1));
            }
        }

        return result;
    }

    static void print() {
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= 9; j++) {
                System.out.print(grid[i][j]);
            }
            System.out.println();
        }
    }
}
