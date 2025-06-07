import java.util.*;
import java.io.*;

public class TenKindsOfPeople {
    static boolean[][] visited;
    static int r, c;
    static char[][] grid;
    static int[][] component;
    static int currComponent;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        r = Integer.parseInt(line[0]); c = Integer.parseInt(line[1]);
        grid = new char[r][c];
        for (int i = 0; i <= r-1; i++) grid[i] = br.readLine().toCharArray();

        visited = new boolean[r][c];
        component = new int[r][c];
        for (int i = 0; i <= r-1; i++) {
            for (int j = 0; j <= c-1; j++) {
                // all the DFSs combined are O(rc), because each node is only visited once
                currComponent = i*c + j;
                dfs(i, j, grid[i][j]);
            }
        }

        int n = Integer.parseInt(br.readLine());
        while (n-->0) {
            line = br.readLine().split(" ");
            int r1 = Integer.parseInt(line[0])-1;
            int c1 = Integer.parseInt(line[1])-1;
            int r2 = Integer.parseInt(line[2])-1;
            int c2 = Integer.parseInt(line[3])-1;
            if (component[r1][c1] != component[r2][c2]) pw.println("neither");
            else {
                if (grid[r1][c1]=='0') pw.println("binary");
                else pw.println("decimal");
            }
        }

        br.close(); pw.close();
    }

    static void dfs(int i, int j, char color) {
        if (i < 0 || i >= r || j < 0 || j >= c) return;
        if (visited[i][j]) return;
        if (grid[i][j] != color) return;

        visited[i][j] = true;
        component[i][j] = currComponent;
        dfs(i, j-1, color);
        dfs(i, j+1, color);
        dfs(i-1, j, color);
        dfs (i+1, j,color);
    }

    static class Point {
        int i, j;

        public Point(int i, int j) { this.i=i; this.j=j; }
    }

    static class DSU {
        Point[][] parent;
        // int[] size;

        public DSU(int r, int c) {
            parent = new Point[r][c];
            // size = new int[length];
            for (int i = 0; i <= r-1; i++) {
                for (int j = 0; j <= c-1; j++) {
                    parent[i][j] = new Point(i, j);
                }
            }
            // Arrays.fill(size, 1);
        }

        public Point find(int i, int j) {
            if (parent[i][j].i == i && parent[i][j].j==j) return parent[i][j];
            else {
                parent[i][j] = find(parent[i][j].i, parent[i][j].j);
                return parent[i][j];
            }
        }

        public void union(int ai, int aj, int bi, int bj) {
            Point c = find(ai, aj);
            Point d = find(bi, bj);
            if (c.i != d.i || c.j != d.j) {
                parent[d.i][d.j] = c;
                // size[c] = sum;
                // size[d] = sum;
            }
        }

        // public int size(int x) {
        //     return size[x];
        // }
    }
}
