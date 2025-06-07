import java.util.*;
import java.io.*;

public class IcyPerimeter {
    static int n;
    static char[][] grid;
    static boolean[][] visited;

    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("perimeter.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("perimeter.out", false)));

        n = Integer.parseInt(br.readLine());
        grid = new char[n][n];
        for (int i = 0; i <= n-1; i++) {
            char[] gridLine = br.readLine().toCharArray();
            for (int j = 0; j <= n-1; j++) {
                grid[i][j] = gridLine[j];
            }
        }
        // for (char[] line : grid) {
        //     pw.println(line);
        // }

        visited = new boolean[n][n];
        TreeSet<Blob> piles = new TreeSet<Blob>(new Comp());
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= n-1; j++) {
                Blob pile = dfs(i, j);
                piles.add(pile);
            }
        }
        pw.println(piles.last().area + " " + piles.last().perimeter);

        br.close(); pw.close();
    }

    static class Blob {
        long area, perimeter;

        public Blob(long area, long perimeter) {
            this.area = area;
            this.perimeter = perimeter;
        }
    }

    static class Comp implements Comparator<Blob> {
        public int compare(Blob b1, Blob b2) {
            if (b1.area != b2.area) return Long.compare(b1.area, b2.area);
            else return -Long.compare(b1.perimeter, b2.perimeter); // negative so smallest perim at end of treeset
        }
    }

    static Blob dfs(int i, int j) {
        Stack<Point> s = new Stack<Point>();
        if (grid[i][j] == '.') {
            visited[i][j] = true;
            return new Blob(0, 0);
        }
        s.add(new Point(i, j));
        long area = 0;
        long perimeter = 0;
        while (!s.isEmpty()) {
            Point currPoint = s.pop();
            int r = currPoint.i;
            int c = currPoint.j;
            if (!visited[r][c]) {
                visited[r][c] = true;
                area++;
                perimeter += 4;
                if (r+1 <= n-1 && grid[r+1][c] == '#') {
                    perimeter--;
                    if (!visited[r+1][c]) s.add(new Point(r+1,c));
                }
                if (r-1 >=0 && grid[r-1][c] == '#') {
                    perimeter--;
                    if (!visited[r-1][c]) s.add(new Point(r-1,c));
                }
                if (c+1<= n-1 && grid[r][c+1] == '#') {
                    perimeter--;
                    if (!visited[r][c+1]) s.add(new Point(r,c+1));
                }
                if (c-1>=0 && grid[r][c-1] == '#') {
                    perimeter--;
                    if (!visited[r][c-1]) s.add(new Point(r,c-1));
                }
            }
        }
        return new Blob(area, perimeter);
    }

    static class Point {
        int i, j;

        public Point(int r, int c) {
            i = r;
            j = c;
        }
    }
}
