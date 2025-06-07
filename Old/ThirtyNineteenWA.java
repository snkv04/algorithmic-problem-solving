// Author: Sri Vangaru

import java.util.*;
import java.io.*;

// Wrong answer solution
public class ThirtyNineteenWA {
    static ArrayList<Integer>[] graph;
    static ArrayList<Integer> reverseTopological;
    static boolean[] visited;
    static TreeSet<Integer> reachableOnPath;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        graph = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            graph[a].add(b);
        }

        // This solution incorrectly does topological sort directly without
        // ever compressing the graph by its SCCs, and then uses that order
        // to do dynamic programming. Essentially, this solution uses the code
        // of the standard solution to the "longest path in a DAG" problem,
        // except this graph is not guaranteed to be a DAG. Because of this,
        // it may pass a decent number of test cases, but it is ultimately
        // wrong and will not pass most of the test cases with general/arbitrary
        // graphs, especially when they are large.
        visited = new boolean[n];
        reverseTopological = new ArrayList<Integer>();
        for (int i = 0; i <= n-1; i++) if (!visited[i]) dfs(i);

        int max = Integer.MIN_VALUE, start = -1;
        int[] memo = new int[n];
        int[] next = new int[n]; Arrays.fill(next, -1);
        for (int i = 0; i <= reverseTopological.size()-1; i++) {
            int node = reverseTopological.get(i);
            int maxFromAdj = 0;
            for (int adjacent : graph[node]) {
                if (memo[adjacent] > maxFromAdj) {
                    maxFromAdj = memo[adjacent];
                    next[node] = adjacent;
                }
            }
            memo[node] = maxFromAdj + 1;

            if (memo[node] > max) {
                max = memo[node];
                start = node;
            }
        }

        reachableOnPath = new TreeSet<Integer>();
        int currentNode = start;
        while (true) {
            reachableOnPath.add(currentNode);
            if (next[currentNode] == -1) break;
            else currentNode = next[currentNode];
        }
        
        pw.println(max);
        for (int node : reachableOnPath) pw.print(node+1+" ");
        pw.println("\n"+(start+1));

        br.close(); pw.close();
    }

    static void dfs(int node) {
        visited[node] = true;
        for (int next : graph[node])
            if (!visited[next])
                dfs(next);
        
        reverseTopological.add(node);
    }
}
