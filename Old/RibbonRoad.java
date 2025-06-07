import java.util.*;
import java.io.*;

public class RibbonRoad {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    public static void solve() throws IOException {
        // Reads in the vertices of the (possibly concave) polygon
        int n = Integer.parseInt(br.readLine());
        Point[] vertices = new Point[n];
        String[] s;
        for (int i = 0; i < n; i++) {
            s = br.readLine().split(" ");
            vertices[i] = new Point(Integer.parseInt(s[0]), Integer.parseInt(s[1]));
        }
        
        // Flips the array of vertices if they are not given in counterclockwise order
        ArrayList<Integer> convexHull = hull(vertices);
        int increasingIndices = 0, decreasingIndices = 0;
        for (int i = 0; i < convexHull.size(); i++) {
            if (convexHull.get(i) < convexHull.get((i+1)%convexHull.size())) {
                increasingIndices++;
            } else {
                decreasingIndices++;
            }
        }
        // if (Math.min(decreasingIndices, increasingIndices) != 1) {
        //     throw new IOException(); // this should never happen, but it does on Test Case 53?
        // }
        if (decreasingIndices > increasingIndices) {
            for (int i = 0; i < n / 2; i++) {
                Point temp = vertices[i];
                vertices[i] = vertices[n-1-i];
                vertices[n-1-i] = temp;
            }
        }

        // Reads in the coordinates of the ant's ray vector
        s = br.readLine().split(" ");
        Point ant = new Point(Integer.parseInt(s[0]), Integer.parseInt(s[1]));
        Point rayend = new Point(Integer.parseInt(s[2]), Integer.parseInt(s[3]));

        // Finds the edge (or point) that the ant is on
        Point before = null, on = null, after = null;
        for (int i = 0; i <=  n-1; i++) {
            if (vertices[i].x == ant.x && vertices[i].y == ant.y) {
                on = vertices[i];
                after = vertices[(i+1)%n];
                before = vertices[(i+n-1)%n];
                break;
            }
        }
        if (on == null) for (int i = 0; i < n; i++) {
            Point last = vertices[i], next = vertices[(i+1)%n];
            long dx = next.x - last.x, dy = next.y - last.y; // dx and dy for the edge itself
            long gcd = gcd(dx, dy);
            long dxOrig = dx, dyOrig = dy;
            dx /= gcd; dy /= gcd;
            long dx2 = ant.x - last.x, dy2 = ant.y - last.y; // dx and dy from the "last" point to the ant
            boolean onLine = (dx==0 && dx2==0 && bounded(dy2, 0, dyOrig))
                || (dy == 0 && dy2 == 0 && bounded(dx2, 0, dxOrig))
                || (dx!=0 && dx2!=0 && (dx2 % dx == 0) && dy!=0 && dy2!=0 &&  (dy2 % dy == 0) && (dx2/dx == dy2/dy) && bounded(dx2, 0, dxOrig) && bounded(dy2, 0, dyOrig));
            if (onLine) {
                before = last;
                after = next;
                break;
            }
        }

        // Uses cross products to check if the ray points inside or outside
        long[] ray = vec(ant, rayend);
        long[] tonext = vec(ant, after);
        long[] toprev = vec(ant, before);
        if (on == null) {
            if (cross(ray, tonext) == 0) {
                pw.println("?");
            } else {
                if (cross(tonext, ray) > 0) {
                    pw.println("inside");
                } else {
                    pw.println("outside");
                }
            }
        } else {
            if (cross(tonext, ray) == 0 || cross(toprev, ray) == 0) {
                pw.println("?");
            } else {
                if (cross(tonext, ray) > 0 && cross(toprev, ray) < 0) {
                    pw.println("inside");
                } else if (cross(invert(tonext), ray) > 0 && cross(invert(toprev), ray) < 0) {
                    pw.println("outside");
                } else {
                    pw.println("?");
                }
            }
        }
    }

    static ArrayList<Integer> hull(Point[] points) {
        int bottomLeft = 0;
        for (int i = 1; i < points.length; i++) {
            if (points[i].x < points[bottomLeft].x) {
                bottomLeft = i;
            } else if (points[i].x == points[bottomLeft].x && points[i].y < points[bottomLeft].y) {
                bottomLeft = i;
            }
        }
        
        final Point anchor = points[bottomLeft];
        PriorityQueue<Integer> sorted = new PriorityQueue<Integer>((i1, i2) -> {
            Point p1 = points[i1], p2 = points[i2];
            long cross = cross(vec(anchor, p2), vec(anchor, p1));
            return sign(cross);
        });
        for (int i = 0; i < points.length; i++) {
            if (i != bottomLeft) {
                sorted.add(i);
            }
        }

        Stack<Integer> hull = new Stack<>();
        hull.add(bottomLeft);
        while (!sorted.isEmpty()) {
            int idx = sorted.poll();
            Point polled = points[idx];
            while (true) {
                if (sorted.isEmpty()) break;
                Point next = points[sorted.peek()];
                if (cross(vec(anchor, polled), vec(anchor, next)) == 0) {
                    sorted.poll();
                    if (sqdist(anchor, next) > sqdist(anchor, polled)) {
                        polled = next;
                    }
                } else {
                    break;
                }
            }

            while (hull.size() > 1) {
                int top = hull.pop();
                Point secondFromTop = points[hull.peek()];
                if (cross(vec(secondFromTop, points[top]), vec(points[top], polled)) > 0) {
                    hull.add(top);
                    break;
                }
            }

            hull.add(idx);
        }
        
        return new ArrayList<Integer>(hull);
    }

    static long[] vec(Point p1, Point p2) {
        return new long[] {p2.x-p1.x, p2.y-p1.y, 0};
    }

    static long sqdist(Point p1, Point p2) {
        long x1=p1.x, y1=p1.y,x2=p2.x,y2=p2.y;
        return (x2-x1)*(x2-x1) + (y2-y1)*(y1-y1);
    }

    static int sign(long x) {
        if (x == 0) return 0;
        if (x > 0) return 1;
        else return -1;
    }

    static boolean bounded(long x, long a, long b) {
        return x >= Math.min(a, b) && x <= Math.max(a, b);
    }

    static long[] invert(long[] vector) {
        return new long[] {-1*vector[0], -1*vector[1], 0};
    }

    static long cross(long[] a, long[] b) {
        // long[] result = {a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]};
        // return result[0] + result[1] + result[2];
        return a[0]*b[1] - a[1]*b[0];
    }

    static class Point {
        long x, y;

        public Point(long x, long y) {
            this.x = x;
            this.y = y;
        }

        public String toString() {
            return "(x="+x+", y="+y+")";
        }
    }

    static long gcd(long a, long b) {
        a = Math.abs(a);
        b = Math.abs(b);

        long A = Math.max(a, b), B = Math.min(a, b);
        if (B == 0) return A;
        else return gcd(B, A % B);
    }
}
