import java.util.*;
import java.io.*;


public class LivestockLineupWithGraph {
    static ArrayList<Integer>[] adj;
    static boolean[] visited;
    static HashMap<String, Integer> dictionary;
    static HashMap<Integer, String> reverseDict;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("lineup.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("lineup.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        // n is the number of conditions
        adj = new ArrayList[8];
        for (int i = 0; i <= 7; i++) {
            adj[i] = new ArrayList<Integer>();
        }

        // can set up a dictionary to convert the cows' names as strings into integers
        // dictionary will map the names in alphabetical order
        // Beatrice, Belinda, Bella, Bessie, Betsy, Blue, Buttercup, Sue
        dictionary = new HashMap<String, Integer>();
        dictionary.put("Beatrice", 0);
        dictionary.put("Belinda", 1);
        dictionary.put("Bella", 2);
        dictionary.put("Bessie", 3);
        dictionary.put("Betsy", 4);
        dictionary.put("Blue", 5);
        dictionary.put("Buttercup", 6);
        dictionary.put("Sue", 7);

        for (int i = 0; i <= n-1; i++) {
            String[] line = br.readLine().split(" must be milked beside ");
            int a = dictionary.get(line[0]);
            int b = dictionary.get(line[1]);
            adj[a].add(b);
            adj[b].add(a);
        }
        for (int i = 0; i <= 7; i++) {
            Collections.sort(adj[i]);
        }

        //// summary
        // the algorithm creates an adjacency list, where the nodes are the cows and an
        // edge is drawn if two cows must be milked next to each other
        // the adjacency lists are each sorted for each node
        // then, the nodes are gone through in alphabetical order
        // if a node has no edges, then it is added to the final end printed array
        // if it has two edges, then ignore it (as it will be reached later)
        // if it has one edge, then start a "dfs" (just running through the connected nodes)
        // until reaching the end of the series of nodes, and when a node is visited in this
        // manner, print it and don't visit it again
        // go through the 8 cows this way, and it's done
        //// justification
        // the graph is created to see which cows must be adjacent to each other, and the rest
        // can just be done purely in alphabetical order
        // the adjacency lists for each node were originally sorted so the nodes could have their
        // incident edges traversed in the proper order, but once the algorithm was changed to only
        // start a "dfs" from nodes with one incident edge, i don't think that's necessary anymore
        // basically, it can be observed that no cow can possibly have more than two adjacent
        // cows, as one cow cannot be milked beside 3 cows in a line of cows
        // so, either cows will be entirely alone or linked to other cows in a "series", where
        // cows that are guaranteed to be milked beside others are connected to each other to
        // confirm that guarantee
        // also, it can be seen that a cow with no edges is alone in the graph, a cow with
        // two edges must be in the middle of a series, and a cow with one edge must either be
        // at the beginning or end of a series; so, we only start looking for cows that have
        // 0 or 1 edges so that when we search through series, we print out cows in an order
        // that ensures cows that must be milked beside each other are
        // finally, we go through all the nodes in alphabetical order so that series are started
        // as alphabetically early as possible, and lone nodes are processed in optimal order
        //// what was learned from this?
        //// (understand that i could always be wrong about this conclusion)
        // always think of using graphs to solve problems lol
        // also, always keep things simple; if there is a simple way to do an optimal solution,
        // DEFO try to find that/figure that out (like only starting DFSs from nodes with one edge)
        // instead of doing a convoluted way (like, you know, starting at the first non-alone node
        // and finding the start of the series it's part of by sorting the adjacent nodes and
        // then printing out everything in order by doing an INORDER TRAVERSAL)
        visited = new boolean[8];
        reverseDict = new HashMap<Integer, String>();
        for (String key : dictionary.keySet()) { reverseDict.put(dictionary.get(key), key); }
        for (int i = 0; i <= 7; i++) {
            if (adj[i].size() == 0) {
                pw.println(reverseDict.get(i));
                visited[i] = true;
            }
            if (adj[i].size() == 1) {
                dfs(i, pw);
            }
        }

        br.close(); pw.close();
    }

    static void dfs(int start, PrintWriter pw) {
        if (!visited[start]) {
            visited[start] = true;
            pw.println(reverseDict.get(start));
        }
        for (int adjacent : adj[start]) {
            if (!visited[adjacent]) dfs(adjacent, pw);
        }
    }
}
