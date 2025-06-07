import java.util.*;
import java.io.*;

public class ProgrammingCompetition {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static ArrayList<Integer>[] adj;
    static int[] size; // size[i] is size of subtree rooted at node i

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        int i = 1;
        while (i <= t) {
            solve();
            i++;
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        int[]p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        adj = new ArrayList[n]; for (int i = 0; i <= n-1; i++) adj[i] = new ArrayList<Integer>();
        for (int i = 1; i <= n-1; i++) {
            int parent = p[i-1] - 1;
            adj[parent].add(i);
        }

        size = new int[n];
        dfs(0);
        // pw.println(Arrays.toString(size));

        int ans = 0, curr = 0;
        while (true) {
            int max = 0, maxNode = -1, sum = 0;
            for (int next : adj[curr]) {
                if (size[next] > max) {
                    max = size[next];
                    maxNode = next;
                }
                sum += size[next];
            }
            // pw.println("children = "+adj[curr]);
            // pw.println("sum = "+sum+", max="+max+", maxChild = "+maxNode);
            // pw.println("ans = "+ans+"\n");
            if (sum == 0) break;

            if (max - ans <= sum - max) {
                ans += sum/2;
                break;
            } else {
                ans += sum-max;
                curr = maxNode;
            }
        }
        pw.println(ans);
    }

    static void dfs(int node) {
        int x = 1;
        for (int next : adj[node]) {
            dfs(next);
            x += size[next];
        }
        size[node] = x;
    }
}


// import java.util.*;

// import java.io.*;

// public class ProgrammingCompetition {
//     static BufferedReader br;
//     static PrintWriter pw;
//     static int MOD = (int) (1e9 + 7); // 998244353;
//     static TreeSet<Integer>[] graph;
//     static int[] transpose;
//     static Stack<Integer> leftmost, rightmost;
//     static int[][] memo;
//     static int[] dist;

//     public static void main(String[] args) throws IOException {
//         br = new BufferedReader(new InputStreamReader(System.in));
//         pw = new PrintWriter(System.out);

//         int t = Integer.parseInt(br.readLine()); // 1;
//         while (t-->0) {
//             solve();
//         }

//         br.close(); pw.close();
//     }

//     static void solve() throws IOException {
//         int n = Integer.parseInt(br.readLine());
//         int[] _p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
//         graph = new TreeSet[n]; for (int i = 0; i <= n-1; i++) graph[i] = new TreeSet<>();
//         transpose = new int[n];
//         transpose[0] = -1;
//         for (int i = 1; i <= n-1; i++) {
//             int parent = _p[i-1];
//             parent--;
//             graph[parent].add(i);
//             transpose[i] = parent;
//         }
//         // for (int i= 0; i <= n-1; i++) pw.println("i="+i+", grpah[i] = "+graph[i]);
//         // pw.println(Arrays.toString(transpose));

//         // TreeSet<Integer> leaves = new TreeSet<>();
//         // for (int i = 0; i <= n-1; i++) {
//         //     if (graph[i].size()==0) leaves.add(i);
//         // }
//         // pw.println(leaves);

//         // int ans = 0;
//         // while (leaves.size() >= 2) {
//         //     int leaf1 = leaves.pollFirst();
//         //     int leaf2 = leaves.pollFirst();
//         //     graph[transpose[leaf1]].remove(leaf1);
//         //     graph[transpose[leaf2]].remove(leaf2);
//         //     if (graph[transpose[leaf1]].size()==0) {
//         //         leaves.add(transpose[leaf1]);
//         //     }
//         //     if (graph[transpose[leaf2]].size()==0) {
//         //         leaves.add(transpose[leaf2]);
//         //     }
//         //     transpose[leaf1] = -1; transpose[leaf2] = -1; // useless?
//         //     ans++;
//         //     pw.println("l1="+leaf1+", l2="+leaf2+", leaves after removing/adding = "+leaves);
//         // }
//         // pw.println(ans);

//         // leftmost = new Stack<>(); rightmost = new Stack<>();
//         // leftmost.add(0); rightmost.add(0);
//         // while (!graph[leftmost.peek()].isEmpty()) {
//         //     leftmost.add(graph[leftmost.peek()].first());
//         // }
//         // while (!graph[rightmost.peek()].isEmpty()) {
//         //     rightmost.add(graph[rightmost.peek()].last());
//         // }

