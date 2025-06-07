import java.util.*;
import java.io.*;

public class StuckInARutSilver {
    // for getting the cows that each cow stopped
    static Cow[] cows;
    static ArrayList<Cow> active;
    static TreeMap<Rut, Integer> ruts;
    static int[] distances;

    // for parsing through the graph to determine each cow's blame
    static ArrayList<Integer>[] adjLists;
    static boolean[] visited;
    static int[] numStopped;
    
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        cows = new Cow[n];
        active = new ArrayList<Cow>();
        for (int i = 0; i <= n-1; i++) {
            char direction = sc.next().charAt(0);
            int x = sc.nextInt();
            int y = sc.nextInt();
            Cow c = new Cow(i, x, y, direction);
            cows[i] = c;
            active.add(c);
        }

        TreeSet<Integer> times = new TreeSet();
        for (int i = 0; i <= n-1; i++) {
            for (int j=i+1; j<=n-1; j++) {
                // calculates the time of potential intersection
                if (cows[i].direction=='E' && cows[j].direction=='E'
                    || cows[i].direction=='N' && cows[j].direction=='N') {

                    continue;
                }

                Cow right, up;
                if (cows[i].direction=='E') {
                    right = cows[i];
                    up = cows[j];
                } else {
                    right = cows[j];
                    up = cows[i];
                }
                if (up.x >= right.x && right.y >= up.y) {
                    times.add(up.x-right.x);
                    times.add(right.y-up.y);
                }
                // else they won't ever intersect, nor will their paths
            }
        }
        // for (int time : times) pw.println(time);

        int lastTime = 0;
        distances = new int[n];
        for (int i = 0; i <= n-1; i++) distances[i] = 1;
        ruts = new TreeMap<Rut, Integer>(); // maps the rut to the cow who left it
        addRuts();
        adjLists = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) adjLists[i] = new ArrayList<Integer>();
        for (int time : times) {
            int dist = time - lastTime;
            lastTime = time;
            for (int i = active.size()-1; i >= 0; i--) {
                Cow c = active.get(i);
                c.move(dist);
                if (ruts.containsKey(new Rut(c.x, c.y))) {
                    // add to adj list before updating the stopped cow's location to one spot backward
                    adjLists[ruts.get(new Rut(c.x, c.y))].add(c.id);
                    c.move(-1);
                    distances[c.id] += dist-1;
                    ruts.put(new Rut(c.x, c.y), c.id);
                    active.remove(i);
                } else {
                    distances[c.id] += dist;
                }
            }
            addRuts();
        }
        // for (int i = 0; i <= n-1; i++) {
        //     pw.println("i="+i+", adjlist of i = "+adjLists[i]);
        // }

        visited = new boolean[n];
        numStopped = new int[n];
        for (int i = 0; i <= n-1; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        // pw.println(Arrays.toString(numStopped));

        for (int i = 0; i <= n-1; i++) pw.println(numStopped[i]);

        sc.close(); pw.close();
    }

    static void dfs(int node) {
        visited[node] = true;
        int count = 0;
        for (int next : adjLists[node]) {
            if (!visited[next]) {
                dfs(next);
            }
            count++;
            count += numStopped[next];
        }
        numStopped[node] = count;
    }

    static void addRuts() {
        for (Cow c : active) {
            ruts.put(new Rut(c.x, c.y), c.id);
        }
    }

    static class Cow {
        int id, x, y;
        char direction;

        public Cow(int id, int x, int y, char dir) {
            this.id = id;
            this.x = x;
            this.y = y;
            direction = dir;
        }

        public void move(int dist) {
            if (direction == 'E') {
                this.x += dist;
            } else {
                this.y += dist;
            }
        }
    }

    static class Rut implements Comparable<Rut> {
        int x, y;

        public Rut(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int compareTo(Rut other) {
            if (this.x != other.x) return Integer.compare(this.x, other.x);
            else return Integer.compare(this.y, other.y);
        }

        // public String toString() {
        //     return "(x="+x+",y="+y+")";
        // }
    }
}