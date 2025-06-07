import java.util.*;
import java.io.*;

public class WormholeSort {
    static int n;
    static int m;
    static ArrayList<Edge>[] adj;
    static boolean[] visited;
    static int[] p;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("wormsort.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Edge>();
            // also decrements the values of the permutation array
            p[i] = p[i] - 1;
        }
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            int w = Integer.parseInt(line[2]);
            adj[a].add(new Edge(b, w));
            adj[b].add(new Edge(a, w));
        }

        int left=0, right=Integer.MAX_VALUE, answer=-1;
        // if left and right are both at the max integer value, then on the next step
        // left will be moved to the min integer value, keeping left <= right and making
        // the loop never end
        if (check((int) (Math.pow(10, 9) + 1))) pw.println(-1);
        else {
            while (left <= right) {
                int mid = (left + right) / 2;
                if (check(mid) == true) {
                    left = mid+1;
                    answer = mid;
                }
                else right = mid-1;
            }
            pw.println(answer);
        }

        //// summary
        // i learned through testing some examples that all of the nodes in a connected
        // component can be rearranged into any permutation
        // so we want to find the maximum weight value such that all the weights in every
        // connected component are greater than that value AND every cow is in the
        // correct node or can reach that node through its connected component
        // (checking that every cow is in the same connected component as its proper place
        // will check both of those conditions)
        // for each value of this minimum weight, we can check if it works by running
        // dfs from all of the nodes and making sure that they're correct spot is reachable
        // from their current spot
        // for the case where no wormholes are needed, we can simply check if the maximum
        // weight is infinity

        // after input
        // one thing i learned was that you shoiul look at things from diffferent angles:
        // example: i tried seeing what max value of the min wormhole would make it so that
        // there is no incorrectly placed cow on its own, but actually it should ahve been
        // there is no incorrectly placed cow in a compnnent separate from its correct place.
        // so instead, it should be we are looking for the max min-weight that maeks sure that
        // every connected component has each of the node cows and their correct spots
        // within the connected component. when we find the max value fo rthis,
        // then we are good. do binary search for this
        

        br.close(); pw.close();
    }

    static class Edge {
        int to, weight;

        public Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    static boolean check(int mid) {
        visited = new boolean[n];
        for (int i = 0; i <= n-1; i++) {
            boolean works = dfs(i, mid);
            if (!works) return false;
        }
        return true;
    }

    static boolean dfs(int start, int mid) {
        Stack<Integer> s = new Stack<Integer>();
        s.add(start);
        HashSet<Integer> cows = new HashSet<Integer>();
        HashSet<Integer> positions = new HashSet<Integer>();
        // i is cow, p[i] is position
        while(!s.isEmpty()) {
            int curr = s.pop();
            if (!visited[curr]) {
                visited[curr] = true;
                cows.add(curr);
                positions.add(p[curr]);
                if (cows.contains(p[curr])) {
                    cows.remove(p[curr]);
                    positions.remove(p[curr]);
                }
                if (positions.contains(curr)) {
                    cows.remove(curr);
                    positions.remove(curr);
                }

                for (Edge adjacent : adj[curr]) {
                    if (adjacent.weight >= mid && !visited[adjacent.to]) {
                        s.add(adjacent.to);
                    }
                }
            }
        }

        if (cows.size() > 0 || positions.size() > 0) return false;
        else return true;
    }
}
