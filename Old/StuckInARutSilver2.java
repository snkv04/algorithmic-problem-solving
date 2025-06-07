import java.util.*;
import java.io.*;

public class StuckInARutSilver2 {
    static ArrayList<Integer>[] adjLists;
    static boolean[] visited;
    static int[] numStopped;

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        TreeMap<Cow, Integer> ecows = new TreeMap<>(new Arbiter()); // maps right-facing cows to their id
        TreeMap<Cow, Integer> ncows = new TreeMap<>(new Arbiter2());
        HashMap<Integer, Cow> active = new HashMap<>(); // maps cow id to location
        for (int i = 0; i <= n-1; i++) {
            char direction = sc.next().charAt(0);
            Cow c = new Cow(sc.nextInt(), sc.nextInt());
            if (direction == 'E') {
                ecows.put(c, i);
            } else {
                ncows.put(c, i);
            }
            active.put(i, c);
        }
        // pw.println("ecows="+ecows);
        // pw.println("ncows" + ncows);

        adjLists = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) adjLists[i] = new ArrayList<Integer>();
        for (Map.Entry<Cow, Integer> east : ecows.entrySet()) {
            // int eastCow = east.getValue();
            for (Map.Entry<Cow, Integer> north : ncows.entrySet()) {
                // int northCow = north.getValue();
                if (!active.containsKey(east.getValue()) || !active.containsKey(north.getValue())) { continue; }
                if (north.getKey().x >= east.getKey().x && east.getKey().y >= north.getKey().y) {
                    int distForN = east.getKey().y - north.getKey().y;
                    int distForE = north.getKey().x - east.getKey().x;
                    if (distForE > distForN) {
                        // n will get there first
                        active.remove(east.getValue());
                        adjLists[north.getValue()].add(east.getValue());
                        break; // can't keep looking at this east cow, since it's stopped
                    } else if (distForN > distForE) {
                        active.remove(north.getValue());
                        adjLists[east.getValue()].add(north.getValue());
                    }
                }
            }
        }
        // pw.println(active);
        // for (int i = 0; i <= n-1; i++) pw.println("i="+i+", and adjlist of i = "+adjLists[i]);

        visited = new boolean[n];
        numStopped = new int[n];
        for (int i = 0; i <= n-1; i++)
            if (!visited[i])
                dfs(i);

        for (int i = 0; i <= n-1; i++) pw.println(numStopped[i]);

        sc.close(); pw.close();

        // look at this in a completely unrelated perspective from the bronze version,
        // assuming i had no knowledge of it.
        // the first thing to observe is that if a cow is stopped, then it cannot be
        // used to stop anything after that point nor can it be stopped (again) anywhere
        // else (obviously). if an east cow is stopped by a north cow, then it cannot ever
        // intersect a north cow that is to the right, and if a north cow is stopped by an
        // east cow, then it cannot interset an east cow above that east cow.
        // so, first sort east cows by y and sort north cows by x. then, for each east
        // cow, look at all of the north cows that are not stopped *from left to right*.
        // (to keep track of the unstopped cows during our pass through all east and north
        // cows, we can have an "active" set.) whenever a north cow is stopped by the
        // current east cow, we can add that north cow to the adjacency list of the east
        // cow, which represents all cows stopped by that cow, and remove it from the list
        // of actively moving cows. if the eCow is instead stopped by the nCow, then we
        // add the eCow to the nCow's stopped list, remove it from the active list, and
        // then continue on to the next east cow, since this east cow cannot process
        // any more north cows. by doing this, although we don't find all of the stops
        // exactly in chronological order, it takes care of all of the stopped cows
        // (using the active list) and makes sure that the only intersections we deal
        // with are ones that actually happen, making the adjacency list accurate to the
        // actual situation if it was simulated. then, observe that the adjacency list
        // creates a directed acyclic graph, as no two cows can stop each other and no
        // cow that is stopped can stop another cow. for each node (cow), we want to
        // find the number it stopped, including the number that each of those stopped,
        // etc. and recurse all the way down to nodes with nothing adjacent to them in
        // order to find this. this can be done by dfsing from every node, which is
        // done in O(n) because of the visited array.
        // the problem was mainly split into two steps. finding which cows each cow
        // directly stops, and then finding how many cows are directly+indirectly
        // stopped by each cow. the first part, which is much harder, was made much
        // easier by making the observation that sorting the cows can find the
        // intersections accurately, and this observation was made by seeing how
        // each cow (and all cows) interacts with the given system through drawing
        // a visualization. it will help to make similar observations in the future,
        // and without looking at the solution ;)
    }

    static void dfs(int node) {
        visited[node] = true;
        int count = 0;
        for (int next : adjLists[node]) {
            if (!visited[next]) {
                dfs(next);
            }
            count += numStopped[next];
            count++;
        }
        numStopped[node] = count;
    }

    static class Cow {
        int x, y;

        public Cow(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public String toString() {
            return "(x="+x+", y="+y+")";
        }
    }

    static class Arbiter implements Comparator<Cow> {
        public int compare(Cow c1, Cow c2) {
            return Integer.compare(c1.y, c2.y);
        }
    }

    static class Arbiter2 implements Comparator<Cow> {
        public int compare(Cow c1, Cow c2) {
            return Integer.compare(c1.x, c2.x);
        }
    }
}
