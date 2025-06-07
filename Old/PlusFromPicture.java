import java.util.*;
import java.io.*;

public class PlusFromPicture {
    static char[][] picture;
    static boolean[][] visited;
    static int h, w;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        h = Integer.parseInt(line[0]);
        w = Integer.parseInt(line[1]);
        picture = new char[h][w];
        for (int i = 0; i <= h-1; i++) {
            char[] horizontal = br.readLine().toCharArray();
            for (int j = 0; j <= w-1; j++) {
                picture[i][j] = horizontal[j];
            }
        }
        if (h < 3 || w < 3) {
            pw.println("NO");
            pw.close();
            return;
        }

        boolean plus = false;
        int plusi = -1;
        int plusj = -1;
        for (int i=1; i<=h-2; i++) {
            for (int j = 1; j <= w-2; j++) {
                if (picture[i][j]=='*' && picture[i+1][j]=='*' && picture[i-1][j]=='*'
                    && picture[i][j+1]=='*' && picture[i][j-1]=='*') {

                    plus = true;
                    plusi = i;
                    plusj = j;
                    break;
                }
            }
        }
        if (!plus) {
            pw.println("NO");
            pw.close();
            return;
        }

        // now filling in the plus
        visited = new boolean[h][w];
        visited[plusi][plusj]=true;
        for (int z = 1; z <= 498; z++) {
            if (plusi+z <= h-1 && picture[plusi+z][plusj]=='*') {
                visited[plusi+z][plusj] = true;
            } else break;
        }
        for (int z = 1; z <= 498; z++) {
            if (plusi-z >= 0 && picture[plusi-z][plusj]=='*') {
                visited[plusi-z][plusj] = true;
            } else break;
        }
        for (int z = 1; z <= 498; z++) {
            if (plusj+z <= w-1 && picture[plusi][plusj+z]=='*') {
                visited[plusi][plusj+z] = true;
            } else break;
        }
        for (int z = 1; z <= 498; z++) {
            if (plusj-z >= 0 && picture[plusi][plusj-z]=='*') {
                visited[plusi][plusj-z] = true;
            } else break;
        }
        // "plusi" and "plusj" is a TERRIBLE naming convention lmao

        boolean works = true;
        for (int i = 0; i <= h-1 && works; i++) {
            for (int j = 0; j <= w-1; j++) {
                if (!visited[i][j]&&picture[i][j]=='*') {
                    works=false;
                    break;
                }
            }
        }
        pw.println(works?"YES":"NO");

        br.close(); pw.close();

        // look through the entire board for a small plus
        // if it exists, then extend in all directions until everything is covered,
        // and mark all of these cells as visited
        // now, look through every cell, and if it has not been visited but is still
        // an asterisk, then that means there are other asterisks that are attached
        // to the plus or are separate, and neither case should be true so say no.
        // otherwise, there is only the plus and nothing else, so we say true.
    }



    // static boolean dfs(int i, int j) {
    //     Stack<Point> s = new Stack<Point>();
    //     s.add(new Point(j, i));
    //     TreeSet<Point> points = new TreeSet();
    //     while (!s.isEmpty()) {
    //         Point p = s.pop();
    //         if (!visited[p.x][p.y]) {
    //             visited[p.x][p.y] = true;
    //             points.add(p);
    //             if (p.x+1<w && !visited[p.x+1][p.y] && picture[p.x+1][p.y]=='*') {
    //                 s.add(new Point(p.x+1, p.y));
    //             }
    //             if (p.x-1>-1 && !visited[p.x-1][p.y] && picture[p.x-1][p.y]=='*') {
    //                 s.add(new Point(p.x-1, p.y));
    //             }
    //             if (p.y+1<h && !visited[p.x][p.y+1] && picture[p.x][p.y+1]=='*') {
    //                 s.add(new Point(p.x, p.y+1));
    //             }
    //             if (p.y-1>-1 && !visited[p.x][p.y-1] && picture[p.x][p.y-1]=='*') {
    //                 s.add(new Point(p.x, p.y-1));
    //             }
    //         }           
    //     }

    //     // now checking if the set of points from floodfill makes a plus


    //     return false;
    // }

    // static class Point implements Comparable<Point> {
    //     int x, y;

    //     public Point(int x, int y) {
    //         this.x = x;
    //         this.y=y;
    //     }

    //     public int compareTo(Point other) {
    //         if (this.x != other.x) return Integer.compare(this.x, other.x);
    //         else return Integer.compare(this.y, other.y);
    //     }
    // }
}
