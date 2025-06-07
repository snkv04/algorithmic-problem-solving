import java.util.*;
import java.io.*;

public class ParkingLot {
    static BufferedReader br;
    static PrintWriter pw;
    static char[][] grid;
    static boolean[][] visited;
    static HashSet<Point> component;
    static int r, c;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] asdf = br.readLine().split(" ");
        r = Integer.parseInt(asdf[0]); c = Integer.parseInt(asdf[1]);
        grid = new char[r][c];
        for (int i = 0; i <= r-1; i++) {
            grid[i] = br.readLine().toCharArray();
        }

        HashMap<Point, ArrayList<Point>> adj = new HashMap<>();
        for (int i = 0; i <= r; i++) {
            for (int j = 0; j <= c; j++) {
                adj.put(new Point(i, j), new ArrayList<>());
            }
        }

        for (int i = 0; i <= r; i++) {
            for (int j = 0; j <= c; j++) {
                if (i != r) {
                    adj.get(new Point(i, j)).add(new Point(i+1, j));
                    adj.get(new Point(i+1, j)).add(new Point(i, j));
                }
                if (j != c) {
                    adj.get(new Point(i, j)).add(new Point(i, j+1));
                    adj.get(new Point(i, j+1)).add(new Point(i, j));
                }
            }
        }

        visited = new boolean[r][c];
        for (int i = 0; i <= r-1; i++) {
            for (int j = 0; j <= c-1; j++) {
                if (!visited[i][j] && grid[i][j] == '.') {
                    component = new HashSet<>();
                    dfs(i, j);

                    ArrayList<Point> intersections = new ArrayList<>(); for (Point p : component) intersections.add(p);
                    for (int a = 0; a <= intersections.size()-1; a++) {
                        for (int b = a+1; b <= intersections.size()-1; b++) {
                            Point c = intersections.get(a);
                            Point d = intersections.get(b);
                            if (c.i != d.i && c.j != d.j && connected(c.i, c.j, d.i, d.j)) {
                                adj.get(c).add(d);
                                adj.get(d).add(c);
                            }
                        }
                    }
                }
            }
        }
        
        HashMap<Point, Double> dist = new HashMap<>();
        for (int i = 0; i <= r; i++) {
            for (int j = 0; j <= c; j++) {
                dist.put(new Point(i, j), (double) Integer.MAX_VALUE);
            }
        }
        dist.put(new Point(0, 0), (double) 0);
        PriorityQueue<Point> pq = new PriorityQueue<>(Comparator.comparingDouble(o -> dist.get(o)));
        pq.add(new Point(0, 0));
        while (!pq.isEmpty()) {
            Point p = pq.poll();
            for (Point next : adj.get(p)) {
                double c = Math.sqrt((next.i-p.i)*(next.i-p.i) + (next.j-p.j)*(next.j-p.j));
                if (dist.get(next) > dist.get(p) + c) {
                    dist.put(next, dist.get(p) + c);
                    pq.add(next);
                }
            }
        }
        pw.println(dist.get(new Point(r, c)));
    }

    static void dfs(int i, int j) {
        if (i<0 || i >= r || j<0 || j>=c) return;
        if (visited[i][j]) return;
        if (grid[i][j] == '#') return;

        visited[i][j] = true;
        component.add(new Point(i, j));
        component.add(new Point(i+1, j));
        component.add(new Point(i, j+1));
        component.add(new Point(i+1, j+1));

        dfs(i, j+1);
        dfs(i, j-1);
        dfs(i+1, j);
        dfs(i-1, j);
    }

    static boolean connected(double i1, double j1, double i2, double j2) {
        double deltai = i2 - i1;
        double deltaj = j2 - j1;
        double curri = i1;
        double currj = j1;
        while (true) {
            double nexti = i2>i1 ? (Math.floor(curri)+1) : (Math.ceil(curri)-1);
            double nextj = j2>j1 ? (Math.floor(currj)+1) : (Math.ceil(currj)-1);
            double toNextI = Math.sqrt(Math.pow(nexti-curri, 2) + Math.pow(
                Math.abs(nexti-curri)*(deltaj/deltai), 2
            ));
            double toNextJ = Math.sqrt(Math.pow(
                Math.abs(nextj-currj)*(deltai/deltaj), 2
            ) + Math.pow(nextj-currj, 2));

            double di, dj;
            if (toNextI <= toNextJ) {
                di = nexti-curri;
                dj = (nexti-curri)*(deltaj/deltai);
            } else {
                di = (nextj-currj)*(deltai/deltaj);
                dj = nextj - currj;
            }
            int flri = (int) Math.floor(curri + 0.5*di);
            int flrj = (int) Math.floor(currj + 0.5 * dj);
            if (grid[flri][flrj] == '#') return false;
            curri += di;
            currj += dj;

            if (Math.abs(curri-i2)<=0.001 && Math.abs(currj-j2)<=0.001) break;
        }
        return true;
    }

    static class Point {
        int i, j;

        public Point(int i, int j) {
            this.i = i;
            this.j = j;
        }
        
        @Override
        public boolean equals(Object obj) {
            if (this == obj) return true;
            if (obj == null) return false;
            if (!(obj instanceof Point)) return false;

            Point other = (Point) obj;
            return this.i == other.i && this.j == other.j;
        }

        @Override
        public int hashCode() {
            return (this.i+" "+this.j).hashCode();
        }

        public String toString() {
            return "(i="+i+", j="+j+")";
        }
    }
}
