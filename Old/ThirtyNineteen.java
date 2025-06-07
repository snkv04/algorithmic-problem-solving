// Author: Sri Vangaru

import java.util.*;
import java.io.*;

public class ThirtyNineteen {
    static ArrayList<Integer>[] graph;
    static ArrayList<Integer>[] transposeGraph;
    static ArrayList<Integer> reverseTopological;
    static boolean[] visited;
    static int[] scc;
    static TreeMap<Integer, TreeSet<Integer>> nodesInSCC;
    static ArrayList<Integer>[] condensed;
    static TreeSet<Integer> reachableOnPath;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // The problem can simply be stated as: find the (not necessarily unique)
        // longest path in a directed graph, where the path does not have to be
        // simple (i.e. it can repeat vertices) and the length of the path is
        // defined as the number of vertices within it.

        // Sets up directed graph and transpose graph, and then takes input
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        graph = new ArrayList[n]; transposeGraph = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            graph[i] = new ArrayList<>();
            transposeGraph[i] = new ArrayList<>();
        }
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            graph[a].add(b);
            transposeGraph[b].add(a);
        }

        // Uses Kosaraju's algorithm to map each node to its strongly connected component (SCC),
        // where each SCC is denoted by a representative node
        visited = new boolean[n];
        reverseTopological = new ArrayList<Integer>();
        for (int i = 0; i <= n-1; i++) if (!visited[i]) dfs(i);
        visited = new boolean[n];
        scc = new int[n];
        for (int i = n-1; i >= 0; i--) {
            int node = reverseTopological.get(i);
            if (!visited[node]) dfs2(node, node);
        }

        // Condenses the graph so that each SCC is treated as a singular node--keeping track
        // of the original nodes within each SCC--resulting in a directed acylic graph (DAG)
        condensed = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) condensed[i] = new ArrayList<Integer>();
        nodesInSCC = new TreeMap<Integer, TreeSet<Integer>>();
        for (int i = 0; i <= n-1; i++) {
            for (int adjacent : graph[i]) {
                if (scc[i] != scc[adjacent]) {
                    condensed[scc[i]].add(scc[adjacent]);
                }
            }

            if (!nodesInSCC.containsKey(scc[i])) nodesInSCC.put(scc[i], new TreeSet<>());
            nodesInSCC.get(scc[i]).add(i);
        }

        // Finds the reverse topological ordering (or normal DFS postorder ordering) of the nodes
        // in the condensed graph
        visited = new boolean[n];
        reverseTopological = new ArrayList<Integer>();
        for (int i = 0; i <= n-1; i++) if (!visited[i] && i == scc[i]) dfs3(i);

        // Uses dynamic programming to find the longest path in the condensed graph, where
        // the length of a path is defined by the number of bases (nodes from the original
        // graph) covered in the path. This approach is allowed because the drone is allowed
        // to visit the same base multiple times in its "path", so it can go around and around
        // in circles within an SCC in order to land at the correct node in the SCC that has
        // an outgoing edge to a different SCC. Similarly, any node within the start SCC
        // is a valid start node, so we simply arbitrarily choose the SCC's representative
        // node.
        int max = Integer.MIN_VALUE, start = -1;
        int[] memo = new int[n];
        int[] next = new int[n]; Arrays.fill(next, -1);
        for (int i = 0; i <= reverseTopological.size()-1; i++) {
            int node = reverseTopological.get(i);
            int maxFromAdj = 0;
            for (int adjacent : condensed[node]) {
                if (memo[adjacent] > maxFromAdj) {
                    maxFromAdj = memo[adjacent];
                    next[node] = adjacent;
                }
            }
            memo[node] = maxFromAdj + nodesInSCC.get(node).size();

            if (memo[node] > max) {
                max = memo[node];
                start = node;
            }
        }

        // Retrieves all of the nodes reachable within the longest path defined
        // by the DP earlier
        reachableOnPath = new TreeSet<Integer>();
        int currentNode = start;
        while (true) {
            for (int nodeInSCC : nodesInSCC.get(currentNode)) reachableOnPath.add(nodeInSCC);

            if (next[currentNode] == -1) break;
            else currentNode = next[currentNode];
        }

        // Outputs the results
        pw.println(max);
        for (int node : reachableOnPath) pw.print(node+1+" ");
        pw.println("\n"+(start+1));

        br.close(); pw.close();
    }

    // Utility function for Kosaraju's algorithm
    static void dfs(int node) {
        visited[node] = true;
        for (int next : graph[node])
            if (!visited[next])
                dfs(next);
        
        reverseTopological.add(node);
    }

    // Utility function for Kosaraju's algorithm
    static void dfs2(int node, int start) {
        visited[node] = true;
        scc[node] = start;
        for (int next : transposeGraph[node])
            if (!visited[next])
                dfs2(next, start);
    }

    // Utility function for finding the reverse topological sorting of the
    // condensed graph's nodes
    static void dfs3(int node) {
        visited[node] = true;
        for (int next : condensed[node])
            if (!visited[next])
                dfs3(next);

        reverseTopological.add(node);
    }
}
