// Author: Sri Vangaru

import java.util.*;
import java.io.*;

// Solution that is incorrect because it will get "time limit exceeded"
public class ThirtyNineteenTLE {
    static ArrayList<Integer>[] graph;
    static ArrayList<Integer>[] transposeGraph;
    static ArrayList<Integer> reverseTopological;
    static boolean[] visited;
    static int[] scc;
    static TreeMap<Integer, TreeSet<Integer>> nodesInSCC;
    static ArrayList<Integer>[] condensed;
    static TreeSet<Integer> reachableOnPath;
    static int[] next;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

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

        visited = new boolean[n];
        reverseTopological = new ArrayList<Integer>();
        for (int i = 0; i <= n-1; i++) if (!visited[i]) dfs(i);
        visited = new boolean[n];
        scc = new int[n];
        for (int i = n-1; i >= 0; i--) {
            int node = reverseTopological.get(i);
            if (!visited[node]) dfs2(node, node);
        }
        
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

        visited = new boolean[n];
        reverseTopological = new ArrayList<Integer>();
        for (int i = 0; i <= n-1; i++) if (!visited[i] && i == scc[i]) dfs3(i);

        // This does recursive dynamic programming without memoization,
        // so this section of the code is O(n * (n+m)), which is too slow.
        int max = Integer.MIN_VALUE, start = -1;
        next = new int[n]; Arrays.fill(next, -1);
        for (int i = 0; i <= reverseTopological.size()-1; i++) {
            int node = reverseTopological.get(i);
            int longestPath = longest(node);

            if (longestPath > max) {
                max = longestPath;
                start = node;
            }
        }

        reachableOnPath = new TreeSet<Integer>();
        int currentNode = start;
        while (true) {
            for (int nodeInSCC : nodesInSCC.get(currentNode)) reachableOnPath.add(nodeInSCC);

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

    static void dfs2(int node, int start) {
        visited[node] = true;
        scc[node] = start;
        for (int next : transposeGraph[node])
            if (!visited[next])
                dfs2(next, start);
    }

    static void dfs3(int node) {
        visited[node] = true;
        for (int next : condensed[node])
            if (!visited[next])
                dfs3(next);

        reverseTopological.add(node);
    }

    static int longest(int node) {
        int longestPath = 0;
        for (int adjacent : condensed[node]) {
            int longestPathFromAdjacent = longest(adjacent);
            if (longestPathFromAdjacent > longestPath) {
                longestPath = longestPathFromAdjacent;
                next[node] = adjacent;
            }
        }
        longestPath += nodesInSCC.get(node).size();
        return longestPath;
    }
}