//         // int ans = 0;
//         // while (!(leftmost.peek() == rightmost.peek())) { // while tree isn't a straight line
//         //     System.out.println("leftmost="+leftmost);
//         //     System.out.println("rightmost="+rightmost);
//         //     int leaf1 = leftmost.pop();
//         //     int leaf2 = rightmost.pop();
//         //     graph[leftmost.peek()].pollFirst(); graph[rightmost.peek()].pollLast(); // removing leaf1 and leaf2 from tree
//         //     ans++;
//         //     if (graph[leftmost.peek()].size()>0) leftmost.add(graph[leftmost.peek()].first());
//         //     if (graph[rightmost.peek()].size()>0) rightmost.add(graph[rightmost.peek()].last());
//         // }
//         // pw.println(ans);

//         // boolean[] used = new boolean[n];
//         // Queue<Integer> q = new LinkedList<>();
//         // q.add(0);
//         // int last = 0; int ans = 0;
//         // while (!q.isEmpty()) {
//         //     int node = q.poll();
//         //     if (!used[last] && transpose[node] != last && node != 0) {
//         //         used[last] = true;
//         //         used[node] = true;
//         //         ans++;
//         //         pw.println("last = "+last+", node = "+node);
//         //     }
//         //     last = node;

//         //     for (int next : graph[node]) q.add(next);
//         // }
//         // pw.println(ans);

//         // memo = new int[n][3];
//         // dfs(0);
//         // pw.println(memo[0][2] + memo[0][0]/2);

//         dist = new int[n];
//         dist[0] = 0;
//         dfs2(0);
//         PriorityQueue<Integer> leaves = new PriorityQueue<>(Comparator.comparingInt(o -> -dist[o]));
//         for (int i = 0; i <= n-1; i++) {
//             if (graph[i].size()==0) leaves.add(i);
//         }

//         int ans = 0;
//         while (leaves.size() >= 2) {
//             int leaf1 = leaves.poll();
//             int leaf2 = leaves.poll();
//             graph[transpose[leaf1]].remove(leaf1);
//             graph[transpose[leaf2]].remove(leaf2);
//             if (graph[transpose[leaf1]].size()==0) {
//                 leaves.add(transpose[leaf1]);
//             }
//             if (graph[transpose[leaf2]].size()==0 && transpose[leaf2] != transpose[leaf1]) {
//                 leaves.add(transpose[leaf2]);
//             }
//             ans++;
//         }
//         pw.println(ans);
//     }

//     // static void dfs(int node) {
//     //     for (int next : graph[node]) {
//     //         dfs(next);
//     //     }

//     //     if (graph[node].size() == 0) {
//     //         memo[node][0] = 0;
//     //         memo[node][1] = 1;
//     //         memo[node][2] = 0;
//     //         return;
//     //     }
//     //     if (graph[node].size() == 1) {
//     //         memo[node][0] = memo[graph[node].get(0)][0];
//     //         memo[node][1] = memo[graph[node].get(0)][1]+1;
//     //         memo[node][2] = memo[graph[node].get(0)][2];
//     //         return;
//     //     }

//     //     int matchable = memo[graph[node].get(0)][0],
//     //         unmatchable = memo[graph[node].get(0)][1],
//     //         matched = memo[graph[node].get(0)][2];
//     //     for (int i = 1; i <= graph[node].size()-1; i++) {
//     //         int next = graph[node].get(i);
//     //         matchable += memo[next][0];
//     //         matched += memo[next][2];

//     //         int canMatch = Math.min(matchable+unmatchable, memo[next][1]);
//     //         matched += 2*canMatch;
//     //         unmatchable += memo[next][1]-canMatch;
//     //         int portion = Math.min(canMatch, unmatchable); unmatchable -= portion;
//     //         if (canMatch > unmatchable) {
//     //             canMatch -= unmatchable;
//     //             matchable -= canMatch;
//     //         }
//     //     }
//     //     memo[node][0] = matchable;
//     //     memo[node][1] = unmatchable + 1;
//     //     memo[node][2] = matched;
//     // }

//     static void dfs2(int node) {
//         for (int next : graph[node]) {
//             dist[next] = dist[node] + 1;
//             dfs2(next);
//         }
//     }
// }
