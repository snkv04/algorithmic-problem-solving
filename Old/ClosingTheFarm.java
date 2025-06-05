import java.util.*;
import java.io.*;

public class ClosingTheFarm {
    static ArrayList<Integer>[] adj;
    static TreeSet<Integer> unclosedBarns;
    static boolean[] visited;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("closing.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("closing.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Integer>();
        }
        for (int i = 1; i <= m; i++) {
            int[] edgeLine = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int a = edgeLine[0] - 1;
            int b = edgeLine[1] - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        unclosedBarns = new TreeSet<Integer>();
        for (int i = 0; i <= n-1; i++) {
            unclosedBarns.add(i);
        }
        for (int i = 0; i <= n-1; i++) {
            int barnBeingClosed = Integer.parseInt(br.readLine()) - 1;
            visited = new boolean[n];
            boolean fullyConnected = bfs(unclosedBarns.first(), n-i);
            pw.println(fullyConnected ? "YES" : "NO");
            remove(barnBeingClosed);
        }

        br.close(); pw.close();
    }

    // closes a barn
    // removes a barn from the list of running barns, deletes the adjacency arraylist for that barn,
    // and removes it from the rest of the whole adjacency list
    public static void remove(int barn) {
        unclosedBarns.remove(barn);
        adj[barn] = new ArrayList<Integer>();
        for (int i = 0; i <= adj.length-1; i++) {
            if (adj[i].contains(barn)) {
                adj[i].remove(new Integer(barn));
            }
        }
    }

    public static boolean bfs(int barn, int totalBarns) {
        int count = 0;
        Queue<Integer> q = new LinkedList<Integer>();
        q.add(barn);
        while(!q.isEmpty()) {
            int curr = q.poll();
            
            // This is only necessary because there are duplicate paths; if not for them,
            // then the remove() function would completely take care of closing barns.
            // Since this is here, though, this line essentially makes
            // the second and third parts of the remove() function unnecesssary.
            // Alternatively, instead of having this line, the "if" in the
            // remove() function could be changed to a "while" to completely remove
            // all duplicate paths.
            if (!unclosedBarns.contains(curr)) continue;

            if (!visited[curr]) {
                visited[curr] = true;
                count++;
                for (int adjacent : adj[curr]) {
                    if (!visited[adjacent]) {
                        q.add(adjacent);
                    }
                }
            }
        }
        return count == totalBarns;
    }
}
